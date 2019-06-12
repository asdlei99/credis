/********************************************************************
created:	2019-06-11

author:		chensong

purpose:	redis master

*********************************************************************/
#ifndef _C_REDIS_MASTER_H_
#define _C_REDIS_MASTER_H_
#include "cnoncopyable.h"
#include "credis_sentinel.h"

namespace chen {
	class credis_master : private cnoncopyable
	{
	public:
		static credis_master * construct();
		static void destroy(credis_master * master_ptr);
	public:
		explicit credis_master();
		~credis_master();
	public:
		bool init(const char * ip ,  uint16 port);
		void destroy();
	public:
		bool hmsethash(const std::string & data);
	private:
		void* _command(const char *format, ...);
	private:
		std::string						m_ip;
		uint16							m_port;
		redisContext *					m_master_context;
	};

} // namespace chen


#endif // !#define _C_REDIS_MASTER_H_