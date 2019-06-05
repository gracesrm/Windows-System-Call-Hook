REM del "%SystemRoot%\System32\DbgPrintLog.ex_"
REM net stop DbgPrintLog
REM net stop DbgPrnHk
REM ren "%SystemRoot%\System32\DbgPrintLog.exe" DbgPrintLog.ex_
REM del "%SystemRoot%\System32\DbgPrintLog.ex_"
REM copy DbgPrintLog.exe "%SystemRoot%\System32\"
REM copy DbgPrnHk.sys "%SystemRoot%\System32\drivers\"

del DbgPrint.log
TIMEOUT 1
DbgPrintLog.exe
