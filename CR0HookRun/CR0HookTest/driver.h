#include <fltkernel.h>
#include <ntstrsafe.h>
#include <stddef.h>
#include <wdf.h>
#include <wdm.h>
#include <ntifs.h>
#include <ntddk.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IO_TYPE 0
#define IOCTL_EXAMPLE_SAMPLE_BUFFERED_IO     CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)
#define FILTERPIDCNT 5
#define THRESHOLD 10
#define SLEEPTIME 10
#define MAXSIZE 10000

PDEVICE_OBJECT DeviceObject;

DRIVER_INITIALIZE DriverEntry;

DRIVER_UNLOAD OnUnload;

NTSTATUS IrpCloseCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS IrpReadCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS IrpIoControlCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS IrpCreateCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS IrpWriteCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp);