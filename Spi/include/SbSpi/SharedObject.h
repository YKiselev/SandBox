#pragma once

#include <memory>

namespace sb_spi
{
	// Used as a base class for interfaces, returned from shared libraries.
	class SharedObject
	{
	public:
		SharedObject() = default;
		SharedObject(const SharedObject&) = delete;
		SharedObject& operator = (const SharedObject& src) = delete;

		// Use this method to release instance of interface. Implementation is free to call destructor or do something else (or even nothing).
		virtual void release() = 0;

	protected:
		// Protected to prevent accidental deletion of object instead of calling release method.
		virtual ~SharedObject() = default;
	};

	template <typename T>
	std::shared_ptr<T> make_shared(T* p)
	{
		return std::shared_ptr<T>(p, [](T* p) { p->release(); });
	}
}