#pragma once

#include "NonCopyable.h"
#include "SharedObject.h"

namespace sb_spi
{
	//
	// Readable byte stream
	//
	class Readable : public SharedObject
	{
	public:
		//
		// Reads up to specified amount of bytes from the stream to supplied buffer.
		//
		// @param buf the buffer.
		// @param capacity the buffre's capacity.
		// @return the number of bytes read or -1 if end of stream reached.
		//
		virtual size_t read(char* buf, size_t capacity) = 0;
	};

	//
	// Writable byte stream
	//
	class Writable : public SharedObject
	{
	public:
		//
		// Writes supplied bytes to the stream
		//
		// @param buf the buffer
		// @param length number of bytes to write
		// @return number of bytes written or -1 if stream is closed.
		//
		virtual size_t write(const char* buf, size_t length) = 0;
	};

	//
	// File system interface
	//
	class FileSystem : public NonCopyable
	{
	public:
		inline std::shared_ptr<Readable> openReadable(const char* name)
		{
			return sb_spi::make_shared(_openReadable(name));
		}
		inline std::shared_ptr<Writable> openWritable(const char* name)
		{
			return sb_spi::make_shared<Writable>(_openWritable(name));
		}
	protected:
		virtual Readable* _openReadable(const char* name) = 0;
		virtual Writable* _openWritable(const char* name) = 0;
	};
}