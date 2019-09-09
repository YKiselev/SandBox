
#include "SbCore/App.h"
#include "SbPal/DynamicLibrary.h"
#include "SbPal/Pal.h"
#include "SbSpi/Game.h"
#include <string>
#include <iostream>
#include <exception>
#include <cstdlib>
#include <memory>
#include "Windows.h"
#include <tchar.h>
#include <filesystem>
#include <io.h>
#include <fcntl.h>
#include "SbSpi/ProgramArguments.h"
#include "SbCommon/StringConversion.h"


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

int useWriteConsole()
{
	HANDLE hInput = ::GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		std::wcout << L"Enter some text (like \x239 or \x44e)...\n";
		TCHAR buf[100];
		DWORD written = 0;
		if (!::ReadConsoleW(hInput, buf, sizeof(buf) / sizeof(TCHAR), &written, NULL))
		{
			std::cout << "Unable to read console input!" << std::endl;
			return 1;
		}
		size_t terminate = max(0, min(written, 199));
		buf[terminate] = 0;
		terminate--;
		// Trim cr/lf
		while (terminate >= 0 && std::isspace(static_cast<unsigned char>(buf[terminate])))
		{
			buf[terminate--] = 0;
		}

		if (!::WriteConsoleW(hOutput, buf, _tcslen(buf), &written, NULL))
		{
			std::cout << "Unable to write to console output!" << std::endl;
			return 1;
		}

		//std::wcout << "Ok, got \"" << buf << "\"\n";
	}
}

int useWriteFile()
{
	HANDLE hInput = ::GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		std::wcout << L"Enter some text (like \x239 or \x44e)...\n";
		char buf[100];
		DWORD written = 0;
		if (!::ReadFile(hInput, buf, sizeof(buf), &written, NULL))
		{
			std::cout << "Unable to read console input!" << std::endl;
			return 1;
		}
		size_t terminate = max(0, min(written, 199));
		buf[terminate] = 0;
		terminate--;
		// Trim cr/lf
		while (terminate >= 0 && std::isspace(static_cast<unsigned char>(buf[terminate])))
		{
			buf[terminate--] = 0;
		}

		if (!::WriteFile(hOutput, buf, strlen(buf), &written, NULL))
		{
			std::cout << "Unable to write to console output!" << std::endl;
			return 1;
		}

		std::wcout << "Ok, got \"" << buf << "\"\n";
	}
}

int useWcout()
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < 10; i++)
	{
		std::wcout << L"Enter some text (like \x239 or \x44e)...\n";

		std::wstring text;
		std::getline(std::wcin, text);

		std::wcout << "Ok, got \"" << text << "\"\n";
		
		if (std::wcout.fail())
		{
			std::wcout << "Wcout failed!\n";
			std::wcout.clear();
		}
		if (std::wcin.fail())
		{
			std::wcout << "Wcin failed!\n";
			std::wcin.ignore(100);
			std::wcin.clear();
		}
	}
	return 0;
}

int useWprintf()
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < 10; i++)
	{
		std::wprintf(L"Enter some text (like \x239 or \x44e)...\n");
		wchar_t buf[200];
		std::wscanf(L"%199s", buf);
		std::wprintf(L"Ok, got \"%s\"\n", buf);
	}
	return 0;
}

void setConsoleCp()
{
	constexpr UINT cp = CP_UTF8; // 1251 ok, 866 ok, 65001 ?
	if (!::SetConsoleOutputCP(cp))
	{
		std::cout << "Failed to set output cp!" << std::endl;
	}
	if (!::SetConsoleCP(cp))
	{
		std::cout << "Failed to set input cp!" << std::endl;
	}
}

int main(int argc, char* argv[])
{/*
	const char* loc = "ru_RU.UTF-8";
	const char* locres = setlocale(LC_ALL, loc);
	if (!locres)
	{
		fprintf(stderr, "Failed to set the specified locale\n");
		return 1;
	}
	else
	{
		printf("Locale is set to %s\n", locres);
	}*/
	//std::cout << "Input cp=" << ::GetConsoleCP() << ", Output cp=" << ::GetConsoleOutputCP() << "\n";
	/*
	setConsoleCp();
	*/
	std::wcout << std::locale().name().c_str() << std::endl;
	//return useWprintf();

	{
		std::string name = u8"SbGame-d.dll";

		sb_pal::DynamicLibrary lib{ name };

		CreateGameSignature* createGame = lib.resolve<CreateGameSignature>("createGame");

		if (createGame)
		{
			std::cout << "Ok" << std::endl;

			MyGameImport gi;

			std::shared_ptr<Game> game{ make_shared(createGame(&gi)) };

			std::cout << "Got new game: " << game->getName() << std::endl;
		}
		else
		{
			throw std::runtime_error("Unable to get function address!");
		}
	}

	app::App app;

	return app.run(argc, argv);
}
