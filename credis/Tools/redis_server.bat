@echo off

setlocal

set Dir=%~dp0

@ping -n 1 127.0.0.1>nul
start "sentinel" /D %Dir% %Dir%redis-server.exe ./sentinel/sentinel26379.conf  --sentinel 

@ping -n 1 127.0.0.1>nul
start "master" /D %Dir% %Dir%redis-server.exe ./master/redis6379.conf


@ping -n 1 127.0.0.1>nul
start "slave" /D %Dir% %Dir%redis-server.exe ./slave/redis6380.conf


 
