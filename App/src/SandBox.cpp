
#include "SbCore/App.h"
#include "SbPal/DynamicLibrary.h"
#include "SbSpi/Game.h"
#include <string>
#include <iostream>
#include <exception>

using namespace sb_spi;

class MyGameImport : public sb_spi::GameImport
{
public:
	void print(Level level, const char* msg) const override
	{
		switch (level)
		{
		case Message:
			std::cout << "MESSAGE: " << msg << std::endl;
			break;

		case Error:
			std::cout << "ERROR: " << msg << std::endl;
			break;

		default:
			std::cout << "Got something from game: " << msg << std::endl;
		}
	}

	virtual ~MyGameImport()
	{
	}
};

int main()
{
	std::wstring name = L"SbGame-d.dll";

	sb_pal::DynamicLibrary lib{ name };

	CreateGameSignature* createGame = lib.address<CreateGameSignature>("createGame");

	if (createGame)
	{
		std::cout << "Ok" << std::endl;

		MyGameImport gi{};
		
		std::shared_ptr<Game> game{ make_shared(createGame(&gi)) };

		std::cout << "Got new game: " << game->getName() << std::endl;
	}
	else
	{
		throw std::runtime_error("Unable to get function address!");
	}

	return 0;
	//app::App app;

	//return app.run();
}
