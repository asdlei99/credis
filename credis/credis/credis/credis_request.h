/********************************************************************
				created:	2019-04-28

				author:		chensong

				purpose:	redis seach

*********************************************************************/
#ifndef _C_REDIS_REQUEST_H_
#define _C_REDIS_REQUEST_H_
#include "cnoncopyable.h"
namespace chen {
	class credis_request : private cnoncopyable
	{
	public:
		credis_request();
		~credis_request();
	public:
		bool init();
		void destroy();
	};
} //namespace chen

#endif //!#define _C_REDIS_REQUEST_H_