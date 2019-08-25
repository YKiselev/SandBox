
#include "../include/SbSpi/PersistedConfiguration.h"
#include <cstring>

namespace sb_spi
{
	//
	// IntValue
	//
	IntValue::IntValue()
	{
	}
	IntValue::IntValue(int value)
	{
		set(value);
	}
	IntValue::~IntValue()
	{
	}
	int IntValue::getString(char* buf, size_t capacity) const
	{
		return snprintf(buf, capacity, "%d", get());
	}
	void IntValue::setString(const char* value)
	{
		const long r = strtol(value, nullptr, 0);
		set(static_cast<int>(r));
	}
	int IntValue::getInt() const
	{
		return get();
	}
	void IntValue::setInt(int value)
	{
		set(value);
	}
	unsigned long long IntValue::getUllong() const
	{
		return get();
	}
	void IntValue::setUllong(unsigned long long value)
	{
		set(static_cast<int>(value));
	}
	float IntValue::getFloat() const
	{
		return static_cast<float>(get());
	}
	void IntValue::setFloat(float value)
	{
		set(static_cast<int>(value));
	}
	double IntValue::getDouble() const
	{
		return get();
	}
	void IntValue::setDouble(double value)
	{
		set(static_cast<int>(value));
	}
	bool IntValue::getBool() const
	{
		return get() != 0;
	}
	void IntValue::setBool(bool value)
	{
		set(value ? 1 : 0);
	}

	//
	// UllongValue
	//
	UllongValue::UllongValue()
	{
	}
	UllongValue::UllongValue(unsigned long long value) : _atomic{ value }
	{
	}
	UllongValue::~UllongValue()
	{
	}
	int UllongValue::getString(char* buf, size_t capacity) const
	{
		return snprintf(buf, capacity, "%#llx", get());
	}
	void UllongValue::setString(const char* value)
	{
		set(strtoull(value, nullptr, 0));
	}
	int UllongValue::getInt() const
	{
		return static_cast<int>(get());
	}
	void UllongValue::setInt(int value)
	{
		set(value);
	}
	unsigned long long UllongValue::getUllong() const
	{
		return get();
	}
	void UllongValue::setUllong(unsigned long long value)
	{
		set(value);
	}
	float UllongValue::getFloat() const
	{
		return static_cast<float>(get());
	}
	void UllongValue::setFloat(float value)
	{
		set(static_cast<unsigned long long>(value));
	}
	double UllongValue::getDouble() const
	{
		return static_cast<double>(get());
	}
	void UllongValue::setDouble(double value)
	{
		set(static_cast<unsigned long long>(value));
	}
	bool UllongValue::getBool() const
	{
		return get() != 0;
	}
	void UllongValue::setBool(bool value)
	{
		set(value ? 1 : 0);
	}

	//
	// DoubleValue
	//
	DoubleValue::DoubleValue()
	{

	}
	DoubleValue::DoubleValue(double value) : _atomic{ value }
	{

	}
	DoubleValue::~DoubleValue()
	{

	}
	int DoubleValue::getString(char* buf, size_t capacity) const
	{
		return snprintf(buf, capacity, "%f", get());
	}
	void DoubleValue::setString(const char* value)
	{
		set(strtod(value, nullptr));
	}
	int DoubleValue::getInt() const
	{
		return static_cast<int>(get());
	}
	void DoubleValue::setInt(int value)
	{
		set(value);
	}
	unsigned long long DoubleValue::getUllong() const
	{
		return static_cast<unsigned long long>(get());
	}
	void DoubleValue::setUllong(unsigned long long value)
	{
		set(static_cast<double>(value));
	}
	float DoubleValue::getFloat() const
	{
		return static_cast<float>(get());
	}
	void DoubleValue::setFloat(float value)
	{
		set(value);
	}
	double DoubleValue::getDouble() const
	{
		return get();
	}
	void DoubleValue::setDouble(double value)
	{
		set(value);
	}
	bool DoubleValue::getBool() const
	{
		return get() != 0;
	}
	void DoubleValue::setBool(bool value)
	{
		set(value ? 1 : 0);
	}

	//
	// FloatValue
	//
	FloatValue::FloatValue()
	{
	}
	FloatValue::FloatValue(float value) :_atomic{ value }
	{
	}
	FloatValue::~FloatValue()
	{
	}
	int FloatValue::getString(char* buf, size_t capacity) const
	{
		return snprintf(buf, capacity, "%f", get());
	}
	void FloatValue::setString(const char* value)
	{
		set(strtof(value, nullptr));
	}
	int FloatValue::getInt() const
	{
		return static_cast<int>(get());
	}
	void FloatValue::setInt(int value)
	{
		set(static_cast<float>(value));
	}
	unsigned long long FloatValue::getUllong() const
	{
		return static_cast<unsigned long long>(get());
	}
	void FloatValue::setUllong(unsigned long long value)
	{
		set(static_cast<float>(value));
	}
	float FloatValue::getFloat() const
	{
		return get();
	}
	void FloatValue::setFloat(float value)
	{
		set(value);
	}
	double FloatValue::getDouble() const
	{
		return get();
	}
	void FloatValue::setDouble(double value)
	{
		set(static_cast<float>(value));
	}
	bool FloatValue::getBool() const
	{
		return get() != 0;
	}
	void FloatValue::setBool(bool value)
	{
		set(value ? 1.f : 0.f);
	}

	//
	//
	//
	BoolValue::BoolValue()
	{
	}
	BoolValue::BoolValue(bool value) : _atomic{ value }
	{
	}
	BoolValue::~BoolValue()
	{
	}
	int BoolValue::getString(char* buf, size_t capacity) const
	{
		return snprintf(buf, capacity, "%s", get() ? "yes" : "no");
	}
	void BoolValue::setString(const char* value)
	{
		const size_t len = strlen(value);
		set(len == 3 && (value[0] == 'y' || value[0] == 'Y') && (value[1] == 'e') && (value[2] == 's'));
	}
	int BoolValue::getInt() const
	{
		return get() ? 1 : 0;
	}
	void BoolValue::setInt(int value)
	{
		set(value != 0);
	}
	unsigned long long BoolValue::getUllong() const
	{
		return get() ? 1 : 0;
	}
	void BoolValue::setUllong(unsigned long long value)
	{
		set(value != 0);
	}
	float BoolValue::getFloat() const
	{
		return get() ? 1.f : 0.f;
	}
	void BoolValue::setFloat(float value)
	{
		set(value != 0);
	}
	double BoolValue::getDouble() const
	{
		return get() ? 1.0 : 0.0;
	}
	void BoolValue::setDouble(double value)
	{
		set(value != 0);
	}
	bool BoolValue::getBool() const
	{
		return get();
	}
	void BoolValue::setBool(bool value)
	{
		set(value);
	}

	//
	// StringValue
	//
	StringValue::StringValue(size_t capacity) : _capacity{ capacity }, _value{ new char[capacity] }
	{
		set("");
	}
	StringValue::StringValue(size_t capacity, const char* value) : StringValue(capacity)
	{
		set(value);
	}
	StringValue::~StringValue()
	{
		delete[] _value;
	}
	int StringValue::getString(char* buf, size_t capacity) const
	{
		return get(buf, capacity);
	}
	void StringValue::setString(const char* value)
	{
		set(value);
	}
	int StringValue::getInt() const
	{
		return 0;
	}
	void StringValue::setInt(int value)
	{
		// no-op
	}
	unsigned long long StringValue::getUllong() const
	{
		return 0;
	}
	void StringValue::setUllong(unsigned long long value)
	{
		// no-op
	}
	float StringValue::getFloat() const
	{
		return 0;
	}
	void StringValue::setFloat(float value)
	{
		// no-op
	}
	double StringValue::getDouble() const
	{
		return 0;
	}
	void StringValue::setDouble(double value)
	{
		// no-op
	}
	bool StringValue::getBool() const
	{
		return false;
	}
	void StringValue::setBool(bool value)
	{
		// no-op
	}
	void StringValue::set(const char* value)
	{
		const size_t req = strlen(value);
		const size_t count = req < _capacity ? req : _capacity - 1;
		{
			std::lock_guard<std::shared_mutex> lock{ _mutex };
			strncpy(_value, value, count);
			_value[count] = 0;
		}
	}

	int StringValue::get(char* buf, size_t capacity) const
	{
		std::shared_lock<std::shared_mutex> lock{ _mutex };
		const size_t req = strlen(_value);
		const size_t count = req < capacity ? req : capacity - 1;
		strncpy(buf, _value, capacity);
		buf[count] = 0;
		return req;
	}
}