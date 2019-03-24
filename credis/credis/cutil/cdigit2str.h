/********************************************************************
created:	2019-03-24

author:		chensong

purpose:	字符串处理工具类

*********************************************************************/
#ifndef _C_DIGIT2STR_H_
#define _C_DIGIT2STR_H_
#include <algorithm>
#include <cstdio>

#ifdef _MSC_VER
#pragma warning (disable:4996)
#endif
namespace chen
{
	//convert int to decimal string, add '\0' at end
	template<typename T>
	int digit2str_dec(char* buf, int buf_size, T value)
	{
		T i = value;
		char* p = buf;
		int num = 0;
		do {
			i /= 10;
			++num;
		} while (i);
		if (num > buf_size)
		{
			return 0;
		}
		i = value;
		do
		{
			*p++ = '0' + (i % 10);
			i /= 10;
		} while (i);

		if (value < 0)
		{
			*p++ = '-';
		}
		*p = '\0';
		std::reverse(buf, p);

		return static_cast<int>(p - buf);
	}
	

}// namespace chen

#endif _C_DIGIT2STR_H_