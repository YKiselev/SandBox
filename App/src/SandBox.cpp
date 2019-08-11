
#include "SbCore/App.h"
#include "SbPal/DynamicLibrary.h"
#include "SbSpi/Game.h"
#include <string>
#include <iostream>
#include <exception>

int main()
{
	std::wstring name = L"SbGame-d.dll";

	sb_pal::DynamicLibrary lib{ name };

	sb_spi::CreateGameSignature* fn1 = lib.address<sb_spi::CreateGameSignature>("createGame");

	sb_spi::Game*(*fn)() = lib.address<sb_spi::Game*()>("createGame");
	if (fn)
	{
		std::cout << "Ok" << std::endl;

		sb_spi::Game* game = fn();

		std::cout << "Got new game: " << game->getName() << std::endl;

		game->release();
		game = nullptr;
	}
	else
	{
		throw std::runtime_error("Unable to get function address!");
	}

	return 0;
	//app::App app;
	
	//return app.run();
}
