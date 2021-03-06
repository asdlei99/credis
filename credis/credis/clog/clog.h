/***********************************************************************************************
				created: 		2019-03-02
	
				author:			chensong
					
				purpose:		log
************************************************************************************************/


#ifndef _C_LOG_H_
#define _C_LOG_H_
#include "cnet_type.h"
#include "cnoncopyable.h"
#include <cstdio>
#include <cstdlib>
#include <string>
namespace chen {


	class clog : private cnoncopyable
	{
	public:
		explicit clog();
		virtual ~clog();
	public:
	   static bool init(const std::string& path, const std::string & name);
	   static void destroy();
	public:
	};









#if defined(_MSC_VER)
#define FUNCTION __FUNCTION__

#elif defined(__GNUC__)
#define FUNCTION __PRETTY_FUNCTION__

#else
#pragma error "unknow platform!!!"

#endif
	
#define NORMAL_LOG(format, ...)		printf(format, ##__VA_ARGS__)
#define ERROR_LOG(format, ...)		printf(format, ##__VA_ARGS__)
#define WARNING_LOG(format, ...)	printf(format, ##__VA_ARGS__)
#define SYSTEM_LOG(format, ...)		printf(format, ##__VA_ARGS__)
#define DEBUG_LOG(format, ...)		printf(format, ##__VA_ARGS__)


#define ERROR_EX_LOG(format, ...)	ERROR_LOG("[%s][%u][ERROR]" format, FUNCTION, __LINE__, ##__VA_ARGS__)
#define WARNING_EX_LOG(format, ...)	ERROR_LOG("[%s][%u][WARNING]" format, FUNCTION, __LINE__, ##__VA_ARGS__)

} // chen

#endif // _C_LOG_H_