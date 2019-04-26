#ifndef _C_REDIS_CFG_H_
#define _C_REDIS_CFG_H_
#include "ccfg.h"
#include "csingleton.h"
namespace chen {
	enum ECNGIndex
	{
		CNG_REDIS_IP = 0,
		CNG_REDIS_PORT,
		CNG_Max,
	};
	class credis_cfg : public ccfg
	{
	public:
	    explicit	credis_cfg();
		virtual	~credis_cfg();
	public:
		bool init(const char *file_name);
		void destroy();
	};

	extern 	credis_cfg g_redis_cfg;
} //namespace chen

#endif //!#define _C_REDIS_CFG_H_

