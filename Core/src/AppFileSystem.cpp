
#include "../include/SbCore/AppFileSystem.h"
#include "SbPal/Pal.h"
#include "SbCommon/StringConversion.h"
#include <mutex>

namespace
{
	bool isDefaultGame(const char* name)
	{
		return 0 == strcmp(app::DefaultGameFolder, name);
	}
}

namespace app
{
	//
	//
	//
	Folder::Folder(const fs::path& base, const sb_spi::Logger& logger) : _base{ base }, _logger{ logger }
	{
	}
	Folder::~Folder()
	{
	}
	sb_spi::Readable* Folder::openReadable(const char* name)
	{
		_logger.debug("Trying {}...", sb_com::narrow(_base.c_str()));

		return nullptr;
	}
	sb_spi::Writable* Folder::openWritable(const char* name)
	{
		_logger.debug("Trying {}...", sb_com::narrow(_base.c_str()));

		return nullptr;
	}

	//
	//
	//
	AppFileSystem::AppFileSystem()
	{
	}
	AppFileSystem::~AppFileSystem()
	{

	}
	void AppFileSystem::init(const sb_spi::CoreServices& cs)
	{
		std::lock_guard guard{ _mutex };
		if (_initialized)
		{
			shutdown();
		}
		_logger.delegateTo(cs.loggerFactory->getDelegate("FileSystem"));
		_logger.message("Initializing...");

		_userHome = sb_pal::getUserHome();
		_base = cs.arguments->currentDir;
		_initialized = true;

		select(DefaultGameFolder);
	}
	void AppFileSystem::shutdown()
	{
		std::lock_guard guard{ _mutex };
		if (!_initialized)
		{
			return;
		}
		_logger.message("Shutting down...");
		_folders.clear();
		_initialized = false;
	}
	void AppFileSystem::select(const char* game)
	{
		std::lock_guard guard{ _mutex };
		if (!_initialized)
		{
			return;
		}
		_logger.message("Selecting \"{}\"...", game);
		// add current game user folder
		_folders.emplace_back(_userHome / game, _logger);
		// add current game folder
		_folders.emplace_back(_base / game, _logger);
		if (!isDefaultGame(game))
		{
			_folders.emplace_back(_base / DefaultGameFolder, _logger);
		}
	}
	sb_spi::Readable* AppFileSystem::_openReadable(const char* name)
	{
		for (Folder& folder : _folders)
		{
			
			sb_spi::Readable* r = folder.openReadable(name);
			if (r)
			{
				return r;
			}
		}
		return nullptr;
	}
	sb_spi::Writable* AppFileSystem::_openWritable(const char* name)
	{
		for (Folder& folder : _folders)
		{
			sb_spi::Writable* w = folder.openWritable(name);
			if (w)
			{
				return w;
			}
		}
		return nullptr;
	}
}