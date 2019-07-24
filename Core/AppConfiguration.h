#pragma once

#include <mutex>
#include <unordered_map>
#include <variant>
#include <stdexcept>
#include "PersistedConfiguration.h"

namespace app
{
	class AppConfiguration : public spi::PersistedConfiguration
	{
	public:
		using value_type = std::variant<spi::IntValue, spi::FloatValue, spi::BoolValue, spi::StringValue>;

		AppConfiguration()
		{
		}

		virtual void persist(const std::string& name) const override;
		virtual void load(const std::string& name) override;
		virtual void loadAll(const std::string& name) override;

		virtual void add(const std::string& name, spi::IntValue& value) override;
		virtual void addReadOnly(const std::string& name, const spi::IntValue& value) override;
		virtual void add(const std::string& name, spi::FloatValue& value) override;
		virtual void addReadOnly(const std::string& name, const spi::FloatValue& value) override;
		virtual std::string getString(const std::string& name) const override;
		virtual void setString(const std::string& name, const std::string& value) override;
		virtual int getInt(const std::string& name) const override;
		virtual void setInt(const std::string& name, int value) override;
		virtual float getFloat(const std::string& name) const override;
		virtual void setFloat(const std::string& name, float value) override;
		virtual bool getBool(const std::string& name) const override;
		virtual void setBool(const std::string& name, bool value) override;
		virtual spi::IntValue const* findInt(const std::string& name) const override;
		virtual spi::FloatValue const* findFloat(const std::string& name) const override;
		virtual spi::BoolValue const* findBool(const std::string& name) const override;
		virtual spi::StringValue const* findString(const std::string& name) const override;

	private:
		mutable std::shared_mutex mutex;
		std::unordered_map < std::string, value_type> map;

		template <typename V>
		const V& ref(std::string& name, V const* value) const
		{
			if (value)
			{
				return *value;
			}
			throw std::runtime_error("Not found: " + name);
		}
	};
}