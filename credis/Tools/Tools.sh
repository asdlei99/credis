#!/bin/bash

#通过sentinel了解master的状态 
sentinel master mymaster 

SENTINEL slaves mymaster 
SENTINEL sentinels mymaster 

#获取当前master的地址 
SENTINEL get-master-addr-by-name mymaster 


#① INFO 
#sentinel的基本状态信息 
#②SENTINEL masters 
#列出所有被监视的主服务器，以及这些主服务器的当前状态 
#③ SENTINEL slaves 
#列出给定主服务器的所有从服务器，以及这些从服务器的当前状态 
#④SENTINEL get-master-addr-by-name 
#返回给定名字的主服务器的 IP 地址和端口号 
#⑤SENTINEL reset 
#重置所有名字和给定模式 pattern 相匹配的主服务器。重置操作清除主服务器目前的所有状态， 包括正在执行中的故障转移， 并移除目前已经发现和关联的， 主服务器的所有从服务器和 Sentinel 。 
#⑥SENTINEL failover 
#当主服务器失效时， 在不询问其他 Sentinel 意见的情况下， 强制开始一次自动故障迁移，但是它会给其他sentinel发送一个最新的配置，其他sentinel会根据这个配置进行更新
