
rem 本机IP
set localIp=192.168.1.159

rem 主节点服务器的IP，特别注意,必须配置正确
set masterIp=192.168.1.159

rem 本机要开放的端口前缀，一般以本机IP的尾号，固定三尾数，
rem 不够三位，后补0，如192.168.1.159，那设置成159,
rem 如果本机IP为192.168.1.31，那设置为310
set portPre=161

rem 主节点的端口前缀，特别注意,必须配置正确。详细说明见参数portPre
set masterPortPre=159

rem 你要安装的盘符，可自行配置
set InstallPath=F:\

set sourcePath=%~dp0
cd /d %InstallPath%

mkdir redis-stl
cd redis-stl
mkdir %portPre%04Srv

mkdir redis-sentinel
cd redis-sentinel
mkdir %portPre%05Stl

cd ..


copy %sourcePath%redis-server.exe %portPre%04Srv
copy %sourcePath%redis-server.exe redis-sentinel\%portPre%05Stl

rename redis-sentinel\%portPre%05Stl\redis-server.exe redis-stl.exe


copy %sourcePath%EventLog.dll %portPre%04Srv
copy %sourcePath%EventLog.dll redis-sentinel\%portPre%05Stl

copy %sourcePath%redis.windows-service.conf %portPre%04Srv
copy %sourcePath%redis.windows-service.conf redis-sentinel\%portPre%05Stl

rename %portPre%04Srv\redis.windows-service.conf redis.conf
rename redis-sentinel\%portPre%05Stl\redis.windows-service.conf sentinel.conf

copy %sourcePath%redis.windows-service.conf 
copy %sourcePath%redis-cli.exe 
copy %sourcePath%startAllRedisNodes.bat 
copy %sourcePath%stopAllRedisNodes.bat 
copy %sourcePath%uninstall.bat 

rem 关闭回显
@echo off

rem 定义变量延迟环境
setlocal enabledelayedexpansion
rem 读取所有内容
for /f "eol=* tokens=*" %%i in (%portPre%04Srv\redis.conf) do (
rem 设置变量a为每行内容
set a=%%i
rem 如果该行有123，则将其改为456
set "a=!a:port 6379=port %portPre%04!"
rem 修改绑定的IP
set "a=!a:bind 127.0.0.1=bind %localIp%!"
set "a=!a:dir ./=dir %InstallPath%redis-stl\%portPre%04Srv\!"
set "a=!a:# slaveof <masterip> <masterport>=slaveof %masterIp% %masterPortPre%04!"
echo !a!>>$)
rem 用$的内容替换原来a.txt内容
move $ %portPre%04Srv\redis.conf


rem 以下配置为sentinel的配置
for /f "eol=* tokens=*" %%i in (redis-sentinel\%portPre%05Stl\sentinel.conf) do (
set a=%%i
set "a=!a:# sentinel monitor mymaster 127.0.0.1 6379 2=sentinel monitor mymaster %masterIp% %masterPortPre%04 2!"   
set "a=!a:# sentinel down-after-milliseconds mymaster 5000=sentinel down-after-milliseconds mymaster 5000!"     
set "a=!a:# sentinel parallel-syncs mymaster 1=sentinel parallel-syncs mymaster 1!"     
set "a=!a:# sentinel failover-timeout mymaster 15000=sentinel failover-timeout mymaster 15000!" 
set "a=!a:port 6379=port %portPre%05!"
set "a=!a:bind 127.0.0.1=bind %localIp%!"
set "a=!a:dir ./=dir %InstallPath%redis-stl\redis-sentinel\%portPre%05Stl\!"
echo !a!>>$)
move $ redis-sentinel\%portPre%05Stl\sentinel.conf


@echo on

echo modify redis.conf file finished....
echo begin install redis windows services.....
%portPre%04Srv\redis-server.exe --service-install %InstallPath%redis-stl\%portPre%04Srv\redis.conf --service-name %portPre%04Srv
redis-sentinel\%portPre%05Stl\redis-stl.exe --service-install %InstallPath%redis-stl\redis-sentinel\%portPre%05Stl\sentinel.conf --service-name %portPre%05Stl


echo install redis windows services finished.....

echo begin start all the redis as windows service......
%portPre%04Srv\redis-server.exe --service-start --service-name %portPre%04Srv
redis-sentinel\%portPre%05Stl\redis-stl.exe --service-start --sentinel --service-name %portPre%05Stl

echo start all the redis as windows service finished....

rem 延时10秒,自动关闭窗口
ping -n 10 127.0>nul