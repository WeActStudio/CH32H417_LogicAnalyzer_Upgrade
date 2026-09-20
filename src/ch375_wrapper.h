/*
 * CH375DLL dynamic loading wrapper.
 *
 * Copyright (C) 2026 WeAct Studio
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Thin wrapper around CH375DLL.DLL.
 *
 * The DLL is loaded at runtime with LoadLibrary()/GetProcAddress(), so no
 * import library (.lib) is required. Only C standard types are used, which
 * keeps the file buildable with mingw-w64 as well as MSVC.
 *
 * The module is fully self-contained: it does not depend on libsigrok or
 * glib. Diagnostic output is delivered through the callback registered with
 * ch375_set_log_func(); when no callback is registered the module is silent.
 */

#ifndef CH375_WRAPPER_H
#define CH375_WRAPPER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * Constants
 * ============================================================================ */

/* CH375 packet length in bytes */
#define CH375_PACKET_LENGTH     64

/* CH375 endpoint addresses */
#define CH375_ENDP_AUX_UP       0x81    /* Interrupt IN endpoint */
#define CH375_ENDP_AUX_DOWN     0x01    /* Auxiliary OUT endpoint */
#define CH375_ENDP_DATA_UP      0x82    /* Bulk data IN endpoint */
#define CH375_ENDP_DATA_DOWN    0x02    /* Bulk data OUT endpoint */

/* Maximum number of devices */
#define CH375_MAX_NUMBER        16

/* Invalid handle value */
#define CH375_INVALID_HANDLE    ((void *)-1)

/* Boolean return values */
#define CH375_TRUE              1
#define CH375_FALSE             0

/* Generic return codes (libsigrok-free replacements of SR_OK / SR_ERR) */
#define CH375_OK                0
#define CH375_ERR               (-1)

/* Device event codes (used by the CH375SetDeviceNotify callback) */
#define CH375_DEVICE_ARRIVAL        3   /* Device plugged in */
#define CH375_DEVICE_REMOVE_PEND    1   /* Device is about to be removed */
#define CH375_DEVICE_REMOVE         0   /* Device removed */

/* Default buffered upload size (1 MB) */
#define CH375_DEFAULT_TRANSFER_SIZE    (1024 * 1024)

/* ============================================================================
 * Log interface
 * ============================================================================ */

/* Log levels */
#define CH375_LOG_ERROR     0
#define CH375_LOG_WARN      1
#define CH375_LOG_INFO      2
#define CH375_LOG_DEBUG     3

/**
 * Log callback type.
 * @param level   Log level, one of the CH375_LOG_* constants.
 * @param message Already formatted, NUL terminated log text.
 */
typedef void (*ch375_log_func_t)(int level, const char *message);

/**
 * Register the log callback.
 * @param func Callback function; pass NULL to disable logging.
 */
void ch375_set_log_func(ch375_log_func_t func);

/* ============================================================================
 * Function pointer types
 * ============================================================================ */

/* Device management */
typedef void* (*CH375OpenDevice_func)(unsigned long iIndex);
typedef void (*CH375CloseDevice_func)(unsigned long iIndex);
typedef unsigned long (*CH375GetVersion_func)(void);
typedef unsigned long (*CH375GetDrvVersion_func)(void);
typedef unsigned long (*CH375GetUsbID_func)(unsigned long iIndex);
typedef void* (*CH375GetDeviceName_func)(unsigned long iIndex);

/* Device descriptors */
typedef int (*CH375GetDeviceDescr_func)(unsigned long iIndex, void *oBuffer, unsigned long *ioLength);
typedef int (*CH375GetConfigDescr_func)(unsigned long iIndex, void *oBuffer, unsigned long *ioLength);

/* Device control */
typedef int (*CH375ResetDevice_func)(unsigned long iIndex);
typedef int (*CH375SetExclusive_func)(unsigned long iIndex, unsigned long iExclusive);

/* Timeout configuration */
typedef int (*CH375SetTimeout_func)(unsigned long iIndex, unsigned long iWriteTimeout, unsigned long iReadTimeout);
typedef int (*CH375SetTimeoutEx_func)(unsigned long iIndex, unsigned long iWriteTimeout, unsigned long iReadTimeout,
                                      unsigned long iAuxTimeout, unsigned long iInterTimeout);

/* Direct write-then-read on endpoint 1 */
typedef int (*CH375WriteRead_func)(unsigned long iIndex, void *iBuffer, void *oBuffer, unsigned long *ioLength);

/* Separate endpoint write / read */
typedef int (*CH375WriteEndP_func)(unsigned long iIndex, unsigned long iEndP, void *iBuffer, unsigned long *ioLength);
typedef int (*CH375ReadEndP_func)(unsigned long iIndex, unsigned long iEndP, void *oBuffer, unsigned long *ioLength);

/* Endpoint control */
typedef int (*CH375AbortEndPRead_func)(unsigned long iIndex, unsigned long iEndP);
typedef int (*CH375AbortEndPWrite_func)(unsigned long iIndex, unsigned long iEndP);
typedef int (*CH375ResetInEndP_func)(unsigned long iIndex, unsigned long iEndP);
typedef int (*CH375ResetOutEndP_func)(unsigned long iIndex, unsigned long iEndP);

/* Data endpoint read / write */
typedef int (*CH375ReadData_func)(unsigned long iIndex, void *oBuffer, unsigned long *ioLength);
typedef int (*CH375WriteData_func)(unsigned long iIndex, void *iBuffer, unsigned long *ioLength);
typedef int (*CH375AbortRead_func)(unsigned long iIndex);
typedef int (*CH375AbortWrite_func)(unsigned long iIndex);

/* Buffered upload mode */
typedef int (*CH375SetBufUpload_func)(unsigned long iIndex, unsigned long iEnableOrClear);
typedef long (*CH375QueryBufUpload_func)(unsigned long iIndex);
typedef int (*CH375SetBufUploadEx_func)(unsigned long iIndex, unsigned long iEnableOrClear,
                                        unsigned long iEndP, unsigned long TransferSize);
typedef int (*CH375QueryBufUploadEx_func)(unsigned long iIndex, unsigned long iEndP,
                                          unsigned long *oTransferCount, unsigned long *oTotalDataLen);
typedef int (*CH375ClearBufUpload_func)(unsigned long iIndex, unsigned long iEndP);

/* Buffered download mode */
typedef int (*CH375SetBufDownload_func)(unsigned long iIndex, unsigned long iEnableOrClear);
typedef long (*CH375QueryBufDownload_func)(unsigned long iIndex);
typedef int (*CH375SetBufDownloadEx_func)(unsigned long iIndex, unsigned long iEnableOrClear,
                                          unsigned long iEndP, unsigned long TransferSize);

/* IO mode configuration */
typedef int (*CH375SetIOMode_func)(unsigned long iIndex, unsigned long iData);

/* Device event notification callback type */
typedef void (*CH375NotifyCallback)(unsigned long iEventStatus);

/* Device event notification */
typedef int (*CH375SetDeviceNotify_func)(unsigned long iIndex, char *iDeviceID, CH375NotifyCallback iNotifyRoutine);

/* CH375 driver command */
typedef int (*CH375DriverCommand_func)(unsigned long iIndex, void *ioCommand);

/* CH375 driver command definitions */
#define mFuncSetIOMode          0x00000012    /* Set IO mode */

/* WIN32 command structure */
#pragma pack(push, 1)
typedef struct _mWIN32_COMMAND {
    unsigned long mFunction;        /* Function code */
    unsigned long mLength;          /* Payload length */
    unsigned char mBuffer[64];      /* Payload buffer */
} mWIN32_COMMAND;
#pragma pack(pop)

/* ============================================================================
 * Wrapper API
 * ============================================================================ */

/* DLL load / unload */
int ch375_init(void);
void ch375_cleanup(void);
int ch375_is_loaded(void);

/**
 * Full path of the CH375 DLL currently loaded, "" when no DLL is loaded.
 * Useful for diagnostics: it shows which copy of CH375DLL was picked up.
 */
const char *ch375_loaded_dll_path(void);

unsigned long ch375_get_version(void);

/* Device management */
void* ch375_open_device(unsigned long index);
void ch375_close_device(unsigned long index);
unsigned long ch375_get_usb_id(unsigned long index);
const char* ch375_get_device_name(unsigned long index);
int ch375_get_device_descr(unsigned long index, void *buffer, unsigned long *length);
int ch375_get_config_descr(unsigned long index, void *buffer, unsigned long *length);
int ch375_reset_device(unsigned long index);

/* Timeout configuration */
int ch375_set_timeout(unsigned long index, unsigned long writeTimeout, unsigned long readTimeout);
int ch375_set_timeout_ex(unsigned long index, unsigned long writeTimeout, unsigned long readTimeout,
                         unsigned long auxTimeout, unsigned long interTimeout);

/* Direct write-then-read on endpoint 1 (command submit / response read back) */
int ch375_write_read(unsigned long index, void *iBuffer, void *oBuffer, unsigned long *ioLength);

/* Separate endpoint write / read; pipe_num is the pipe number (1, 2 or 3) */
int ch375_write_endpoint(unsigned long index, unsigned long pipe_num, void *buffer, unsigned long *length);
int ch375_read_endpoint(unsigned long index, unsigned long pipe_num, void *buffer, unsigned long *length);

/* Endpoint control; pipe_num is the pipe number (1, 2 or 3) */
int ch375_abort_endpoint_read(unsigned long index, unsigned long pipe_num);
int ch375_abort_endpoint_write(unsigned long index, unsigned long pipe_num);
int ch375_reset_in_endpoint(unsigned long index, unsigned long pipe_num);
int ch375_reset_out_endpoint(unsigned long index, unsigned long pipe_num);

/* Buffered upload mode (data transfer on endpoint 2/3); pipe_num is 1, 2 or 3 */
int ch375_set_buf_upload_ex(unsigned long index, unsigned long enable, unsigned long pipe_num, unsigned long transferSize);
int ch375_query_buf_upload_ex(unsigned long index, unsigned long pipe_num, unsigned long *transferCount, unsigned long *totalDataLen);
int ch375_clear_buf_upload(unsigned long index, unsigned long pipe_num);

/* Buffered download mode; pipe_num is the pipe number (1, 2 or 3) */
int ch375_set_buf_download_ex(unsigned long index, unsigned long enable, unsigned long pipe_num, unsigned long transferSize);

/* IO mode: selects whether buffered upload reads/writes are synchronous */
int ch375_set_io_mode(unsigned long index, unsigned long sync);

/* Device event notification: register / unregister the plug-in / plug-out callback */
int ch375_set_device_notify(unsigned long index, char *deviceID, CH375NotifyCallback callback);

/* Data endpoint read / write */
int ch375_read_data(unsigned long index, void *buffer, unsigned long *length);
int ch375_write_data(unsigned long index, void *buffer, unsigned long *length);
int ch375_abort_read(unsigned long index);
int ch375_abort_write(unsigned long index);

#ifdef __cplusplus
}
#endif

#endif /* CH375_WRAPPER_H */
