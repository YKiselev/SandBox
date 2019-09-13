
#include "../include/SbCore/AppFileSystem.h"
#include "SbPal/Pal.h"
#include "SbCommon/StringConversion.h"
#include <mutex>
#include <cstdio>

namespace
{
	bool isDefaultGame(const char* name)
	{
		return 0 == strcmp(app::DefaultGameFolder, name);
	}

	//
	// BaseFile
	//
	class BaseFile : public sb_spi::SharedObject
	{
	public:
		BaseFile(std::FILE* file) : _file{ file, std::fclose }
		{
		}
		void release() override final
		{
			delete this;
		}
	protected:
		FILE* file() const {
			return _file.get();
		}
	private:
		std::unique_ptr<std::FILE, int(*)(std::FILE*)> _file;
	};

	//
	// Readable file
	//
	class ReadableFile : virtual public sb_spi::Readable, public BaseFile
	{
	public:
		ReadableFile(std::FILE* file) : BaseFile{ file }
		{
		}
		size_t read(char* buf, size_t capacity) override
		{
			return std::fread(buf, sizeof(char), capacity, file());
		}
	};

	//
	// Writable file
	//
	class WritableFile : virtual public sb_spi::Writable, public BaseFile
	{
	public:
		WritableFile(std::FILE* file) : BaseFile{ file }
		{
		}
		size_t write(const char* buf, size_t length) override
		{
			return std::fwrite(buf, sizeof(char), length, file());
		}
	};

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
		_logger.debug("Trying {}...", [&]() {return sb_com::narrow(_base.c_str()); });

		return nullptr;
	}
	sb_spi::Writable* Folder::openWritable(const char* name)
	{
		_logger.debug("Trying {}...", [&]() { return sb_com::narrow(_base.c_str()); });

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
		_logger.info("Initializing...");

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
		_logger.info("Shutting down...");
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
		_logger.info("Selecting \"{}\"...", game);
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