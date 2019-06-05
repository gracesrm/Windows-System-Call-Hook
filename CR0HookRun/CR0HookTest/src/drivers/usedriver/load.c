/**********************************************************************
 * 
 *  Toby Opferman
 *
 *  Example Communicating with a driver
 *
 *  This example is for educational purposes only.  I license this source
 *  out for use in learning how to write a device driver.
 *
 *    
 **********************************************************************/


#include <windows.h>
#include <stdio.h>

/*********************************************************
 *   Main Function Entry
 *
 *********************************************************/
int _cdecl main(void)
{
    HANDLE hFile;
    DWORD dwReturn;

    hFile = CreateFile("\\\\.\\Example", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if(hFile)
    {
        WriteFile(hFile, "Hello from user mode!", sizeof("Hello from user mode!"), &dwReturn, NULL); 
        CloseHandle(hFile);
    }
    
    return 0;
}


