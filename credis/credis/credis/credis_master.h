/********************************************************************
created:	2019-06-11

author:		chensong

purpose:	redis master

*********************************************************************/
#ifndef _C_REDIS_MASTER_H_
#define _C_REDIS_MASTER_H_
#include "cnoncopyable.h"


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
		bool init();
		void destroy();
	private:

	};

} // namespace chen


#endif // !#define _C_REDIS_MASTER_H_