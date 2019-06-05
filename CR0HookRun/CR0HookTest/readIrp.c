#include "util.h"

#pragma alloc_text (PAGE, IrpCloseCallback) 
#pragma alloc_text (PAGE, IrpReadCallback) 
#pragma alloc_text (PAGE, IrpIoControlCallback) 
#pragma alloc_text (PAGE, IrpCreateCallback)
#pragma alloc_text (PAGE, IrpWriteCallback)

WCHAR deviceNameBuffer[] = L"\\Device\\ComDevice";
WCHAR deviceSymLinkBuffer[] = L"\\DosDevices\\ComDevice";
UNICODE_STRING deviceNameUnicode;
ULONG filterPids[FILTERPIDCNT] = {0};
ULONG strategyPids[FILTERPIDCNT] = {0};
ULONG intrusivePids[FILTERPIDCNT] = {0};

NTSTATUS InitIrpCallBack(IN PDRIVER_OBJECT theDriverObject){
	//**********************
	WDF_DRIVER_CONFIG config;
	NTSTATUS status;
	WDF_OBJECT_ATTRIBUTES attributes;
	UNICODE_STRING deviceSymLinkUnicode;

	RtlInitUnicodeString(&deviceNameUnicode, deviceNameBuffer);
	RtlInitUnicodeString(&deviceSymLinkUnicode, deviceSymLinkBuffer);

	status = IoCreateDevice(theDriverObject, 0,	&deviceNameUnicode, FILE_DEVICE_UNKNOWN, FILE_DEVICE_UNKNOWN, FALSE, &DeviceObject);

	if (!NT_SUCCESS(status)){
		DbgPrint("IO device create error: %d", status);
		return status;
	}

	status = IoCreateSymbolicLink(&deviceSymLinkUnicode, &deviceNameUnicode);

	if (!NT_SUCCESS(status)){
		DbgPrint("IO symbolic link create error: %d", status);
		return status;
	}

	theDriverObject->MajorFunction[IRP_MJ_CLOSE] = IrpCloseCallback;
	//DriverObject->MajorFunction[IRP_MJ_READ] = IrpReadCallback;
	theDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IrpIoControlCallback;
	theDriverObject->MajorFunction[IRP_MJ_CREATE] = IrpCreateCallback;
	// DriverObject->MajorFunction[IRP_MJ_WRITE] = IrpWriteCallback;

	DeviceObject->Flags |= IO_TYPE;
	DeviceObject->Flags &= (~DO_DEVICE_INITIALIZING);
}

VOID removeIrp(IN PDRIVER_OBJECT DriverObject){
	RtlInitUnicodeString(&deviceNameUnicode, deviceNameBuffer);
	IoDeleteSymbolicLink(&deviceNameUnicode);
	IoDeleteDevice(DriverObject->DeviceObject);
}	

BOOLEAN IsStringTerminated(PCHAR pString, unsigned int uiLength, unsigned int *pdwStringLength){
	BOOLEAN bStringIsTerminated = FALSE;
	unsigned int uiIndex = 0;
	*pdwStringLength = 0;

	while (uiIndex < uiLength && bStringIsTerminated == FALSE){
		if (pString[uiIndex] == '\0'){
			*pdwStringLength = uiIndex + 1; /* Include the total count we read, includes the NULL */
			bStringIsTerminated = TRUE;
		}
		else{
			uiIndex++;
		}
	}
	return bStringIsTerminated;
}

NTSTATUS IrpCloseCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp){
	return STATUS_SUCCESS;
}

NTSTATUS IrpReadCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp){
	NTSTATUS status = STATUS_BUFFER_TOO_SMALL;
	PIO_STACK_LOCATION pIoStackIrp = NULL;
	PCHAR pReturnData = "Hello from the Kernel!";  //"Example_ReadBufferedIO - Hello from the Kernel!"
	unsigned int dwDataSize = strlen(pReturnData) + 1; // sizeof("Example_ReadBufferedIO - Hello from the Kernel!");
	unsigned int dwDataRead = 0;
	PCHAR pReadDataBuffer;

	DbgPrint("%s \r\n", pReturnData);
	/*
	* Each time the IRP is passed down the driver stack a new stack location is added
	* specifying certain parameters for the IRP to the driver.
	*/
	pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);

	if (pIoStackIrp){
		pReadDataBuffer = (PCHAR)Irp->AssociatedIrp.SystemBuffer;

		if (pReadDataBuffer && pIoStackIrp->Parameters.Read.Length >= dwDataSize){
			RtlCopyMemory(pReadDataBuffer, pReturnData, dwDataSize);
			dwDataRead = dwDataSize;
			status = STATUS_SUCCESS;
		}
	}

	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = dwDataRead;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}

VOID FilterOutPids(PCHAR pInputBuffer){
	int i = 0, np = 0;
	for(i=0; i< FILTERPIDCNT; i++){
		filterPids[i] = 0;
	}
	for(i=2; i< strlen(pInputBuffer); i++){  // rather than <=
		if(pInputBuffer[i] == ' '){
			np++;
			continue;
		}
		filterPids[np-1] *= 10;
		filterPids[np-1] += (int)(pInputBuffer[i] -'0');
	}
	// Debug Info -- see if filtered pid is correct
	for(i=0; i< FILTERPIDCNT; i++){
		if(filterPids[i] == 0)	return;
		DbgPrint("Filtering pid: %d\r\n", filterPids[i]);
	}
}

VOID StrategyOutPids(PCHAR pInputBuffer){
	int i = 0, np = 0;
	for(i=0; i< FILTERPIDCNT; i++){
		strategyPids[i] = 0;
	}
	for(i=2; i< strlen(pInputBuffer); i++){  // rather than <=
		if(pInputBuffer[i] == ' '){
			np++;
			continue;
		}
		strategyPids[np-1] *= 10;
		strategyPids[np-1] += (int)(pInputBuffer[i] -'0');
	}
	// Debug Info -- see if filtered pid is correct
	for(i=0; i< FILTERPIDCNT; i++){
		if(strategyPids[i] == 0)	return;
		DbgPrint("Strategy pid: %d\r\n", strategyPids[i]);
	}
}

VOID IntrusiveOutPids(PCHAR pInputBuffer){
	int i = 0, np = 0;
	for(i=0; i< FILTERPIDCNT; i++){
		intrusivePids[i] = 0;
	}
	for(i=2; i< strlen(pInputBuffer); i++){  // rather than <=
		if(pInputBuffer[i] == ' '){
			np++;
			continue;
		}
		intrusivePids[np-1] *= 10;
		intrusivePids[np-1] += (int)(pInputBuffer[i] -'0');
	}
	// Debug Info -- see if filtered pid is correct
	for(i=0; i< FILTERPIDCNT; i++){
		if(intrusivePids[i] == 0)	return;
		DbgPrint("Intrusive pid: %d\r\n", intrusivePids[i]);
	}
}

NTSTATUS IrpIoControlCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp){
	NTSTATUS status = STATUS_NOT_SUPPORTED;
	PIO_STACK_LOCATION pIoStackIrp = NULL;
	PCHAR pInputBuffer;
	PCHAR pOutputBuffer;
	unsigned int dwDataRead = 0;
	PCHAR pReturnData = "IOCTL - Buffered I/O From Kernel!";
	unsigned int dwDataSize = strlen(pReturnData) + 1; 
	int i = 0, np = 0; // np: the nth empty char, "-f pid0 pid1"

	pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);

	if (pIoStackIrp){ /* Should Never Be NULL! */
		pInputBuffer = Irp->AssociatedIrp.SystemBuffer;
		pOutputBuffer = Irp->AssociatedIrp.SystemBuffer;

		if (pInputBuffer && pOutputBuffer){
			if (IsStringTerminated(pInputBuffer, pIoStackIrp->Parameters.DeviceIoControl.InputBufferLength, &dwDataRead)){
				//DbgPrint("User Msg: %s\r\n", pInputBuffer);
				if(pInputBuffer[1] == 's'){
					StrategyOutPids(pInputBuffer);
				}else if(pInputBuffer[1] == 'f'){
					FilterOutPids(pInputBuffer);
				}else if(pInputBuffer[1] == 'i'){
					IntrusiveOutPids(pInputBuffer);
				}else{
					DbgPrint("Wrong User Input\r\n");
					status = STATUS_ACCESS_DENIED;
					return status;
				}

				// DbgPrint("%i >= %i", pIoStackIrp->Parameters.DeviceIoControl.OutputBufferLength, dwDataSize);
				//Reply session, send msg to user mode application
				if (pIoStackIrp->Parameters.DeviceIoControl.OutputBufferLength >= dwDataSize){
					RtlCopyMemory(pOutputBuffer, pReturnData, dwDataSize);
					status = STATUS_SUCCESS;
				}
				else{
					status = STATUS_BUFFER_TOO_SMALL;
				}
			}
		}
	}
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = dwDataSize;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS IrpCreateCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp){
	//DbgPrint("IRP MJ CREATE received.");
	return STATUS_SUCCESS;
}

NTSTATUS IrpWriteCallback(PDEVICE_OBJECT DeviceObject, PIRP Irp){
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	PIO_STACK_LOCATION pIoStackIrp = NULL;
	PCHAR pWriteDataBuffer;
	unsigned int dwDataWritten = 0;
	DbgPrint("Example_WriteNeither Called \r\n");

	pIoStackIrp = IoGetCurrentIrpStackLocation(Irp);

	if (pIoStackIrp){
		__try {
			if (Irp->UserBuffer){
				ProbeForRead(Irp->UserBuffer, pIoStackIrp->Parameters.Write.Length, TYPE_ALIGNMENT(char));
				pWriteDataBuffer = Irp->UserBuffer;

				if (IsStringTerminated(pWriteDataBuffer, pIoStackIrp->Parameters.Write.Length, &dwDataWritten)){
					DbgPrint(pWriteDataBuffer);
					status = STATUS_SUCCESS;
				}
			}

		}
		__except (EXCEPTION_EXECUTE_HANDLER){
			status = GetExceptionCode();
		}
	}

	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = dwDataWritten;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}
