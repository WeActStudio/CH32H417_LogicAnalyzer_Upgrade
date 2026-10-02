/*
 * CH32H417 Logic Analyzer firmware upgrade tool
 *
 * Serial (USB CDC / usbser) channel implementation.
 *
 * Enumeration walks the Windows COM port device interface with SetupAPI and
 * parses the VID / PID / serial number straight out of the interface device
 * path - no port has to be opened for that, so a terminal holding the port
 * open does not hide the board. Entering IAP does open the port and pushes
 * the magic baud rate through SET_LINE_CODING (see serialdev.h).
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "serialdev.h"

#include <QCoreApplication>
#include <QRegularExpression>

#include <algorithm>
#include <cstring>

#ifdef Q_OS_WIN
#include <windows.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#endif

namespace {

/* GUID_DEVINTERFACE_COMPORT, defined in the DDK (ntddser.h); spelled out here
 * to avoid pulling the whole header in */
const GUID kComPortInterfaceGuid = {
    0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 }
};

/*
 * A USB device instance ID looks like:
 *   USB\VID_1A86&PID_5540\B5E339E33906E19C7F6416064C   (has a serial string)
 *   USB\VID_1A86&PID_5540\9&26C87144&1                 (location style, no
 *                                                       serial string - the
 *                                                       firmware did not
 *                                                       expose one)
 * The VID / PID sit in the prefix, the instance part after the last backslash.
 */
bool parseUsbInstanceId(const QString &id, quint16 &vid, quint16 &pid,
                        QString &instance)
{
    const QString p = id.toLower();
    if (!p.startsWith(QStringLiteral("usb\\vid_")))
        return false;

    int pos = p.indexOf(QLatin1String("vid_"));
    if (pos < 0)
        return false;
    vid = static_cast<quint16>(p.mid(pos + 4, 4).toUShort(nullptr, 16));

    pos = p.indexOf(QLatin1String("pid_"));
    if (pos < 0)
        return false;
    pid = static_cast<quint16>(p.mid(pos + 4, 4).toUShort(nullptr, 16));

    instance = p.mid(p.lastIndexOf(QLatin1Char('\\')) + 1);
    return true;
}

/* Extract the port name from the friendly name, e.g.
 * "USB Serial Device (COM5)" or "USB 串行设备 (COM5)" -> "COM5" */
QString comPortFromFriendlyName(const QString &friendly)
{
    const QRegularExpression re(QStringLiteral("\\((COM\\d+)\\)"));
    const QRegularExpressionMatch match = re.match(friendly);
    return match.hasMatch() ? match.captured(1) : QString();
}

/* Natural COM port ordering: COM2 before COM10 */
bool comPortLess(const Ch375DeviceInfo &a, const Ch375DeviceInfo &b)
{
    const int numA = a.comPort.mid(3).toInt();
    const int numB = b.comPort.mid(3).toInt();
    if (numA != numB)
        return numA < numB;
    return a.comPort < b.comPort;
}

} // namespace

QList<Ch375DeviceInfo> serialdev_enum_devices(QString &errorMessage)
{
    QList<Ch375DeviceInfo> list;
    errorMessage.clear();

#ifndef Q_OS_WIN
    errorMessage = QCoreApplication::translate(
        "SerialDev", "Serial port enumeration is only supported on Windows");
    return list;
#else
    HDEVINFO devInfo = ::SetupDiGetClassDevsW(&kComPortInterfaceGuid, nullptr, nullptr,
                                              DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (devInfo == INVALID_HANDLE_VALUE) {
        errorMessage = QCoreApplication::translate(
            "SerialDev", "Cannot enumerate the COM ports (error %1)")
                           .arg(::GetLastError());
        return list;
    }

    /*
     * One board shows up as three COM ports (one per CDC channel). The three
     * usbser children share the same parent - the USB composite device - so
     * the parent instance ID is the grouping key. Grouping by parent instead
     * of by serial number keeps working when a firmware build does not expose
     * a serial string (the instance part is a location style id then).
     */
    struct Candidate
    {
        Ch375DeviceInfo info;
        QString parentInstance;
    };
    QList<Candidate> candidates;

    for (DWORD i = 0;; ++i) {
        SP_DEVICE_INTERFACE_DATA interfaceData;
        std::memset(&interfaceData, 0, sizeof(interfaceData));
        interfaceData.cbSize = sizeof(interfaceData);
        if (!::SetupDiEnumDeviceInterfaces(devInfo, nullptr, &kComPortInterfaceGuid,
                                           i, &interfaceData)) {
            if (::GetLastError() == ERROR_NO_MORE_ITEMS)
                break;
            continue;
        }

        DWORD required = 0;
        ::SetupDiGetDeviceInterfaceDetailW(devInfo, &interfaceData, nullptr, 0,
                                           &required, nullptr);
        if (required == 0)
            continue;

        QByteArray detailBuf(int(required), 0);
        auto *detail = reinterpret_cast<SP_DEVICE_INTERFACE_DETAIL_DATA_W *>(
            detailBuf.data());
        detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);

        SP_DEVINFO_DATA devData;
        std::memset(&devData, 0, sizeof(devData));
        devData.cbSize = sizeof(devData);
        if (!::SetupDiGetDeviceInterfaceDetailW(devInfo, &interfaceData, detail,
                                                required, nullptr, &devData))
            continue;

        /* The USB composite device this COM port belongs to */
        DEVINST parent = 0;
        if (::CM_Get_Parent(&parent, devData.DevInst, 0) != CR_SUCCESS)
            continue;
        wchar_t parentId[MAX_DEVICE_ID_LEN + 1];
        if (::CM_Get_Device_IDW(parent, parentId, MAX_DEVICE_ID_LEN, 0) != CR_SUCCESS)
            continue;

        quint16 vid = 0;
        quint16 pid = 0;
        QString instance;
        if (!parseUsbInstanceId(QString::fromWCharArray(parentId), vid, pid, instance))
            continue;
        if (vid != CH32H417_U2U_VID || pid != CH32H417_U2U_PID)
            continue;

        wchar_t friendly[256];
        friendly[0] = L'\0';
        DWORD propSize = sizeof(friendly);
        DWORD propType = 0;
        if (!::SetupDiGetDeviceRegistryPropertyW(devInfo, &devData, SPDRP_FRIENDLYNAME,
                                                 &propType,
                                                 reinterpret_cast<PBYTE>(friendly),
                                                 sizeof(friendly), &propSize))
            continue;

        const QString portName = comPortFromFriendlyName(QString::fromWCharArray(friendly));
        if (portName.isEmpty())
            continue;

        Candidate candidate;
        candidate.info.index = -1;              /* no CH375 index on this channel */
        candidate.info.channel = DeviceChannel::Serial;
        candidate.info.vid = vid;
        candidate.info.pid = pid;
        candidate.info.name = QString::fromWCharArray(friendly);
        /* A genuine USB serial string is hex only; a location style instance
         * id contains '&' and is not worth showing as a serial number */
        candidate.info.serial = instance.contains(QLatin1Char('&')) ? QString() : instance;
        candidate.info.comPort = portName;
        candidate.info.isIap = false;
        candidate.parentInstance = instance;

        /* Keep the lowest numbered COM port of this board */
        Candidate *existing = nullptr;
        for (Candidate &c : candidates) {
            if (c.parentInstance == instance) {
                existing = &c;
                break;
            }
        }
        if (!existing)
            candidates.append(candidate);
        else if (comPortLess(candidate.info, existing->info))
            existing->info = candidate.info;
    }

    ::SetupDiDestroyDeviceInfoList(devInfo);

    for (const Candidate &c : candidates)
        list.append(c.info);
    std::sort(list.begin(), list.end(), comPortLess);

    return list;
#endif /* Q_OS_WIN */
}

bool serialdev_enter_iap(const QString &comPort, QString &errorMessage)
{
    errorMessage.clear();

#ifndef Q_OS_WIN
    Q_UNUSED(comPort)
    errorMessage = QCoreApplication::translate(
        "SerialDev", "Serial port access is only supported on Windows");
    return false;
#else
    const QString fullPath = QStringLiteral("\\\\.\\%1").arg(comPort);

    HANDLE handle = ::CreateFileW(reinterpret_cast<const wchar_t *>(fullPath.utf16()),
                                  GENERIC_READ | GENERIC_WRITE, 0, nullptr,
                                  OPEN_EXISTING, 0, nullptr);
    if (handle == INVALID_HANDLE_VALUE) {
        const DWORD err = ::GetLastError();
        if (err == ERROR_ACCESS_DENIED || err == ERROR_BUSY) {
            errorMessage = QCoreApplication::translate(
                "SerialDev",
                "%1 is open in another program.\n"
                "Close the program (for example a serial terminal) and retry.")
                               .arg(comPort);
        } else {
            errorMessage = QCoreApplication::translate(
                "SerialDev", "Cannot open %1 (error %2)")
                               .arg(comPort).arg(err);
        }
        return false;
    }

    DCB dcb;
    std::memset(&dcb, 0, sizeof(dcb));
    dcb.DCBlength = sizeof(dcb);
    if (!::GetCommState(handle, &dcb)) {
        errorMessage = QCoreApplication::translate(
            "SerialDev", "Cannot query the settings of %1 (error %2)")
                           .arg(comPort).arg(::GetLastError());
        ::CloseHandle(handle);
        return false;
    }

    /*
     * The baud rate is the command: the firmware watches SET_LINE_CODING and
     * reboots into the IAP bootloader when it sees this rate. The port is
     * closed again immediately afterwards.
     */
    dcb.BaudRate = CH32H417_U2U_IAP_BAUD;
    if (!::SetCommState(handle, &dcb)) {
        errorMessage = QCoreApplication::translate(
            "SerialDev", "Cannot set the IAP baud rate on %1 (error %2)")
                           .arg(comPort).arg(::GetLastError());
        ::CloseHandle(handle);
        return false;
    }

    ::CloseHandle(handle);
    return true;
#endif /* Q_OS_WIN */
}
