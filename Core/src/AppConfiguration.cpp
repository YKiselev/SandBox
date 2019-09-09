
#include "../include/SbCore/AppConfiguration.h"

using ConfigValue = sb_spi::ConfigValue;

namespace app
{
	AppConfiguration::AppConfiguration()
	{
	}
	AppConfiguration::~AppConfiguration()
	{
	}
	void AppConfiguration::init()
	{
		//??????
	}
	void AppConfiguration::shutdown()
	{
		//?????????????
	}
	void AppConfiguration::persist(const char* name) const
	{
		// todo
	}
	void AppConfiguration::load(const char* name)
	{
		// todo
	}
	bool AppConfiguration::add(ConfigValue& value)
	{
		std::lock_guard<std::shared_mutex> lock{ _mutex };
		return _map.insert({ value.name(), value }).second;
	}
	bool AppConfiguration::remove(ConfigValue& value)
	{
		std::lock_guard<std::shared_mutex> lock{ _mutex };
		return 1 == _map.erase(value.name());
	}
	template <typename R, typename...Args>
	R AppConfiguration::getValue(const char* name, R(ConfigValue::* mf)(Args...)const, Args...args) const
	{
		std::shared_lock<std::shared_mutex> lock{ _mutex };
		auto p = _map.find(name);
		if (p != _map.end())
		{
			return std::invoke(mf, p->second, args...);
		}
		return {};
	}
	template <typename...Args>
	void AppConfiguration::setValue(const char* name, void(ConfigValue::* mf)(Args...), Args...args)
	{
		auto p = _map.find(name);
		if (p != _map.end())
		{
			std::invoke(mf, p->second, args...);
		}
	}
	int AppConfiguration::getString(const char* name, char* dest, size_t capacity) const
	{
		return getValue(name, &ConfigValue::getString, dest, capacity);
	}
	void AppConfiguration::setString(const char* name, const char* value)
	{
		setValue(name, &ConfigValue::setString, value);
	}
	int AppConfiguration::getInt(const char* name) const
	{
		return getValue(name, &ConfigValue::getInt);
	}
	void AppConfiguration::setInt(const char* name, int value)
	{
		setValue(name, &ConfigValue::setInt, value);
	}
	unsigned long long AppConfiguration::getUllong(const char* name) const
	{
		return getValue(name, &ConfigValue::getUllong);
	}
	void AppConfiguration::setUllong(const char* name, unsigned long long value)
	{
		setValue(name, &ConfigValue::setUllong, value);
	}
	float AppConfiguration::getFloat(const char* name) const
	{
		return getValue(name, &ConfigValue::getFloat);
	}
	void AppConfiguration::setFloat(const char* name, float value)
	{
		setValue(name, &ConfigValue::setFloat, value);
	}
	double AppConfiguration::getDouble(const char* name) const
	{
		return getValue(name, &ConfigValue::getDouble);
	}
	void AppConfiguration::setDouble(const char* name, double value)
	{
		setValue(name, &ConfigValue::setDouble, value);
	}
	bool AppConfiguration::getBool(const char* name) const
	{
		return getValue(name, &ConfigValue::getBool);
	}
	void AppConfiguration::setBool(const char* name, bool value)
	{
		setValue(name, &ConfigValue::setBool, value);
	}
}