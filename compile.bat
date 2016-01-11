@echo off
:begin
gcc src\*.c -o bin\main.exe -Iinclude -Llib -lopengl32 -lglu32 -lglut32
pause
rem goto begin