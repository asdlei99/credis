/********************************************************************
created:	2019-06-12

author:		chensong

purpose:	redis sentinel   

*********************************************************************/
#ifndef _C_REDIS_SENTINEL_H_
#define _C_REDIS_SENTINEL_H_
#include "cnoncopyable.h"
#include "cnet_type.h"
#include <string>
#include <vector>
#include <hiredis.h>

namespace chen {
	class credis_sentinel : private cnoncopyable
	{
	private:
		typedef struct credis_info
		{
			std::string			m_ip;
			uint16				m_port;
			credis_info()
				:m_ip("")
				, m_port(0)
			{}
		};
	public:
		static credis_sentinel * construct();
		static void			destroy(credis_sentinel * sentinel_ptr);
	public:
		explicit credis_sentinel();
		~credis_sentinel();
	public:
		bool init(const char *ip, uint16 port);
		void destroy();
	public:
		const std::string & get_master_ip() const { return m_redis_info[1].m_ip; }
		const uint16 & get_master_port() const { return m_redis_info[1].m_port; }
	private:
		bool _get_redis_master_info();
		void* _command(const char *format, ...);
	private:
		std::vector<credis_info>		m_redis_info;   // 0 : sentinel 1 : master 
		redisContext *					m_sentinel_context;
	};
} // !namespace chen
#endif // !#define _C_REDIS_SENTINEL_H_