#pragma once

#include <atomic>
#include <mutex>
#include <cstring>
#include <shared_mutex>
#include "NonCopyable.h"

namespace sb_spi
{
	//
	// Configuration value - interface implemented by all final types of values.
	//
	class ConfigValue : public NonCopyable
	{
	public:
		constexpr ConfigValue(const char* name);
		virtual ~ConfigValue() = default;

		virtual int getString(char* buf, size_t capacity) const = 0;
		virtual void setString(const char* value) = 0;
		virtual int getInt() const = 0;
		virtual void setInt(int value) = 0;
		virtual unsigned long long getUllong() const = 0;
		virtual void setUllong(unsigned long long value) = 0;
		virtual float getFloat() const = 0;
		virtual void setFloat(float value) = 0;
		virtual double getDouble() const = 0;
		virtual void setDouble(double value) = 0;
		virtual bool getBool() const = 0;
		virtual void setBool(bool value) = 0;

		const char* name();

	private:
		const char* _name;
	};

	//
	// Int value
	//
	class IntValue final : public ConfigValue
	{
	public:
		IntValue(const char* name);
		IntValue(const char* name, int value);
		IntValue(const IntValue& src) = delete;
		IntValue(IntValue&& src) = delete;
		virtual ~IntValue();

		IntValue& operator = (const IntValue& src) = delete;
		IntValue& operator = (IntValue&& src) = delete;

		int getString(char* buf, size_t capacity) const override;
		void setString(const char* value) override;
		int getInt() const override;
		void setInt(int value) override;
		unsigned long long getUllong() const override;
		void setUllong(unsigned long long value) override;
		float getFloat() const override;
		void setFloat(float value) override;
		double getDouble() const override;
		void setDouble(double value) override;
		bool getBool() const override;
		void setBool(bool value) override;

		void set(int value)
		{
			_atomic.store(value, std::memory_order_release);
		}

		int get() const
		{
			return _atomic.load(std::memory_order_acquire);
		}

	private:
		std::atomic_int _atomic;
	};

	//
	// Unsigned long long int value
	//
	class UllongValue final : public ConfigValue
	{
	public:
		UllongValue(const char* name);
		UllongValue(const char* name, unsigned long long value);
		UllongValue(const UllongValue& src) = delete;
		UllongValue(UllongValue&& src) = delete;
		virtual ~UllongValue();

		UllongValue& operator = (const UllongValue& src) = delete;
		UllongValue& operator = (UllongValue&& src) = delete;

		int getString(char* buf, size_t capacity) const override;
		void setString(const char* value) override;
		int getInt() const override;
		void setInt(int value) override;
		unsigned long long getUllong() const override;
		void setUllong(unsigned long long value) override;
		float getFloat() const override;
		void setFloat(float value) override;
		double getDouble() const override;
		void setDouble(double value) override;
		bool getBool() const override;
		void setBool(bool value) override;

		void set(unsigned long long value)
		{
			_atomic.store(value, std::memory_order_release);
		}

		unsigned long long get() const
		{
			return _atomic.load(std::memory_order_acquire);
		}

	private:
		std::atomic_ullong _atomic;
	};

	//
	// Double value
	//
	class DoubleValue final : public ConfigValue
	{
	public:
		DoubleValue(const char* name);
		DoubleValue(const char* name, double value);
		DoubleValue(const DoubleValue& src) = delete;
		DoubleValue(DoubleValue&& src) = delete;
		virtual ~DoubleValue();

		DoubleValue& operator = (const DoubleValue& src) = delete;
		DoubleValue& operator = (DoubleValue&& src) = delete;

		int getString(char* buf, size_t capacity) const override;
		void setString(const char* value) override;
		int getInt() const override;
		void setInt(int value) override;
		unsigned long long getUllong() const override;
		void setUllong(unsigned long long value) override;
		float getFloat() const override;
		void setFloat(float value) override;
		double getDouble() const override;
		void setDouble(double value) override;
		bool getBool() const override;
		void setBool(bool value) override;

		void set(double value)
		{
			_atomic.store(value, std::memory_order_release);
		}

		double get() const
		{
			return _atomic.load(std::memory_order_acquire);
		}

	private:
		std::atomic<double> _atomic;
	};

	//
	// Float value
	//
	class FloatValue final : public ConfigValue
	{
	public:
		FloatValue(const char* name);
		FloatValue(const char* name, float value);
		FloatValue(const FloatValue& src) = delete;
		FloatValue(FloatValue&& src) = delete;
		virtual ~FloatValue();

		FloatValue& operator = (const FloatValue& src) = delete;
		FloatValue& operator = (FloatValue&& src) = delete;

		int getString(char* buf, size_t capacity) const override;
		void setString(const char* value) override;
		int getInt() const override;
		void setInt(int value) override;
		unsigned long long getUllong() const override;
		void setUllong(unsigned long long value) override;
		float getFloat() const override;
		void setFloat(float value) override;
		double getDouble() const override;
		void setDouble(double value) override;
		bool getBool() const override;
		void setBool(bool value) override;

		void set(float value)
		{
			_atomic.store(value, std::memory_order_release);
		}

		float get() const
		{
			return _atomic.load(std::memory_order_acquire);
		}

	private:
		std::atomic<float> _atomic;
	};

	//
	// Bool value
	//
	class BoolValue final : public ConfigValue
	{
	public:
		BoolValue(const char* name);
		BoolValue(const char* name, bool value);
		BoolValue(const BoolValue& src) = delete;
		BoolValue(BoolValue&& src) = delete;
		virtual ~BoolValue();

		BoolValue& operator = (const BoolValue& src) = delete;
		BoolValue& operator = (BoolValue&& src) = delete;

		int getString(char* buf, size_t capacity) const override;
		void setString(const char* value) override;
		int getInt() const override;
		void setInt(int value) override;
		unsigned long long getUllong() const override;
		void setUllong(unsigned long long value) override;
		float getFloat() const override;
		void setFloat(float value) override;
		double getDouble() const override;
		void setDouble(double value) override;
		bool getBool() const override;
		void setBool(bool value) override;

		void set(bool value)
		{
			_atomic.store(value, std::memory_order_release);
		}

		bool get() const
		{
			return _atomic.load(std::memory_order_acquire);
		}

	private:
		std::atomic_bool _atomic;
	};

	//
	// Fixed capacity string value
	//
	class StringValue final : public ConfigValue
	{
	public:
		StringValue(const char* name, size_t capacity);
		StringValue(const char* name, size_t capacity, const char* value);
		StringValue(const StringValue& src) = delete;
		StringValue(StringValue&& src) = delete;
		virtual ~StringValue();

		StringValue& operator = (const StringValue& src) = delete;
		StringValue& operator = (StringValue&& src) = delete;

		int getString(char* buf, size_t capacity) const override;
		void setString(const char* value) override;
		int getInt() const override;
		void setInt(int value) override;
		unsigned long long getUllong() const override;
		void setUllong(unsigned long long value) override;
		float getFloat() const override;
		void setFloat(float value) override;
		double getDouble() const override;
		void setDouble(double value) override;
		bool getBool() const override;
		void setBool(bool value) override;

		void set(const char* value);
		int get(char* buf, size_t capacity) const;

		constexpr size_t capacity() const
		{
			return _capacity;
		}

	private:
		mutable std::shared_mutex _mutex;
		const size_t _capacity;
		char* _value;
	};

	//
	// Configuration interface
	//
	class Configuration : public NonCopyable
	{
	public:
		virtual bool add(ConfigValue& value) = 0;
		virtual bool remove(ConfigValue& value) = 0;

		virtual int getString(const char* name, char* dest, size_t capacity) const = 0;
		virtual void setString(const char* name, const char* value) = 0;

		virtual int getInt(const char* name) const = 0;
		virtual void setInt(const char* name, int value) = 0;

		virtual unsigned long long getUllong(const char* name) const = 0;
		virtual void setUllong(const char* name, unsigned long long value) = 0;

		virtual float getFloat(const char* name) const = 0;
		virtual void setFloat(const char* name, float value) = 0;

		virtual double getDouble(const char* name) const = 0;
		virtual void setDouble(const char* name, double value) = 0;

		virtual bool getBool(const char* name) const = 0;
		virtual void setBool(const char* name, bool value) = 0;
	};

	//
	// Persisted configuration interface
	//
	class PersistedConfiguration : public Configuration
	{
	public:
		virtual void persist(const char* name) const = 0;
		virtual void load(const char* name) = 0;
	};
}