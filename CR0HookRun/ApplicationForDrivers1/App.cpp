#include "App.h"


//int _cdecl main(void)
int _cdecl main(int argc, char *argv[])
{
	HANDLE hFile = NULL;
	DWORD dwReturn;
	char szTemp[256] = { 0 };
	//printf("number of args: %d\n", argc);
	printf(argv[1]);
	hFile = CreateFile("\\\\.\\ComDevice", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile)
	{
		/*WriteFile(hFile, "** Hello from user mode!", sizeof("** Hello from user mode!"), &dwReturn, NULL);
		ReadFile(hFile, &szTemp, 256, &dwReturn, NULL);
		printf(szTemp);
		printf("\n");*/

		ZeroMemory(szTemp, sizeof(szTemp));
		//Prepare for your message here, it can be a pointer of any kind. Great Got it.
		DeviceIoControl(hFile, IOCTL_EXAMPLE_SAMPLE_BUFFERED_IO, argv[1], strlen(argv[1])+1, szTemp, sizeof(szTemp), &dwReturn, NULL);
	    //DeviceIoControl(hFile, IOCTL_EXAMPLE_SAMPLE_BUFFERED_IO, "** Hello from User Mode Buffered I/O", sizeof("** Hello from User Mode Buffered I/O"), szTemp, sizeof(szTemp), &dwReturn, NULL);
		printf(szTemp);
		printf(" sent to kernel\n");


		CloseHandle(hFile);
	}

	return 0;
}