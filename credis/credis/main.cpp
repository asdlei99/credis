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
#include "credis.h"

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
#ifdef _MSC_VER
		system("pause");
#endif // !_MSC_VER
	
		return 1;
	}
	printf("redis ip = %s, port = %d\n", chen::g_redis_cfg.get_string(chen::CNG_REDIS_IP).c_str(),
		chen::g_redis_cfg.get_int32(chen::CNG_REDIS_PORT));
	
	if (!g_redis_singleton.connectSvr(chen::g_redis_cfg.get_string(chen::CNG_REDIS_IP).c_str(), chen::g_redis_cfg.get_int32(chen::CNG_REDIS_PORT)))
	{
#ifdef _MSC_VER
		system("pause");
#endif // !_MSC_VER
		return -1;
	}
	redisContext * redisInstance_ = NULL;
	// redis pass
	if (chen::g_redis_cfg.get_string(chen::CNG_REDIS_PASSWORD).length() > 1)
	{
		redisReply* reply = static_cast<redisReply*>( g_redis_singleton.command("SENTINEL get-master-addr-by-name %s", "mymaster"));
		
		if (reply)
		{
			if (reply->type == REDIS_REPLY_ARRAY)
			{
				int port = 0;
				std::string strAddrIP;
				redisReply* ipElement = reply->element[0];
				if (ipElement && ipElement->type == REDIS_REPLY_STRING)
				{
					//strAddrIP = ipElement->str;
					strAddrIP = "192.168.1.33";
				}

				redisReply* portElement = reply->element[1];
				if (portElement && portElement->type == REDIS_REPLY_STRING)
				{
					port = std::atoi(portElement->str);
				}

				redisInstance_ = redisConnect(strAddrIP.c_str(), port);
				if (NULL == redisInstance_ || redisInstance_->err)
				{
					// redis为NULL与redis->err是两种不同的错误，
					// 若redis->err为true，可使用redis->errstr查看错误信息
					printf("Run Redis: %d %s\n", redisInstance_->err, redisInstance_->errstr);
					
					redisFree(redisInstance_);
				}
				else
				{
					
					redisReply* reply = (redisReply*)redisCommand(redisInstance_, "AUTH %s", chen::g_redis_cfg.get_string(chen::CNG_REDIS_PASSWORD).c_str());
					if (reply->type == REDIS_REPLY_ERROR) 
					{
						/* Authentication failed */
						printf("Run Redis Error: %s\n", reply->str);
						
					}
					else
					{
					//	bSuccess = true;
					}//endi
				}//endi
			}
			else
			{
				if (reply->type == REDIS_REPLY_ERROR)
				{
					printf( "Run Redis  Authentication failed: %s\n" , reply->str);
				}
				printf("Run Redis Error: %d", reply->type);
			}//endi
			freeReplyObject(reply);
		}
		else
		{
			//printf("Run Redis Error: %d %s\n", sentinelInstance_->err, sentinelInstance_->errstr);
			
		}//endi
		
		
		
		std::string cmd_redis = "hmset wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww:9725 playername huanao006 playertoken b224ff7fe1ffe2a6b714b2257d746b0caa1fba7b playerheardheat 1558275879 playerclientversion 10 playerlanguage 0 playergsid gs device_id E4417401-17B8-4BE6-ABAC-A7C06D739552";


		reply = (redisReply*)redisCommand(redisInstance_, cmd_redis.c_str());
		if (reply->type == REDIS_REPLY_ERROR)
		{
			/* Authentication failed */
			printf("Run Redis Error: %s\n", reply->str);
			printf(" error \n");
			//	//system("pause");
		}
		else
		{
			printf(" ok \n");
			//	//system("pause");
			//	bSuccess = true;
		}//endi
		//if (g_redis_singleton.command(cmd_redis.c_str()))
		//{
		//	printf(" error \n");
		//	//system("pause");

		//}
		
		
		
		
		
		
		
		
		/*if (!g_redis_singleton.command("AUTH %s", chen::g_redis_cfg.get_string(chen::CNG_REDIS_PASSWORD).c_str()))
		{
			system("pause");
			return -1;
		}*/
	}

	//g_redis_singleton.setKey("chensong", 8, "chenli", 7);
	//char buf[1024];
	//g_redis_singleton.getKey("chensong", 8, buf, 1024);
	//char cmd_redis[256]  = "hmset playerLoginSessionProperty:3163 playername 123456 playertoken 587fc1d48933fb84d4ef3445d16afd496d731380 playerheardheat 1558289942 playerclientversion 10 playerlanguage 0 playergsid gs device_id 7a30fcec%2D7ec0%2D4ae6%2D9a8a%2Ddc32299fb977";
	
//	printf("get key buf value = %s \n", buf);
	chen::g_redis_cfg.destroy();
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}




#include<iostream>  
#include<stdio.h>   
using namespace std;
static unsigned char char_to_hex(unsigned char x)
{
	return (unsigned char)(x > 9 ? x + 55 : x + 48);
}

static int is_alpha_number_char(unsigned char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return 1;
	return 0;
}

//url编码实现   

void urlencode(const unsigned char * src, int  src_len, unsigned char * dest, int  dest_len)
{
	unsigned char ch;
	int  len = 0;

	while (len < (dest_len - 4) && *src)
	{
		ch = (unsigned char)*src;
		if (*src == ' ')
		{
			*dest++ = '+';
		}
		else if (is_alpha_number_char(ch) || strchr("=!~*'()", ch))
		{
			*dest++ = *src;
		}
		else
		{
			*dest++ = '%';
			*dest++ = char_to_hex((unsigned char)(ch >> 4));
			*dest++ = char_to_hex((unsigned char)(ch % 16));
		}
		++src;
		++len;
	}
	return;
}



//解url编码实现   

unsigned char* urldecode(unsigned char* encd, unsigned char* decd)
{
	int j, i;
	char *cd = (char*)encd;
	char p[2];
	unsigned int num;
	j = 0;

	for (i = 0; i < strlen(cd); i++)
	{
		memset(p, '/0', 2);
		if (cd[i] != '%')
		{
			decd[j++] = cd[i];
			continue;
		}

		p[0] = cd[++i];
		p[1] = cd[++i];

		p[0] = p[0] - 48 - ((p[0] >= 'A') ? 7 : 0) - ((p[0] >= 'a') ? 32 : 0);
		p[1] = p[1] - 48 - ((p[1] >= 'A') ? 7 : 0) - ((p[1] >= 'a') ? 32 : 0);
		decd[j++] = (unsigned char)(p[0] * 16 + p[1]);

	}

	return decd;
}


int test_main()
{

	std::string str = "7a30fcec%2D7ec0%2D4ae6%2D9a8a%2Ddc32299fb977";
	char buf[256] = {0};
	int buf_len = 256;
	//urlencode((const unsigned char *)str.c_str(), str.length(),(unsigned char *) buf, buf_len);
	std::cout << buf << std::endl;
	char buf2[256] = {0};
	int len_l = 256;
	urldecode(( unsigned char *)str.c_str(), ( unsigned char *)buf2);
	std::cout << buf2 << std::endl;
	urlencode((const unsigned char *)buf2, strlen(buf),(unsigned char *) buf, buf_len);
	std::cout << buf << std::endl;


	return 0;
}