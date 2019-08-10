#pragma once

#include "../include/SbWindows/WindowsDynamicLibrary.h"
#include <Windows.h>
#include <stdexcept>

namespace
{
	inline HMODULE handle(void* p)
	{
		return reinterpret_cast<HMODULE>(p);
	}
}

namespace sb_win
{
	WindowsDynamicLibrary::WindowsDynamicLibrary(void* src) : lib{ src, [](void* h) { ::FreeLibrary(handle(h)); } }
	{
		if (!lib)
		{
			throw std::runtime_error("Unable to load dynamic library: error code " + std::to_string(::GetLastError()));
		}
	}
	WindowsDynamicLibrary::WindowsDynamicLibrary(const std::wstring& name) : WindowsDynamicLibrary(::LoadLibraryW(name.c_str()))
	{
	}

	void* WindowsDynamicLibrary::WindowsDynamicLibrary::getAddress(const char* name)
	{
		return ::GetProcAddress(handle(lib.get()), name);
	}
}