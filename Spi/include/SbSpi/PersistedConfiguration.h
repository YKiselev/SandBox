#pragma once

#include <string>
#include <array>
#include <charconv>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <atomic>
#include <type_traits>
#include <shared_mutex>

namespace sb_spi
{
	namespace traits
	{
		template <typename T>
		constexpr bool isAtomic()
		{
			return std::is_trivially_copyable_v<T> && std::is_copy_constructible_v<T> && std::is_move_constructible_v<T>
				&& std::is_copy_assignable_v<T> && std::is_move_assignable_v<T>;
		}
	}

	template <typename V>
	struct AtomicValue
	{
		using value_type = V;

		AtomicValue()
		{
		}
		AtomicValue(V src)
		{
			set(src);
		}
		AtomicValue(const AtomicValue<V>& src) = delete;
		AtomicValue(AtomicValue<V>&& src) = delete;
		AtomicValue<V>& operator = (const AtomicValue<V>& src) = delete;
		AtomicValue<V>& operator = (AtomicValue<V>&& src) = delete;

		V get() const
		{
			return value.load(std::memory_order::memory_order_acquire);
		}
		void set(const V src)
		{
			value.store(src, std::memory_order::memory_order_release);
		}

	private:
		std::atomic<V> value;
	};

	template <typename V>
	struct LockedValue
	{
		using value_type = std::string;

		LockedValue()
		{
		}
		LockedValue(const V& src)
		{
			set(src);
		}
		LockedValue(const LockedValue<V>& src) = delete;
		LockedValue(LockedValue<V>&& src) = delete;
		LockedValue<V>& operator = (const LockedValue<V>& src) = delete;
		LockedValue<V>& operator = (LockedValue<V>&& src) = delete;

		V get() const
		{
			std::shared_lock lock{ mutex };
			return value;
		}
		void set(const V& src)
		{
			std::unique_lock lock{ mutex };
			value = src;
		}

	private:
		mutable std::shared_mutex mutex;
		V value;
	};

	template <typename V>
	struct Converter
	{
		static std::string toString(V value)
		{
			std::array<char, 48> buf;
			auto [p, ec] = std::to_chars(buf.data(), buf.data() + buf.size(), value);
			if (ec == std::errc())
			{
				return std::string(buf.data(), p - buf.data());
			}
			else
			{
				return "value_too_long";
			}
		}

		static V fromString(const std::string& src)
		{
			if (src.empty())
			{
				return {};
			}
			else
			{
				V result;
				auto ec = std::from_chars(src.data(), src.data() + src.size(), result).ec;
				if (ec == std::errc())
				{
					return result;
				}
				else
				{
					return {};
				}
			}
		}
	};

	template <>
	struct Converter<bool>
	{
		static std::string toString(bool value)
		{
			return value ? "true" : "false";
		}

		static bool fromString(const std::string& src)
		{
			return src == "true";
		}
	};

	template <>
	struct Converter<std::string>
	{
		static std::string& toString(std::string&& value)
		{
			return value;
		}

		static std::string fromString(const std::string& src)
		{
			return std::move(src);
		}
	};

	template <typename V, typename C, typename N>
	struct Value
	{
		using value_type = V;
		using wrapper_type = N;
		using converter_type = C;

		Value()
		{
		}

		Value(V src)
		{
			value.set(src);
		}
		Value(const Value<V, C, N>& src) = delete;
		Value(const Value<V, C, N>&& src) = delete;
		Value<V, C, N> operator = (const Value<V, C, N>& src) = delete;
		Value<V, C, N> operator = (Value<V, C, N>&& src) = delete;

		V get() const
		{
			return value.get();
		}

		void set(V src)
		{
			value.set(src);
		}

		std::string toString() const
		{
			return C::toString(value.get());
		}

		void fromString(const std::string& src)
		{
			value.set(C::fromString(src));
		}

	private:
		N value;
	};

	template <typename T>
	using BaseValue = Value<T, Converter<T>, typename std::conditional<traits::isAtomic<T>(), AtomicValue<T>, LockedValue<T>>::type>;

	using IntValue = BaseValue<int>;
	using FloatValue = BaseValue<float>;
	using BoolValue = BaseValue<bool>;
	using StringValue = BaseValue<std::string>;

	class Configuration
	{
	public:
		virtual ~Configuration() = 0;

		virtual void add(const std::string& name, IntValue& value) = 0;
		virtual void addReadOnly(const std::string& name, const IntValue& value) = 0;

		virtual void add(const std::string& name, FloatValue& value) = 0;
		virtual void addReadOnly(const std::string& name, const FloatValue& value) = 0;

		virtual std::string getString(const std::string& name) const = 0;
		virtual void setString(const std::string& name, const std::string& value) = 0;

		virtual int getInt(const std::string& name) const = 0;
		virtual void setInt(const std::string& name, int value) = 0;

		virtual float getFloat(const std::string& name) const = 0;
		virtual void setFloat(const std::string& name, float value) = 0;

		virtual bool getBool(const std::string& name) const = 0;
		virtual void setBool(const std::string& name, bool value) = 0;

	protected:
		virtual IntValue const* findInt(const std::string& name) const = 0;
		virtual FloatValue const* findFloat(const std::string& name) const = 0;
		virtual BoolValue const* findBool(const std::string& name) const = 0;
		virtual StringValue const* findString(const std::string& name) const = 0;
	};

	class PersistedConfiguration : public Configuration
	{
	public:
		virtual ~PersistedConfiguration() = 0;

		virtual void persist(const std::string& name) const = 0;
		virtual void load(const std::string& name) = 0;
		virtual void loadAll(const std::string& name) = 0;
	};
}