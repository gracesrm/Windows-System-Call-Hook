REM pnputil -a "c:\CR0HookTest_01_23_06\Win7Debug\CR0HookTest Package\CR0HookTest.inf"
REM Runas /profile /user:ruimin\administrator C:\WinDDK\7600.16385.1\bin\selfsign\inf2cat /driver:"C:\WinDDK\7600.16385.1\src\CR0HookTest\Win7Debug\CR0HookTest Package" /os:7_x86
REM Runas /profile /user:ruimin\administrator C:\WinDDK\7600.16385.1\bin\x86\signtool sign /s UFCertStore /n "UF - for test use only" /t http://timestamp.verisign.com/scripts/timestamp.dll "C:\WinDDK\7600.16385.1\src\CR0HookTest\Win7Debug\CR0HookTest Package\cr0hooktest.cat"

C:\WinDDK\7600.16385.1\bin\selfsign\inf2cat /driver:"C:\WinDDK\7600.16385.1\src\CR0HookTest\Win7Debug\CR0HookTest Package" /os:7_x86
C:\WinDDK\7600.16385.1\bin\x86\signtool sign /s CertStore /n "University - for test use only" /t http://timestamp.verisign.com/scripts/timestamp.dll "C:\WinDDK\7600.16385.1\src\CR0HookTest\Win7Debug\CR0HookTest Package\cr0hooktest.cat"
timeout 5
C:\WinDDK\7600.16385.1\tools\devcon\i386\devcon.exe install "C:\WinDDK\7600.16385.1\src\CR0HookTest\Win7Debug\CR0HookTest Package\CR0HookTest.inf" ROOT\CR0HookTest