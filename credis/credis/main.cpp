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

	g_redis_singleton.setKey("chensong", 8, "chenli", 7);
	char buf[1024];
	g_redis_singleton.getKey("chensong", 8, buf, 1024);
	printf("get key buf value = %s \n", buf);
	chen::g_redis_cfg.destroy();
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}