/********************************************************************
created:	2019-06-11

author:		chensong

purpose:	redis master

*********************************************************************/
#include "credis_master.h"


namespace chen {
	credis_master * credis_master::construct()
	{

		return new credis_master();
	}
	void credis_master::destroy(credis_master * master_ptr)
	{
		delete master_ptr;
	}
	credis_master::credis_master()
	{
	}
	credis_master::~credis_master()
	{
	}
	bool credis_master::init()
	{
		return false;
	}
	void credis_master::destroy()
	{
	}
} // namespace chen


