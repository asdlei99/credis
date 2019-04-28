@echo off

setlocal

set Dir=%~dp0


@ping -n 1 127.0.0.1>nul
start "redis-cli" /D %Dir% %Dir%redis-cli.exe -h 127.0.0.1 -p 6379 



 
