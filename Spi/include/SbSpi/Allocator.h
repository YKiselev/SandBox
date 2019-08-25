#pragma once

#include "SharedObject.h"

namespace sb_spi
{
	class Allocator : public SharedObject
	{
	public:
		template <typename T>
		T* allocate(size_t size)
		{
			return alloc(size * sizeof(T));
		}

	protected:
		virtual char* alloc(size_t size);
	};
}
