#include <stdexcept>
#include <GLFW/glfw3.h>
#include "../include/SbCore/AppWindow.h"


namespace app
{
	AppWindow::AppWindow(GLFWwindow* wnd) : window{ wnd }
	{
	}

	AppWindow::AppWindow(AppWindow&& src) noexcept : window{ src.window }
	{
		src.window = nullptr;
	}

	AppWindow::~AppWindow()
	{
		::glfwDestroyWindow(window);
		window = nullptr;
	}

	AppWindow AppWindow::Builder::build()
	{
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
		GLFWwindow* window = ::glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!window)
		{
			throw std::runtime_error("Unable to create application window!");
		}
		return AppWindow(window);
	}
}