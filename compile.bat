@echo off
:begin
gcc src/display.c  src/game.c  src/main.c  src/messages.c  src/resourse.c  src/timing.c  src/vector.c -o bin\main.exe -Iinclude -Llib  -lglut32
pause
rem goto begin