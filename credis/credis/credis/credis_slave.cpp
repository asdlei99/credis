/********************************************************************
created:	2019-06-11

author:		chensong

purpose:	redis slave

*********************************************************************/
#include "credis_slave.h"

namespace chen {
	credis_slave * credis_slave::construct()
	{
		return new credis_slave();
	}
	void credis_slave::destroy(credis_slave * slave_ptr)
	{
		delete slave_ptr;
	}
	credis_slave::credis_slave()
	{
	}
	credis_slave::~credis_slave()
	{
	}
	bool credis_slave::init()
	{
		return false;
	}
	void credis_slave::destroy()
	{
	}
} // !namespace chen
