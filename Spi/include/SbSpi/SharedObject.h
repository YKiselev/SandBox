#pragma once

#include <memory>
#include "NonCopyable.h"

namespace sb_spi
{
	//
	// Used as a base class for interfaces, returned from shared libraries.
	//
	class SharedObject : public NonCopyable
	{
	public:
		// Use this method to release instance of interface. Implementation is free to call destructor or do something else (or even nothing).
		virtual void release() = 0;

	protected:
		// Protected to prevent accidental deletion of object instead of calling release method.
		virtual ~SharedObject() = default;
	};

	//
	// Helper method to create shared pointer from raw pointer to instance of SharedObject
	//
	template <typename T>
	std::shared_ptr<T> make_shared(T* p)
	{
		return std::shared_ptr<T>(p, [](T* p) { p->release(); });
	}
}