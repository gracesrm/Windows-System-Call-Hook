powershell -Command "(gc C:\WinDDK\7600.16385.1\src\CR0HookTest\CR0HookTest\hook.c) -replace '%1','%2' | Set-Content C:\WinDDK\7600.16385.1\src\CR0HookTest\CR0HookTest\hook.c"