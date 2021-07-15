@echo off
set SOURCE=main.cpp
set EXECUTABLE=main.exe

if "%2" == "" (goto compile)

set SOURCE=%1
set EXECUTABLE=%2

:compile
cl /I . %SOURCE% /link /LIBPATH:.\lib sfml-audio.lib sfml-graphics.lib sfml-system.lib sfml-window.lib user32.lib kernel32.lib /out:.\%EXECUTABLE%