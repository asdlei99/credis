/***********************************************************************************************
				created: 		2019-04-27

				author:			chensong

				purpose:		redis_cfg
************************************************************************************************/
#include "credis_cfg.h"

namespace chen {
	credis_cfg g_redis_cfg;
	
	credis_cfg::credis_cfg()
	{
	}


	credis_cfg::~credis_cfg()
	{
	}
	bool credis_cfg::init(const char * file_name)
	{
		if (!cconfig::init(CNG_Max, file_name))
		{
			return false;
		}
		// 默认值
		set_string(CNG_REDIS_IP, "redis_ip", "127.0.0.1");
		set_int32(CNG_REDIS_PORT, "redis_port", 6379);
		set_string(CNG_REDIS_PASSWORD, "redis_password", "cpglive");

		//配置表的值
		load_cfg_file();

		return true;
	}
	void credis_cfg::destroy()
	{
		cconfig::destroy();
	}
}//namespace chen 
