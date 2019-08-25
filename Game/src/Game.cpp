
#include "SbSpi/Game.h"
#include "sbgame_export.h"

#ifndef SBGAME_EXPORT
#define SBGAME_EXPORT
#endif

using namespace sb_spi;

class GameImpl : public Game
{
public:
	GameImpl(GameImport* gi) : _gi{ gi }
	{
		_gi->print(GameImport::Message, "Game ctor called.");
	}

	virtual const char* getName()
	{
		return "Default game #1";
	}

	virtual void release()
	{
		_gi->print(GameImport::Message, "Game release() called.");
		delete this;
	}

private:
	GameImport* _gi;

	virtual ~GameImpl()
	{
		_gi->print(GameImport::Message, "Game ctor called.");
	}
};

// warning : redeclaration of 'createGame' should not add 'dllexport' attribute [-Wdll-attribute-on-redeclaration]
extern "C" SBGAME_EXPORT sb_spi::Game* createGame(GameImport* gi)
{
	return new GameImpl{ gi };
}