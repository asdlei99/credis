@echo off

setlocal

REM set para=x64\Debug

REM if "%1" NEQ "" set para=%1

set Dir=%~dp0

REM @ping -n 1 127.0.0.1>nul
REM start "credis" /D %Dir% %Dir%credis.exe ..\..\credis.cfg  



REM start redis-server.exe ./sentinel.conf --sentinel
REM start redis-server.exe ./6378.conf
REM start redis-server.exe ./6379.conf


@ping -n 1 127.0.0.1>nul
start "sentinel" /D %Dir% %Dir%redis-server.exe ./sentinel/sentinel26379.conf  --sentinel 

@ping -n 1 127.0.0.1>nul
start "master" /D %Dir% %Dir%redis-server.exe ./master/redis6379.conf


@ping -n 1 127.0.0.1>nul
start "slave" /D %Dir% %Dir%redis-server.exe ./slave/redis6380.conf


 
