
#include "SbCore/App.h"
#include "SbPal/DynamicLibrary.h"
#include "SbSpi/Game.h"
#include <string>
#include <iostream>
#include <exception>

struct Base
{
};

template <typename...Tail>
struct X
{

};

template <typename Head, typename...Tail>
struct X<Head, Tail...>
{
	Head head;
	X<Tail...> tail;
};


template <typename...Tail>
struct Y
{

};

template <typename Head, typename...Tail>
struct Y<Head, Tail...> : private Y<Tail...>
{
	using Base = Y<Tail...>;

	Y(Head h, Tail...tail) : _head{ h }, Base{ tail... }
	{
	}

	Head _head;
};

template <typename...Args>
void format(const char* fmt, Args...args)
{

}

int main()
{
	X<int, double, char*, long long> x{ 1, 2.5, "aaaaa", 0xffff };

	Y<int, double, char*, long long> y{ 1, 2.5, "aaaaa", 0xffff };

	std::cout << "Size of x is " << sizeof(x) << "\n";
	std::cout << "Size of y is " << sizeof(y) << "\n";

	format("????", 1, 3.5, "test", 'A');
	/*
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
		*/
	return 0;
	//app::App app;

	//return app.run();
}
