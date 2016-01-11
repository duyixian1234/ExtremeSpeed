@echo off
if NOT exist bin\main.exe call compile.bat
if exist bin\main.exe call bin\main.exe
pause