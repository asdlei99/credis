#include "ccfg.h"
#include <fstream>
#include "clog.h"

namespace chen {

	ccfg::ccfg():m_configs(NULL), m_values_size(0)
	{
	}


	ccfg::~ccfg()
	{
	}

	bool ccfg::init(int64 max_num, const char * file_name)
	{
		if (max_num < 1 || !file_name )
		{
			ERROR_EX_LOG(" m_config max num = %ld, cfg file ptr= NULL \n", max_num);
			return false;
		}

		if (!m_read_cfg.init(file_name))
		{
			return false;
		}
		m_configs = new cnode[max_num];
		if (!m_configs)
		{
			ERROR_EX_LOG("alloc m_config max num = %lu\n", max_num);
			return false;
		}
		

		m_values_size = max_num;

	}

	void ccfg::destroy()
	{
	}

	void ccfg::set_string(int64 key_num,const std::string key, std::string value)
	{
		if (m_values_size < key_num)
		{
			ERROR_EX_LOG("set_string max_num = %ld, num = %ld, key = %s, value = %s\n", m_values_size, key_num, key.c_str(), value.c_str());
			return;
		}
		m_configs[key_num].init(key, EDataTypeString);
		m_configs[key_num].m_data = value;
	}

	void ccfg::set_int32(int64 key_num, const std::string key, int32 value)
	{
		if (m_values_size < key_num)
		{
			ERROR_EX_LOG("set_int32 max_num = %ld, num = %ld, key = %s, value = %d\n", m_values_size, key_num, key.c_str(), value);
			return;
		}
		m_configs[key_num].init(key, EDataTypeString);
		m_configs[key_num].m_int32 = value;
	}

	void ccfg::set_uint32(int64 key_num, const std::string key, uint32 value)
	{
		if (m_values_size < key_num)
		{
			ERROR_EX_LOG("set_uint32 max_num = %ld, num = %ld, key = %s, value = %ld\n", m_values_size, key_num, key.c_str(), value);
			return;
		}
		m_configs[key_num].init(key, EDataTypeString);
		m_configs[key_num].m_uint32 = value;
	}

	void ccfg::set_string(int64 key_num, int32, const char * key, const char * value)
	{
		if (m_values_size < key_num)
		{
			ERROR_EX_LOG("set_string max_num = %ld, num = %ld, key = %s, value = %s\n", m_values_size, key_num, key, value);
			return;
		}
		m_configs[key_num].init(key, EDataTypeString);
		m_configs[key_num].m_data = value;
	}

	void ccfg::set_int32(int64 key_num, const char * key, int32 value)
	{
		if (m_values_size < key_num)
		{
			ERROR_EX_LOG("set_int32 max_num = %ld, num = %ld, key = %s, value = %d\n", m_values_size, key_num, key, value);
			return;
		}
		m_configs[key_num].init(key, EDataTypeString);
		m_configs[key_num].m_int32 = value;
	}

	void ccfg::set_uint32(int64 key_num, const char * key, uint32 value)
	{
		if (m_values_size < key_num)
		{
			ERROR_EX_LOG("set_uint32 max_num = %ld, num = %ld, key = %s, value = %ld\n", m_values_size, key_num, key, value);
			return;
		}
		m_configs[key_num].init(key, EDataTypeString);
		m_configs[key_num].m_uint32 = value;
	}

	std::string ccfg::get_string(int64 key_num)
	{
		if (m_values_size < key_num)
		{
			ERROR_EX_LOG("get_string max_num = %ld, num = %ld\n", m_values_size, key_num);
			return "";
		}
		return m_configs[key_num].m_data;
	}

	int32 ccfg::get_int32(int64 key_num)
	{
		if (m_values_size < key_num)
		{
			ERROR_EX_LOG("get_int32 max_num = %ld, num = %ld\n", m_values_size, key_num);
			return 0;
		}
		return m_configs[key_num].m_int32;
	}

	uint32 ccfg::get_uint32(int64 key_num)
	{
		if (m_values_size < key_num)
		{
			ERROR_EX_LOG("get_int32 max_num = %ld, num = %ld\n", m_values_size, key_num);
			return 0;
		}
		return m_configs[key_num].m_uint32;
	}

	void ccfg::cfg_data()
	{
		for (int64 i = 0; i < m_values_size; ++i)
		{
			if (m_read_cfg.is_key(m_configs[i].m_name))
			{
				if (m_configs[i].m_type == EDataTypeNULL)
				{
					ERROR_EX_LOG(" i = %ld, type = null , name = %s\n", i, m_configs[i].m_name.c_str());
				}
				else if (m_configs[i].m_type == EDataTypeString)
				{
					m_configs[i].m_data = m_read_cfg.get_value(m_configs[i].m_name);
				}
				else if (m_configs[i].m_type == EDataTypeint)
				{
					m_configs[i].m_int32 = std::atoi(m_read_cfg.get_value(m_configs[i].m_name).c_str());
				}
				else if (m_configs[i].m_type == EDataTypeint)
				{
					m_configs[i].m_uint32 = std::atol(m_read_cfg.get_value(m_configs[i].m_name).c_str());
				}
				else
				{
					ERROR_EX_LOG(" i = %ld, type = is not find , name = %s\n", i, m_configs[i].m_name.c_str());
				}
			}
		}
		m_read_cfg.destroy();
	}

	cread_cfg::cread_cfg()
	{
	}

	cread_cfg::~cread_cfg()
	{
	}

	bool cread_cfg::init(const char * file_name)
	{

		std::ifstream  input(file_name);
		if (!input)
		{
			ERROR_EX_LOG("open config file fail file = %s\n", file_name);
			return false;
		}
		std::string line, key, value;
		while (getline(input, line))
		{
			if (_parser_line(line, key, value))
			{
				_insert_data(key, value);
				//m_configs[1].m_data = value; // 保存到map容器中的方法。
			}
		}
		if (input)
		{
			input.close();
		}
		return true;
	}

	void cread_cfg::destroy()
	{
		m_config_map.clear();
	}


	bool cread_cfg::_parser_line(const std::string & line, std::string & key, std::string & value)
	{
		if (line.empty())
		{
			return false;
		}
		int64 start_pos = 0, end_pos = line.size() - 1, pos;
		if ((pos = line.find('#')) != std::string::npos)
		{
			if (pos == 0)
			{
				return false;// #line---
			}
			end_pos = pos - 1;
		}

		std::string new_line = line.substr(start_pos, end_pos - start_pos + 1); // 删掉后半部分的注释 FIX_ME： 这里应该是减错了吧
																				// 下面pos的赋值时必要的，这样，就可在后面得到Key和value值了。
		if ((pos = new_line.find("=")) == std::string::npos) //说明前面没有 = 号
		{
			return false;
		}
		key = new_line.substr(0, pos); // 获得key
		value = new_line.substr(pos + 1, end_pos + 1 - (pos + 1)); // 获得value
		_trim(key);
		if (key.empty())
		{
			return false;
		}
		_trim(value); // 因为这里的key和value都是引用传递，可以直接被修改，所以不用返回
		return true;
	}


	bool cread_cfg::_is_space(char c)
	{
		if (c == ' ' || c == '\t')
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}

	bool cread_cfg::_iscommentchar(char c)
	{
		if (c == '#')
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}

	void cread_cfg::_trim(std::string & str)
	{
		if (str.empty())
		{
			return;
		}
		int i, start_pos, end_pos;
		for (i = 0; i < str.size(); i++)
		{
			if (!_is_space(str[i]))
			{
				break;
			}
		}
		if (i == str.size())
		{
			str = "";
			return;
		}
		start_pos = i; // 获取到非空格的初始位置

		for (i = str.size() - 1; i >= 0; i--)
		{
			if (!_is_space(str[i]))
			{
				break;
			}
		}
		end_pos = i;
		str = str.substr(start_pos, end_pos - start_pos + 1);
	}



	bool cread_cfg::is_key(const std::string & key) const
	{
		CCONFIG_MAP::const_iterator iter = m_config_map.find(key);
		if (iter != m_config_map.end())
		{
			return true;
		}
		return false;
	}

	std::string  cread_cfg::get_value(const std::string & key)
	{
		// TODO: 在此处插入 return 语句
		CCONFIG_MAP::const_iterator iter = m_config_map.find(key);
		if (iter != m_config_map.end())
		{
			return iter->second;
		}
		return NULL;
	}

	void cread_cfg::_insert_data(const std::string & key, const std::string & value)
	{
		if (!m_config_map.insert(std::make_pair(key, value)).second)
		{
			ERROR_EX_LOG("read cfg insert  key = %s, value = %s\n", key.c_str(), value.c_str());
		}
	}
}//namespace chen
