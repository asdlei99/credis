/********************************************************************
				created:	2019-03-24

				author:		chensong

				purpose:	redis_mgr

*********************************************************************/

#include "credis_mgr.h"
#include "clog.h"
#include <cstring>
#include "credis_cfg.h"

namespace chen {
	credis_mgr	g_redis_mgr;
	static const int BLOB_BUF_SIZE = 2 * 1024 * 1024;

	credis_mgr::credis_mgr()
		: m_redis_sentinel_ptr(NULL)
		, m_redis_master_ptr(NULL)
		, m_redis_slave_ptr(NULL)
		, m_buf(NULL)
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
		m_redis_sentinel_ptr = credis_sentinel::construct();
		if (!m_redis_sentinel_ptr)
		{
			ERROR_LOG(" redis sentinel construct ");
			return false;
		}
		if (!m_redis_sentinel_ptr->init(g_redis_cfg.get_string(CNG_REDIS_IP).c_str(), g_redis_cfg.get_int32(CNG_REDIS_PORT)))
		{
			ERROR_LOG("redis sentinel init error");
			return false;
		}
		m_redis_master_ptr = credis_master::construct();
		if (!m_redis_master_ptr)
		{
			ERROR_LOG(" redis master construct ");
			return false;
		}


		if (!m_redis_master_ptr->init(m_redis_sentinel_ptr->get_master_ip().c_str(), m_redis_sentinel_ptr->get_master_port()))
		{
			ERROR_LOG(" redis master init error ");
			return false;
		}
		m_redis_slave_ptr = credis_slave::construct();
		if (!m_redis_slave_ptr)
		{
			ERROR_LOG(" redis slave construct ");
			return false;
		}
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
		if (m_redis_slave_ptr)
		{
			m_redis_slave_ptr->destroy();
			credis_slave::destroy(m_redis_slave_ptr);
			m_redis_slave_ptr = NULL;
		}
		if (m_redis_master_ptr)
		{
			m_redis_master_ptr->destroy();
			credis_master::destroy(m_redis_master_ptr);
			m_redis_master_ptr = NULL;
		}
		if (m_redis_sentinel_ptr)
		{
			m_redis_sentinel_ptr->destroy();
			credis_sentinel::destroy(m_redis_sentinel_ptr);
			m_redis_sentinel_ptr = NULL;
		}
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
		memset(m_buf, 0, BLOB_BUF_SIZE);
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

	bool credis_mgr::write_master_data(const std::string & data)
	{
		if (!m_redis_master_ptr)
		{
			return false;
		}
		if (!m_redis_master_ptr->hmsethash(data))
		{
			return false;
		}
		return true;
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