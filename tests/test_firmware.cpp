#include "firmwareimage.h"
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <cstdio>

static int failures = 0;

static void check(bool cond, const QString &what)
{
    printf("%s  %s\n", cond ? "[PASS]" : "[FAIL]", what.toLocal8Bit().constData());
    if (!cond)
        failures++;
}

/* Build one HEX record with a correct checksum */
static QString hexRecord(unsigned addr, unsigned type, const QByteArray &data)
{
    unsigned sum = (unsigned)data.size() + ((addr >> 8) & 0xFF) + (addr & 0xFF) + type;
    for (int i = 0; i < data.size(); ++i)
        sum += (unsigned char)data[i];
    const unsigned char cs = (unsigned char)((~sum + 1) & 0xFF);

    QString s = QString(":%1%2%3")
                    .arg((unsigned)data.size(), 2, 16, QChar('0'))
                    .arg(addr, 4, 16, QChar('0'))
                    .arg(type, 2, 16, QChar('0'));
    for (int i = 0; i < data.size(); ++i)
        s += QString("%1").arg((unsigned char)data[i], 2, 16, QChar('0'));
    s += QString("%1").arg((unsigned)cs, 2, 16, QChar('0'));
    return s.toUpper();
}

static bool writeFile(const QString &path, const QByteArray &data)
{
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly))
        return false;
    return f.write(data) == data.size();
}

static QByteArray readFile(const QString &path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly))
        return QByteArray();
    return f.readAll();
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    const QString dir = QDir::tempPath() + "/ch417_fwtest";
    QDir().mkpath(dir);

    /* ---------- Case 1: HEX containing a gap ---------- */
    {
        QByteArray a(16, '\x00');
        for (int i = 0; i < 16; ++i) a[i] = (char)(0x10 + i);
        QByteArray b(4, '\x00');
        for (int i = 0; i < 4; ++i)  b[i] = (char)(0xA0 + i);

        QByteArray upper;
        upper.append((char)0x08);
        upper.append((char)0x00);

        QStringList lines;
        lines << hexRecord(0x0000, 0x04, upper);   /* extended linear address 0x08000000 */
        lines << hexRecord(0x6000, 0x00, a);       /* 0x08006000 */
        lines << hexRecord(0x6020, 0x00, b);       /* 0x08006020, leaving a 16 byte gap */
        lines << QString(":00000001FF");

        const QString path = dir + "/gap.hex";
        writeFile(path, lines.join("\r\n").toLatin1());

        FirmwareImage img;
        QString err;
        const bool ok = firmware_load(path, 0x08006000u, img, err);
        check(ok, QString("HEX parsed (%1)").arg(err));
        check(img.fromHex, "detected as HEX format");
        check(img.startAddress == 0x08006000u,
              QString("start address = 0x%1").arg(img.startAddress, 8, 16, QChar('0')));
        check(img.data.size() == 36, QString("image size = %1 (expected 36)").arg(img.data.size()));
        check((unsigned char)img.data[0] == 0x10, "first byte = 0x10");
        check((unsigned char)img.data[15] == 0x1F, "byte 16 = 0x1F");
        check((unsigned char)img.data[16] == 0xFF, "gap filled with 0xFF");
        check((unsigned char)img.data[32] == 0xA0, "first byte after the gap = 0xA0");
    }

    /* ---------- Case 2: raw BIN ---------- */
    {
        QByteArray raw(300, '\x00');
        for (int i = 0; i < raw.size(); ++i) raw[i] = (char)i;

        const QString path = dir + "/plain.bin";
        writeFile(path, raw);

        FirmwareImage img;
        QString err;
        const bool ok = firmware_load(path, 0x08006000u, img, err);
        check(ok, QString("BIN parsed (%1)").arg(err));
        check(!img.fromHex, "detected as BIN format");
        check(img.startAddress == 0x08006000u, "BIN uses the given base address");
        check(img.data.size() == 300, QString("BIN size = %1").arg(img.data.size()));
    }

    /* ---------- Case 3: a bad HEX checksum must be rejected ---------- */
    {
        QByteArray a(4, '\x11');
        const QString path = dir + "/bad.hex";
        QString text = hexRecord(0x6000, 0x00, a) + "\r\n:00000001FF";

        /* Corrupt the checksum of the last data record, keeping the line
           structure intact */
        const int csPos = text.indexOf('\n') - 3;   /* [cs1][cs2][\r][\n] */
        text.replace(csPos, 2, "00");

        writeFile(path, text.toLatin1());

        FirmwareImage img;
        QString err;
        const bool ok = firmware_load(path, 0x08006000u, img, err);
        check(!ok, QString("checksum error rejected (%1)").arg(err));
    }

    /* ---------- Case 4: missing file ---------- */
    {
        FirmwareImage img;
        QString err;
        check(!firmware_load(dir + "/no_such_file.bin", 0, img, err), "missing file rejected");
    }

    printf("\n%s\n", failures == 0
                         ? "ALL TESTS PASSED"
                         : QString("%1 TEST(S) FAILED").arg(failures).toLocal8Bit().constData());
    return failures == 0 ? 0 : 1;
}
