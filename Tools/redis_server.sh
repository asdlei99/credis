#!/bin/bash


./redis-sentinel ./sentinel/sentinel26379.conf  --sentinel 

./redis-server ./master/redis6379.conf

./redis-server ./slave/redis6380.conf