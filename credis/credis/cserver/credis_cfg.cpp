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
		if (!ccfg::init(CNG_Max, file_name))
		{
			return false;
		}
		// 默认值
		set_string(CNG_REDIS_IP, "redis_ip", "127.0.0.1");
		set_int32(CNG_REDIS_PORT, "redis_prot", 6379);

		//配置表的值
		cfg_data();

		return true;
	}
	void credis_cfg::destroy()
	{
		ccfg::destroy();
	}
}//namespace chen 
