rem 本机要开放的端口，一般以本机IP的尾号，固定三尾数，
rem 不够三位，后补0，如192.168.1.159，那设置成159,
rem 如果本机IP为192.168.1.31，那设置为%portPre%
set portPre=159


cd /d %~dp0


echo begin stop all the redis as windows service......

redis-sentinel\%portPre%05Stl\redis-stl.exe --service-stop --service-name %portPre%05Stl
%portPre%04Srv\redis-server.exe --service-stop --service-name %portPre%04Srv


echo stop all the redis as windows service finished....



rem 延时5秒,自动关闭窗口
ping -n 5 127.0>nul