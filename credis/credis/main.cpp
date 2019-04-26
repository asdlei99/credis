#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cnet_type.h"
#include "cnoncopyable.h"
#include "csingleton.h"
#include <hiredis.h>
#ifdef _MSC_VER
#define NO_QFORKIMPL //这一行必须加才能正常使用
#include <win32fixes.h>
//#pragma comment(lib,"hiredis.lib")
//#pragma comment(lib,"Win32_Interop.lib")
#endif // !_MSC_VER
#include <iostream>
#include <string>
#include "credis_mgr.h"
#include "credis_cfg.h"

void redis_cmd()
{
	chen::credis_mgr redis_sql;
	redis_sql.init();
	redis_sql << "chensong";
	std::string name = "chenli";
	redis_sql << name;
	redis_sql << 343;
	redis_sql << "dklf" << 45;
//	redis_sql << 45.5;
	//redis_sql << 3434.3434;
	printf("buf = %s\n", redis_sql.get_buf());
	std::cout << "redis_sql = " << redis_sql.get_buf() << std::endl;
	std::cout << "redis_sql size = " << redis_sql.get_size() << std::endl;
	
}
int main(int argc, char *argv[])
{

	//redis_cmd();

	if (!chen::g_redis_cfg.init(argv[1]))
	{
		system("pause");
		return 1;
	}
	printf("redis ip = %s, port = %d\n", chen::g_redis_cfg.get_string(chen::CNG_REDIS_IP).c_str(),
		chen::g_redis_cfg.get_int32(chen::CNG_REDIS_PORT));
	system("pause");
	unsigned int j;
	redisContext *c;
	redisReply *reply;

	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	c = redisConnectWithTimeout((char*)"192.168.64.136", 6379, timeout);
	if (c->err) {
		printf("Connection error: %s\n", c->errstr);
		exit(1);
	}

	reply = (redisReply *)redisCommand(c, "AUTH 123456");
	printf("AUTH: %s\n", reply->str);
	freeReplyObject(reply);

	/* PING server */
	reply = (redisReply *)redisCommand(c, "PING");
	printf("PING: %s\n", reply->str);
	freeReplyObject(reply);

	/* Set a key */
	reply = (redisReply *)redisCommand(c, "SET %s %s", "foo", "hello world");
	printf("SET: %s\n", reply->str);
	freeReplyObject(reply);

	/* Set a key using binary safe API */
	//reply = (redisReply *)redisCommand(c, "SET %b %b", "bar", 3, "hello", 5);
	//printf("SET (binary API): %s\n", reply->str);
	//freeReplyObject(reply);

	/* Try a GET and two INCR */
	reply = (redisReply *)redisCommand(c, "GET foo");
	printf("GET foo: %s\n", reply->str);
	freeReplyObject(reply);

	reply = (redisReply *)redisCommand(c, "INCR counter");
	printf("INCR counter: %lld\n", reply->integer);
	freeReplyObject(reply);
	/* again ... */
	reply = (redisReply *)redisCommand(c, "INCR counter");
	printf("INCR counter: %lld\n", reply->integer);
	freeReplyObject(reply);

	/* Create a list of numbers, from 0 to 9 */
	reply = (redisReply *)redisCommand(c, "DEL mylist");
	freeReplyObject(reply);
	for (j = 0; j < 10; j++) {
		char buf[64];

		sprintf_s(buf, 64, "%d", j);
		reply = (redisReply *)redisCommand(c, "LPUSH mylist element-%s", buf);
		freeReplyObject(reply);
	}

	/* Let's check what we have inside the list */
	reply = (redisReply *)redisCommand(c, "LRANGE mylist 0 -1");
	if (reply->type == REDIS_REPLY_ARRAY) {
		for (j = 0; j < reply->elements; j++) {
			printf("%u) %s\n", j, reply->element[j]->str);
			getchar();
		}
	}
	freeReplyObject(reply);
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}