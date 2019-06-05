del "%SystemRoot%\System32\DbgPrintLog.ex_"
net stop DbgPrintLog
net stop DbgPrnHk
ren "%SystemRoot%\System32\DbgPrintLog.exe" DbgPrintLog.ex_
del "%SystemRoot%\System32\DbgPrintLog.ex_"
copy DbgPrintLog.exe "%SystemRoot%\System32\"
copy DbgPrnHk.sys "%SystemRoot%\System32\drivers\"
