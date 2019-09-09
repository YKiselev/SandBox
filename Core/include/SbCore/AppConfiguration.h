#pragma once

#include <shared_mutex>
#include <unordered_map>
#include "SbSpi/PersistedConfiguration.h"

namespace app
{
	class AppConfiguration : public sb_spi::PersistedConfiguration
	{
	public:
		AppConfiguration();
		virtual ~AppConfiguration();

		void init();
		void shutdown();

		void persist(const char* name) const override;
		void load(const char* name) override;

		bool add(sb_spi::ConfigValue& value) override;
		bool remove(sb_spi::ConfigValue& value) override;

		int getString(const char* name, char* dest, size_t capacity) const override;
		void setString(const char* name, const char* value) override;
		int getInt(const char* name) const override;
		void setInt(const char* name, int value) override;
		unsigned long long getUllong(const char* name) const override;
		void setUllong(const char* name, unsigned long long value) override;
		float getFloat(const char* name) const override;
		void setFloat(const char* name, float value) override;
		double getDouble(const char* name) const override;
		void setDouble(const char* name, double value) override;
		bool getBool(const char* name) const override;
		void setBool(const char* name, bool value) override;

	private:
		mutable std::shared_mutex _mutex;
		std::unordered_map<std::string, sb_spi::ConfigValue&> _map;
		bool _initialized = false;

		template <typename R, typename...Args>
		R getValue(const char* name, R(sb_spi::ConfigValue::* mf)(Args...)const, Args...args) const;
		template <typename...Args>
		void setValue(const char* name, void(sb_spi::ConfigValue::* mf)(Args...), Args...args);
	};
}