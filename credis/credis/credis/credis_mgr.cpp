/********************************************************************
created:	2019-03-24

author:		chensong

purpose:	redis cmd tool

*********************************************************************/

#include "credis_mgr.h"
#include "clog.h"

namespace chen {
	static const int BLOB_BUF_SIZE = 2 * 1024 * 1024;

	credis_mgr::credis_mgr() : m_buf(NULL)
		, m_buf_size(0)
		, m_pos(0)
		, m_error(false)
	{
	}

	credis_mgr::~credis_mgr()
	{
		destroy();
	}

	bool credis_mgr::init()
	{
		m_buf = new char[BLOB_BUF_SIZE];
		if (!m_buf)
		{
			ERROR_EX_LOG("new m_buf failed!");
			return false;
		}
		memset(m_buf, 0, BLOB_BUF_SIZE);
		
		m_buf_size = BLOB_BUF_SIZE;

		return true;
	}

	void credis_mgr::destroy()
	{
		if (m_buf)
		{
			delete[] m_buf;
			m_buf = NULL;
		}
		m_buf_size = 0;
		m_pos = 0;
		m_error = false;
	}

	void credis_mgr::reset()
	{
		m_pos = 0;
		m_error = false;
	}

	void credis_mgr::write(const void * buf, uint32 len)
	{
		if (!m_error && m_pos + len <= m_buf_size)
		{
			memcpy(m_buf + m_pos, buf, len);
			m_pos += len;
			return;
		}
		m_error = true;
	}

	void credis_mgr::write(uint32 pos, const void * buf, uint32 len)
	{
		if (!m_error && pos + len <= m_buf_size)
		{
			memcpy(m_buf + pos, buf, len);
			return;
		}
		m_error = true;
	}

	void credis_mgr::skip(uint32 len)
	{
		if (!m_error && m_pos + len <= m_buf_size)
		{
			m_pos += len;
			return;
		}
		m_error = true;
	}

	void credis_mgr::back(uint32 len)
	{
		if (!m_error && m_pos >= len)
		{
			m_pos -= len;
			return;
		}
		m_error = true;
	}

	credis_mgr & credis_mgr::operator<<(char value)
	{
		if (has_error())
		{
			return *this;
		}
		if (m_pos < m_buf_size)
		{
			m_buf[m_pos++] = value;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(bool value)
	{
		if (value)
		{
			return *this << '1';
		}
		else
		{
			return *this << '0';
		}
	}

	credis_mgr & credis_mgr::operator<<(signed char value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(unsigned char value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(signed short value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(unsigned short value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(signed int value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(unsigned int value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(signed long value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(unsigned long value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(signed long long value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(unsigned long long value)
	{
		// TODO: insert return statement here
		if (has_error())
		{
			return *this;
		}
		int len = digit2str_dec(m_buf + m_pos, m_buf_size - m_pos, value);
		if (len > 0)
		{
			m_pos += len;
		}
		else
		{
			m_error = true;
		}
		return *this;
	}

	//credis_mgr & credis_mgr::operator<<(float value)
	//{
	//	// TODO: insert return statement here
	//	if (has_error())
	//	{
	//		return *this;
	//	}
	//	int len = digit2str_dec<float>(m_buf + m_pos, m_buf_size - m_pos, value);
	//	if (len > 0)
	//	{
	//		m_pos += len;
	//	}
	//	else
	//	{
	//		m_error = true;
	//	}
	//	return *this;
	//}

	//credis_mgr & credis_mgr::operator<<(double value)
	//{
	//	// TODO: insert return statement here
	//	if (has_error())
	//	{
	//		return *this;
	//	}
	//	int len = digit2str_dec<double>(m_buf + m_pos, m_buf_size - m_pos, value);
	//	if (len > 0)
	//	{
	//		m_pos += len;
	//	}
	//	else
	//	{
	//		m_error = true;
	//	}
	//	return *this;
	//}

	credis_mgr & credis_mgr::operator<<(const char * c_str)
	{
		// TODO: insert return statement here
		write(c_str, static_cast<uint32>(strlen(c_str)));
		return *this;
	}

	credis_mgr & credis_mgr::operator<<(const std::string & value)
	{
		// TODO: insert return statement here
		write(value.c_str(), static_cast<uint32>(value.length()));
		return *this;
	}

}