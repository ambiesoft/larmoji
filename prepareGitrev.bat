setlocal
set APPNAME=larmoji
C:\local\python3\python.exe ..\distSolution\distSolution.py --show-dummygitrev-wchar > "%~dp0%APPNAME%\gitrev.h"
