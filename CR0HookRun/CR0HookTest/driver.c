#include "util.h"

#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, OnUnload)


VOID OnUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING deviceNameUnicode;
	
	unhook_ssdt_entries_7();
	removeIrp(DriverObject);
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT theDriverObject, IN PUNICODE_STRING theRegistryPath){

	//**********************
	NTSTATUS status = InitIrpCallBack(theDriverObject);

	//*********************
	theDriverObject->DriverUnload  = OnUnload; 

	oldNtMapViewOfSection = NULL;
	oldNtSetContextThread = NULL;
	oldNtCreateThread = NULL;
	oldNtQueueApcThread = NULL;
	oldNtCreateProcess = NULL;
	oldNtSystemDebugControl = NULL;
	oldNtCreateProcessEx = NULL;
	oldNtWriteVirtualMemory = NULL;
	oldNtDebugActiveProcess = NULL;
	oldNtOpenProcess = NULL;
	oldNtOpenThread = NULL;
	oldNtQuerySystemInformation = NULL;
	oldNtCreateFile = NULL;
	oldNtReadFile = NULL;
	oldNtWriteFile = NULL;
	oldNtDeleteFile = NULL;
	oldNtSetInformationFile = NULL;
	oldNtQueryInformationFile = NULL;
	oldNtCreateMutant = NULL;
	oldNtDeviceIoControlFile = NULL;
	oldNtTerminateProcess = NULL;
	oldNtDelayExecution = NULL;
	oldNtQueryValueKey = NULL;
	oldNtQueryAttributesFile = NULL;
	oldNtReadVirtualMemory = NULL;
	oldNtResumeThread = NULL;
	oldNtCreateSection = NULL;
	oldNtUserCallOneParam = NULL;
	oldNtUserCallNoParam = NULL;
	oldNtClose = NULL;
	oldNtOpenFile = NULL;
	
	//added 
	oldNtNotifyChangeMultipleKeys = NULL;
	oldNtQueryMultipleValueKey = NULL;
	oldNtQueryObject = NULL;
	oldNtQueryPerformanceCounter = NULL;
	oldNtRenameKey = NULL;
	oldNtSetInformationKey = NULL;
	oldNtAllocateLocallyUniqueId = NULL;
	oldNtAllocateVirtualMemory = NULL;
	oldNtCreateDirectoryObject = NULL;
	oldNtCreateEvent = NULL;
	oldNtCreateKey = NULL;
	oldNtCreateKeyTransacted = NULL;
	oldNtDeleteKey = NULL;
	oldNtDeleteValueKey = NULL;
	oldNtDuplicateObject = NULL;
	oldNtDuplicateToken = NULL;
	oldNtEnumerateKey = NULL;
	oldNtEnumerateValueKey = NULL;
	oldNtFlushBuffersFile = NULL;
	oldNtFlushKey = NULL;
	oldNtFlushVirtualMemory = NULL;
	oldNtFsControlFile = NULL;
	oldNtLoadDriver = NULL;
	oldNtLockFile = NULL;
	oldNtMakeTemporaryObject = NULL;
	oldNtNotifyChangeKey = NULL;
	oldNtOpenDirectoryObject = NULL;
	oldNtOpenEvent = NULL;
	oldNtOpenKey = NULL;
	oldNtOpenKeyEx = NULL;
	oldNtOpenKeyTransacted = NULL;
	oldNtOpenKeyTransactedEx = NULL;
	oldNtOpenProcessTokenEx = NULL;
	oldNtOpenSection = NULL;
	oldNtOpenSymbolicLinkObject = NULL;
	oldNtOpenThreadTokenEx = NULL;
	oldNtPowerInformation = NULL;
	oldNtQueryInformationThread = NULL;
	oldNtQueryDirectoryFile = NULL;
	oldNtQueryEaFile = NULL;
	oldNtQueryFullAttributesFile = NULL;
	oldNtQueryInformationToken = NULL;
	oldNtQueryKey = NULL;
	oldNtQueryObject = NULL;
	oldNtQueryQuotaInformationFile = NULL;
	oldNtQuerySecurityObject = NULL;
	oldNtQuerySymbolicLinkObject = NULL;
	oldNtQueryVirtualMemory = NULL;
	oldNtQueryVolumeInformationFile = NULL;
	oldNtSetEaFile = NULL;
	oldNtSetEvent = NULL;
	oldNtSetInformationThread = NULL;
	oldNtSetInformationToken = NULL;
	oldNtSetInformationVirtualMemory = NULL;
	oldNtSetQuotaInformationFile = NULL;
	oldNtSetSecurityObject = NULL;
	oldNtSetValueKey = NULL;
	oldNtSetVolumeInformationFile = NULL;
	oldNtUnlockFile = NULL;
	oldNtUnmapViewOfSection = NULL;
	oldNtWaitForSingleObject = NULL;
	oldNtAllocateVirtualMemory = NULL;
	oldNtFlushVirtualMemory = NULL;
	oldNtFreeVirtualMemory = NULL;
	oldNtLockVirtualMemory = NULL;
	oldNtProtectVirtualMemory = NULL;
	oldNtQueryVirtualMemory = NULL;
	oldNtUnlockVirtualMemory = NULL;
	oldNtDebugActiveProcess = NULL;
	oldNtFlushInstructionCache = NULL;
	oldNtQueryInformationProcess = NULL;
	oldNtSetInformationProcess = NULL;
	oldNtAlertThread = NULL;
	oldNtCallbackReturn = NULL;
	oldNtGetContextThread = NULL;
	oldNtAlertResumeThread = NULL;
	oldNtContinue = NULL;
	oldNtImpersonateThread = NULL;
	oldNtQueryInformationThread = NULL;
	oldNtRegisterThreadTerminatePort = NULL;
	oldNtSetInformationThread = NULL;
	oldNtSuspendThread = NULL;
	oldNtTerminateThread = NULL;
	oldNtOpenMutant = NULL;
	oldNtQueryMutant = NULL;
	oldNtReleaseMutant = NULL;
	oldNtSetTimerResolution = NULL;
	oldNtSetSystemTime = NULL;
	oldNtQueryTimerResolution = NULL;
	oldNtQuerySystemTime = NULL;
	//network
	oldNtAcceptConnectPort = NULL;
	oldNtCompleteConnectPort = NULL;
	oldNtCreatePort = NULL;
	oldNtConnectPort = NULL;
	oldNtImpersonateClientOfPort = NULL;
	oldNtListenPort = NULL;
	oldNtQueryInformationPort = NULL;
	oldNtReadRequestData = NULL;
	oldNtReplyPort = NULL;
	oldNtReplyWaitReceivePort = NULL;
	oldNtReplyWaitReplyPort = NULL;
	oldNtRequestPort = NULL;
	oldNtRequestWaitReplyPort = NULL;
	oldNtWriteRequestData = NULL;

	KeServiceDescriptorTableShadow = getShadowTableAddress();
	if(!KeServiceDescriptorTableShadow){
		#ifdef DEBUG
		DbgPrint("error : couldn't retrieve Shadow SSDT\n");
		#endif
		return STATUS_UNSUCCESSFUL;
	}

	hook_ssdt_entries_7();

	return STATUS_SUCCESS;
}


