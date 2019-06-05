REM wmic sysdriver where name="CR0HookTest" delete
REM PNPUTIL -d "CR0HookTest.inf"
start /wait devcon.exe remove ROOT\CR0HookTest
start /wait shutdown.exe /r /t 00