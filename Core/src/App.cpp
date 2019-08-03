#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "SbCommon/ScopeGuard.h"
#include "../include/SbCore/App.h"
#include "../include/SbCore/AppWindow.h"


namespace app
{
	App::App()
	{
	}

	App::~App()
	{
	}

	void errorCallback(int error, const char* description)
	{
		std::cout << "ERROR " << error << ", \"" << description << "\"" << std::endl;
	}

	int App::run()
	{
		::glfwSetErrorCallback(errorCallback);

		if (!::glfwInit())
		{
			return 1;
		}
		const sb::common::OnScopeExit terminator{ ::glfwTerminate };

		const app::AppWindow window = app::AppWindow::Builder{}.build();

		window.makeContextCurrent();
		::glfwSwapInterval(1);

		// debug
		const std::chrono::milliseconds timespan(5);
		while (!window.shouldClose())
		{
			::glfwPollEvents();
			window.swapBuffers();
			// debug
			std::this_thread::sleep_for(timespan);
		}

		return 0;
	}
}
