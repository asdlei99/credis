/********************************************************************
created:	2019-06-11

author:		chensong

purpose:	redis master

*********************************************************************/
#include "credis_master.h"
#include "clog.h"
#include "credis_cfg.h"

namespace chen {
	credis_master * credis_master::construct()
	{

		return new credis_master();
	}
	void credis_master::destroy(credis_master * master_ptr)
	{
		delete master_ptr;
	}
	credis_master::credis_master()
		: m_ip("")
		, m_port(0)
		, m_master_context(NULL)
	{
	}
	credis_master::~credis_master()
	{
	}
	bool credis_master::init(const char * ip, uint16 port)
	{
		m_ip = ip;
		m_port = port;
		m_master_context = redisConnect(ip, port);
		if (NULL == m_master_context || m_master_context->err)
		{
			// redis为NULL与redis->err是两种不同的错误，
			// 若redis->err为true，可使用redis->errstr查看错误信息
			ERROR_LOG(" connect master ip = %s, port = %d: %d %s", ip, port, m_master_context->err, m_master_context->errstr);
			//redisFree(m_master_context);
			return false;
		}
		else
		{

			redisReply* reply = (redisReply*)redisCommand(m_master_context, "AUTH %s", g_redis_cfg.get_string(chen::CNG_REDIS_PASSWORD).c_str());
			if (reply->type == REDIS_REPLY_ERROR)
			{
				/* Authentication failed */
				ERROR_LOG("Run Redis Authentication failed Error: %s", reply->str);
				return false;
			}
		}
		return true;
	}
	void credis_master::destroy()
	{
		if (m_master_context)
		{
			redisFree(m_master_context);
			m_master_context = NULL;
		}
	}
	bool credis_master::hmsethash(const std::string & data)
	{
		redisReply *reply = static_cast<redisReply*>(_command(data.c_str()));
		if (NULL == reply)									
		{													
			return false;			
		}													
		if (REDIS_REPLY_ERROR == reply->type)
		{
			freeReplyObject(reply);
			return false;
		}
		freeReplyObject(reply);
		return true;
	}
	void * credis_master::_command(const char * format, ...)
	{
		va_list ap;
		void *reply = NULL;

		if (m_master_context)
		{
			va_start(ap, format);
			reply = redisvCommand(m_master_context, format, ap);
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
} // namespace chen


