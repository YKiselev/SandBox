#include <stdexcept>
#include <GLFW/glfw3.h>
#include "SbSpi/WindowEvents.h"
#include "../include/SbCore/AppWindow.h"

namespace
{
	using Events = sb_spi::WindowEvents;

	template <typename... Args>
	inline void dispatch(GLFWwindow* window, bool (Events::* emf)(Args...), Args...args)
	{
		Events* const events = static_cast<Events*>(::glfwGetWindowUserPointer(window));
		if (events)
		{
			std::invoke(emf, events, args...);
		}
	}

	void onChar(GLFWwindow* window, unsigned int ch)
	{
		dispatch(window, &Events::onChar, window, ch);
	}

	void onCharMods(GLFWwindow* window, unsigned int ch, int mods)
	{
		dispatch(window, &Events::onCharMods, window, ch, mods);
	}

	void onCursorPos(GLFWwindow* window, double xpos, double ypos)
	{
		dispatch(window, &Events::onCursorPos, window, xpos, ypos);
	}

	void onFramebufferSize(GLFWwindow* window, int width, int height)
	{
		dispatch(window, &Events::onFramebufferSize, window, width, height);
	}

	void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		dispatch(window, &Events::onKey, window, key, scancode, action, mods);
	}

	void onMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		dispatch(window, &Events::onMouseButton, window, button, action, mods);
	}

	void onScroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		dispatch(window, &Events::onScroll, window, xoffset, yoffset);
	}

	void onFocus(GLFWwindow* window, int focused)
	{
		dispatch(window, &Events::onFocus, window, focused == 1);
	}

	void onIconify(GLFWwindow* window, int iconified)
	{
		dispatch(window, &Events::onIconify, window, iconified == 1);
	}

	void onMaximize(GLFWwindow* window, int maximized)
	{
		dispatch(window, &Events::onMaximize, window, maximized == 1);
	}

	void onWindowSize(GLFWwindow* window, int width, int height)
	{
		dispatch(window, &Events::onWindowSize, window, width, height);
	}

	void setCallbacks(GLFWwindow* window) {
		::glfwSetCharCallback(window, onChar);
		::glfwSetCharModsCallback(window, onCharMods);
		::glfwSetCursorPosCallback(window, onCursorPos);
		::glfwSetFramebufferSizeCallback(window, onFramebufferSize);
		::glfwSetKeyCallback(window, onKey);
		::glfwSetMouseButtonCallback(window, onMouseButton);
		::glfwSetScrollCallback(window, onScroll);
		::glfwSetWindowFocusCallback(window, onFocus);
		::glfwSetWindowIconifyCallback(window, onIconify);
		::glfwSetWindowMaximizeCallback(window, onMaximize);
		::glfwSetWindowSizeCallback(window, onWindowSize);
	}
}

namespace app
{
	AppWindow::AppWindow(GLFWwindow* wnd) : window{ wnd }
	{
	}

	AppWindow::AppWindow(AppWindow&& src) noexcept : window{ src.window }
	{
		src.window = nullptr;
	}

	inline AppWindow& AppWindow::operator = (AppWindow&& src) noexcept
	{
		window = src.window;
		src.window = nullptr;
		return *this;
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

		::setCallbacks(window);
		return AppWindow(window);
	}
}