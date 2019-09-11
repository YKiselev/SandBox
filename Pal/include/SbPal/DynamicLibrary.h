#pragma once

#include <string>
#include <memory>

namespace sb_pal
{
	class DynamicLibrary final
	{
	public:
		DynamicLibrary(void* src);
		DynamicLibrary(const std::string& name);

		template <typename Signature, typename T = std::remove_pointer<Signature>::type>
		inline T * resolve(const char* name)
		{
			return reinterpret_cast<T*>(getAddress(name));
		}

	private:
		std::shared_ptr<void> lib;

		void* getAddress(const char* name);
	};
}
