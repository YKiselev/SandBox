
#include "SbSpi/Game.h"
#include "sbgame_export.h"

#ifndef SBGAME_EXPORT
	#define SBGAME_EXPORT
#endif

class GameImpl : public sb_spi::Game
{
public:
	virtual const char* getName()
	{
		return "Default game #1";
	}

	virtual void release()
	{
		delete this;
	}

protected:
	virtual ~GameImpl()
	{
		// do some cleanup
	}
};

// warning : redeclaration of 'createGame' should not add 'dllexport' attribute [-Wdll-attribute-on-redeclaration]
extern "C" SBGAME_EXPORT sb_spi::Game* createGame()
{
	return new GameImpl{};
}