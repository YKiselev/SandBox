#pragma once

namespace sb_spi
{
	class Game
	{
	public:
		virtual const char* getName() = 0;
		virtual void release() = 0;

	protected:
		virtual ~Game() {}
	};

	/*
		Function is expected to be exporrted from shared library by the name 'createGame'
	*/
	using CreateGameFunction = sb_spi::Game* (*)();
	using CreateGameSignature = sb_spi::Game*();
}
