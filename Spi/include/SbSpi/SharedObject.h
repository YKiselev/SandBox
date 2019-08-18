#pragma once

namespace sb_spi
{
	class SharedObject
	{
	public:
		SharedObject() = default;
		SharedObject(const SharedObject&) = delete;
		SharedObject& operator = (const SharedObject& src) = delete;

		virtual void release() = 0;

	protected:
		virtual ~SharedObject() = default;
	};
}