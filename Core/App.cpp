#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include "ScopeGuard.h"
#include "App.h"
#include "AppWindow.h"


void errorCallback(int error, const char* description)
{
	std::cout << "ERROR " << error << ", \"" << description << "\"" << std::endl;
}

namespace app
{
	App::App()
	{
	}

	App::~App()
	{
	}

	int App::run()
	{
		::glfwSetErrorCallback(errorCallback);

		if (!::glfwInit())
		{
			return 1;
		}
		const pg::commons::OnScopeExit terminator{ ::glfwTerminate };

		const app::AppWindow window = app::AppWindow::Builder{}.build();

		window.makeContextCurrent();
		::glfwSwapInterval(1);

		const std::chrono::milliseconds timespan(5);
		while (!window.shouldClose())
		{
			::glfwPollEvents();
			window.swapBuffers();
			std::this_thread::sleep_for(timespan);
		}

		return 0;
	}
}
