#pragma once

#include <memory>
#include <Windows.h>

namespace sb::common
{
	class WindowsDynamicLibrary final
	{
	public:
		WindowsDynamicLibrary(HMODULE src) : lib{ src, [](HMODULE h) { ::FreeLibrary(h); } }
		{
			if (!handle())
			{
				throw std::runtime_error("Unable to load dynamic library: error code " + ::GetLastError());
			}
		}
		WindowsDynamicLibrary(const std::wstring& name) : WindowsDynamicLibrary(::LoadLibrary(name.c_str()))
		{
		}

		template <typename Signature>
		Signature* address(const char* name)
		{
			return reinterpret_cast<Signature*>(::GetProcAddress(handle(), name));
		}
	private:
		std::shared_ptr<void> lib;

		inline HMODULE handle() const
		{
			return reinterpret_cast<HMODULE>(lib.get());
		}
	};
}