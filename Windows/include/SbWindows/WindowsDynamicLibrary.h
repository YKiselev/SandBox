#pragma once

#include <string>
#include <memory>

namespace sb_win
{
	class WindowsDynamicLibrary final
	{
	public:
		WindowsDynamicLibrary(void* src);
		WindowsDynamicLibrary(const std::wstring& name);

		template <typename Signature>
		inline Signature* address(const char* name)
		{
			return reinterpret_cast<Signature*>(getAddress(name));
		}
	private:
		std::shared_ptr<void> lib;

		void* getAddress(const char* name);
	};
}