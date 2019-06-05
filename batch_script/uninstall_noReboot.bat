REM wmic sysdriver where name="CR0HookTest" delete
REM PNPUTIL -d "CR0HookTest.inf"
devcon.exe remove ROOT\CR0HookTest