/********************************************************************
created:	2019-06-12

author:		chensong

purpose:	redis sentinel

*********************************************************************/
#include "credis_sentinel.h"
#if defined(_MSC_VER)
//#pragma warning(disable:4996)
#include <Windows.h>
#endif // !#if defined(_MSC_VER)
#include "clog.h"
namespace chen {
	credis_sentinel * credis_sentinel::construct()
	{
		return new credis_sentinel();
	}
	void credis_sentinel::destroy(credis_sentinel * sentinel_ptr)
	{
		delete sentinel_ptr;
	}
	credis_sentinel::credis_sentinel()
		:m_sentinel_context(NULL)
	{
	}
	credis_sentinel::~credis_sentinel()
	{
	}
	bool credis_sentinel::init(const char *ip, uint16 port)
	{
		credis_info info;
		info.m_ip = ip;
		info.m_port = port;
		m_redis_info.emplace_back(info);


	/*	m_strIP = ip;
		m_nPort = port;
		m_nTimeout = timeout;*/

		struct timeval tvTimeout;
		tvTimeout.tv_sec = 1500 / 1000;
		tvTimeout.tv_usec = 1500 % 1000 * 1000;

		m_sentinel_context = redisConnectWithTimeout(ip, port, tvTimeout);
		if (m_sentinel_context == NULL || m_sentinel_context->err)
		{
			if (m_sentinel_context)
			{
				ERROR_EX_LOG("redis Connection ip: %s, port: %d error: %s\n", ip, port, m_sentinel_context->errstr);
				//disconnectSvr();
			}
			else
			{
				ERROR_EX_LOG("redis Connection error: can't allocate redis context, ip: %s, port: %d\n", ip, port);
			}
			return false;
		}
		if (!_get_redis_master_info())
		{
			ERROR_LOG("get redis master info error");
			return false;
		}
		
		return true;
	}
	void credis_sentinel::destroy()
	{
		if (m_sentinel_context)
		{
			redisFree(m_sentinel_context);
			m_sentinel_context = NULL;
		}
		m_redis_info.clear();
	}
	bool credis_sentinel::_get_redis_master_info()
	{
		// redis pass
		
		redisReply* reply = static_cast<redisReply*>(_command("SENTINEL get-master-addr-by-name %s", "mymaster"));

		if (reply)
		{
			if (reply->type == REDIS_REPLY_ARRAY)
			{
				credis_info info;
				/*int port = 0;
				std::string strAddrIP;*/
				redisReply* ipElement = reply->element[0];
				if (ipElement && ipElement->type == REDIS_REPLY_STRING)
				{
					info.m_ip = ipElement->str;
					//strAddrIP = "192.168.1.33";
				}

				redisReply* portElement = reply->element[1];
				if (portElement && portElement->type == REDIS_REPLY_STRING)
				{
					info.m_port = std::atoi(portElement->str);
				}

				m_redis_info.emplace_back(info);
				//redisInstance_ = redisConnect(strAddrIP.c_str(), port);
				//if (NULL == redisInstance_ || redisInstance_->err)
				//{
				//	// redis为NULL与redis->err是两种不同的错误，
				//	// 若redis->err为true，可使用redis->errstr查看错误信息
				//	printf("Run Redis: %d %s\n", redisInstance_->err, redisInstance_->errstr);

				//	redisFree(redisInstance_);
				//}
				//else
				//{

				//	redisReply* reply = (redisReply*)redisCommand(redisInstance_, "AUTH %s", chen::g_redis_cfg.get_string(chen::CNG_REDIS_PASSWORD).c_str());
				//	if (reply->type == REDIS_REPLY_ERROR)
				//	{
				//		/* Authentication failed */
				//		printf("Run Redis Error: %s\n", reply->str);
				//	}
				//	else
				//	{
				//		//	bSuccess = true;
				//	}//endi
				//}//endi
			}
			else
			{
				if (reply->type == REDIS_REPLY_ERROR)
				{
					ERROR_LOG("Run Redis  Authentication failed: %s", reply->str);
				}
				ERROR_LOG("Run Redis Error: %d", reply->type);
				freeReplyObject(reply);
				return false;
			}//endi
			freeReplyObject(reply);
		}
		else
		{
			ERROR_LOG("Run Redis Error: %d %s\n", m_sentinel_context->err, m_sentinel_context->errstr);
			return false;
		}//endi
		return true;
	}

	bool credis_sentinel::_get_redis_slave_info()
	{
		return true;
	}

	void * credis_sentinel::_command(const char * format, ...)
	{
		va_list ap;
		void *reply = NULL;

		if (m_sentinel_context)
		{
			va_start(ap, format);
			reply = redisvCommand(m_sentinel_context, format, ap);
			va_end(ap);
		}

		/*	if (NULL == reply)
			{
				if (reConnectSvr())
				{
					va_start(ap, format);
					reply = redisvCommand(m_predisContext, format, ap);
					va_end(ap);
				}
			}*/

		return reply;
	}

}// !namespace chen 