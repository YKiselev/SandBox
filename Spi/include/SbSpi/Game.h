#pragma once

#include "SharedObject.h"

namespace sb_spi
{
	//
	// Lifecycle should be managed by the host code.
	//
	class Game : public SharedObject
	{
	public:
		virtual const char* getName() = 0;
	};

	//
	// Lifecycle should be managed by the host code.
	//
	class GameImport
	{
	public:
		enum Level
		{
			Message, Error
		};

		virtual void print(Level level, const char* msg) const = 0;

	protected:
		virtual ~GameImport() = default;
	};

	//
	// Function is expected to be exported from shared library by the name 'createGame'
	// Lifecycle of the returned game is managed by the host code. 
	// Lifecycle of GameImport argument is managed by the host code.
	//
	using CreateGameFunction = sb_spi::Game* (*)(GameImport* gi);
	using CreateGameSignature = sb_spi::Game* (GameImport* gi);
}
