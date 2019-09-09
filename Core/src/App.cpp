#include <iostream>
#include <thread>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "SbCommon/ScopeGuard.h"
#include "SbSpi/ProgramArguments.h"
#include "../include/SbCore/App.h"
#include "../include/SbCore/AppWindow.h"
#include "../include/SbCore/AppConfiguration.h"
#include "../include/SbCore/AppFileSystem.h"
#include "../include/SbCore/AppLoggerFactory.h"

using namespace sb_spi;

namespace
{
	using namespace app;

	std::vector<std::shared_ptr<LoggerSink>> createSinks()
	{
		std::vector<std::shared_ptr<LoggerSink>> sinks;
		if (true)
		{
			sinks.push_back(std::make_shared<FileSink>("log.txt"));
		}
		if (true)
		{
			sinks.push_back(std::make_shared<ConsoleSink>());
		}
		return sinks;
	}

	ProgramArguments createArguments(int argc, char* argv[])
	{
		return {};
	}

	AppLoggerFactory loggerFactory{ std::make_shared<ChainSink>(createSinks()) };

	void errorCallback(int error, const char* description)
	{
		sb_spi::Logger logger{ loggerFactory.getDelegate("glfw") };

		logger.error("{}: {}", error, description);
	}
}

namespace app
{
	App::App()
	{
	}

	App::~App()
	{
	}

	int App::run(int argc, char* argv[])
	{
		ProgramArguments pa = createArguments(argc, argv);

		//
		// Init GLFW
		//
		::glfwSetErrorCallback(errorCallback);
		if (!::glfwInit())
		{
			return 1;
		}
		const sb_com::OnScopeExit terminator{ ::glfwTerminate };

		//
		// Create core services
		//
		AppFileSystem fileSystem;
		AppConfiguration configuration;
		CoreServices host;
		host.arguments = &pa;
		host.configuration = &configuration;
		host.loggerFactory = &loggerFactory;

		//
		// Init core services
		//
		fileSystem.init(host);
		configuration.init();

		//
		// Create window
		//
		const AppWindow window = AppWindow::Builder{}.build();

		window.makeContextCurrent();
		::glfwSwapInterval(1);

		//
		// Run main loop
		//
		const std::chrono::milliseconds timespan(5);
		while (!window.shouldClose())
		{
			::glfwPollEvents();
			window.swapBuffers();
			std::this_thread::sleep_for(timespan);
		}

		//
		// Shutdown core services
		//
		configuration.shutdown();
		fileSystem.shutdown();

		return 0;
	}
}
