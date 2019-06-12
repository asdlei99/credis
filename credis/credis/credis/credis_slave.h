/********************************************************************
created:	2019-06-11

author:		chensong

purpose:	redis slave

*********************************************************************/
#ifndef _C_REDIS_SLAVE_H_
#define _C_REDIS_SLAVE_H_
#include "cnoncopyable.h"

namespace chen {
	class credis_slave : private cnoncopyable
	{
	public:
		static credis_slave * construct();
		static void			destroy(credis_slave * slave_ptr);
	public:
		explicit credis_slave();
		~credis_slave();
	public:
		bool init();
		void destroy();
	
	private:
	};
} // !namespace chen
#endif // !#define _C_REDIS_SLAVE_H_