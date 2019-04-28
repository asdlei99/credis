/********************************************************************
				created:	2019-03-24

				author:		chensong

				purpose:	redis cmd tool

*********************************************************************/
#ifndef _C_REDIS_MGR_H
#define _C_REDIS_MGR_H
#include "cnoncopyable.h"
#include "cnet_type.h"
#include "cdigit2str.h"
#include <string>

namespace chen
{
	class credis_mgr :public cnoncopyable
	{
	public:
		explicit credis_mgr();
		virtual ~credis_mgr();
	public:
	public:
		bool init();
		void destroy();

	public:
		const char* get_buf() const { return m_buf; }

		uint32 get_size() const { return m_pos; }

		bool has_error() const { return m_error; }

		bool no_error() const { return !has_error(); }

		void reset();

		void write(const void* buf, uint32 len);

		void write(uint32 pos, const void* buf, uint32 len);

		void skip(uint32 len);

		void back(uint32 len);

	public:
		credis_mgr& operator<<(char value);

		credis_mgr& operator<<(bool value);

		credis_mgr& operator<<(signed char value);

		credis_mgr& operator<<(unsigned char value);

		credis_mgr& operator<<(signed short value);

		credis_mgr& operator<<(unsigned short value);

		credis_mgr& operator<<(signed int value);

		credis_mgr& operator<<(unsigned int value);

		credis_mgr& operator<<(signed long value);

		credis_mgr& operator<<(unsigned long value);

		credis_mgr& operator<<(signed long long value);

		credis_mgr& operator<<(unsigned long long value);

		/*credis_mgr& operator<<(float value);

		credis_mgr& operator<<(double value);*/
		//must be zero end string, not write the end 0
		credis_mgr& operator<<(const char* c_str);

		credis_mgr& operator<<(const std::string& value);
	
	private:
		char*			m_buf;
		uint32			m_buf_size;
		uint32			m_pos;
		bool			m_error;
	};
}

#endif // _C_REDIS_MGR_H
