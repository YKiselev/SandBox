#pragma once

#include "../include/SbWindows/DynamicLibrary.h"
#include <Windows.h>
#include <stdexcept>
#include "SbCommon/StringConversion.h"

namespace
{
	inline HMODULE handle(void* p)
	{
		return reinterpret_cast<HMODULE>(p);
	}
}

namespace sb_pal
{
	DynamicLibrary::DynamicLibrary(void* src) : lib{ src, [](void* h) { ::FreeLibrary(handle(h)); } }
	{
		if (!lib)
		{
			throw std::runtime_error("Unable to load dynamic library: error code " + std::to_string(::GetLastError()));
		}
	}
	DynamicLibrary::DynamicLibrary(const std::string& name) : DynamicLibrary(::LoadLibraryW(sb_com::widen(name).c_str()))
	{
	}
	void* DynamicLibrary::DynamicLibrary::getAddress(const char* name)
	{
		return ::GetProcAddress(handle(lib.get()), name);
	}
}