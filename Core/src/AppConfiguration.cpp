
#include "../include/SbCore/AppConfiguration.h"

namespace app
{
	void AppConfiguration::persist(const std::string& name) const
	{
	}

	void AppConfiguration::load(const std::string& name)
	{
	}

	void AppConfiguration::loadAll(const std::string& name)
	{
	}
	void AppConfiguration::add(const std::string& name, sb_spi::IntValue& value)
	{
	}
	void AppConfiguration::addReadOnly(const std::string& name, const sb_spi::IntValue& value)
	{
	}
	void AppConfiguration::add(const std::string& name, sb_spi::FloatValue& value)
	{
	}
	void AppConfiguration::addReadOnly(const std::string& name, const sb_spi::FloatValue& value)
	{
	}
	std::string AppConfiguration::getString(const std::string& name) const
	{
		return std::string();
	}
	void AppConfiguration::setString(const std::string& name, const std::string& value)
	{
	}
	int AppConfiguration::getInt(const std::string& name) const
	{
		return 0;
	}
	void AppConfiguration::setInt(const std::string& name, int value)
	{
	}
	float AppConfiguration::getFloat(const std::string& name) const
	{
		return 0.0f;
	}
	void AppConfiguration::setFloat(const std::string& name, float value)
	{
	}
	bool AppConfiguration::getBool(const std::string& name) const
	{
		return false;
	}
	void AppConfiguration::setBool(const std::string& name, bool value)
	{
	}
	
	sb_spi::IntValue const* AppConfiguration::findInt(const std::string& name) const
	{
		return nullptr;
	}
	
	sb_spi::FloatValue const* AppConfiguration::findFloat(const std::string& name) const
	{
		return nullptr;
	}
	
	sb_spi::BoolValue const* AppConfiguration::findBool(const std::string& name) const
	{
		return nullptr;
	}
	
	sb_spi::StringValue const* AppConfiguration::findString(const std::string& name) const
	{
		return nullptr;
	}
}