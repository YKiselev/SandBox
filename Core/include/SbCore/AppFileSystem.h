#pragma once

#include "SbSpi/FileSystem.h"
#include "SbSpi/Host.h"
#include "SbSpi/PersistedConfiguration.h"
#include <vector>
#include <mutex>
#include <filesystem>

namespace app
{
	namespace fs = std::filesystem;

	constexpr const char* const DefaultGameFolder = "default";

	//
	// File system consists of several ordered virtual folders
	//
	class Folder
	{
	public:
		Folder(const fs::path& base, const sb_spi::Logger& logger);
		~Folder();

		sb_spi::Readable* openReadable(const char* name);
		sb_spi::Writable* openWritable(const char* name);

	private:
		fs::path _base;
		sb_spi::Logger _logger;
	};

	//
	// File system is a vector of virtual folders. Usual layout (and search order) looks like this:
	// 1) Current game folder in user's home directory (writable)
	// 2) Current game folder in base directory (read-only)
	// 3) Default game fodler in base directory (read-only)
	class AppFileSystem : public sb_spi::FileSystem
	{
	public:
		AppFileSystem();
		virtual ~AppFileSystem();

		void init(const sb_spi::CoreServices& cs);
		void shutdown();
		void select(const char* game);

	protected:
		sb_spi::Readable* _openReadable(const char* name) override;
		sb_spi::Writable* _openWritable(const char* name) override;

	private:
		std::recursive_mutex _mutex;
		std::vector<Folder> _folders;
		bool _initialized = false;
		std::string _game;
		fs::path _userHome;
		fs::path _base;
		sb_spi::Logger _logger;
	};
}