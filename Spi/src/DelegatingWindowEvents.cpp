
#include "../include/SbSpi/DelegatingWindowEvents.h"

namespace sb_spi
{
	DelegatingWindowEvents::DelegatingWindowEvents()
	{
	}

	DelegatingWindowEvents::DelegatingWindowEvents(std::shared_ptr<WindowEvents> value) : target{ value }
	{
	}

	DelegatingWindowEvents::~DelegatingWindowEvents()
	{
	}

	void DelegatingWindowEvents::delegateTo(std::shared_ptr<WindowEvents> value)
	{
		target = value;
	}

	bool DelegatingWindowEvents::onChar(GLFWwindow* window, unsigned int ch)
	{
		return dispatch(&WindowEvents::onChar, window, ch);
	}

	bool DelegatingWindowEvents::onCharMods(GLFWwindow* window, unsigned int ch, int mods)
	{
		return dispatch(&WindowEvents::onCharMods, window, ch, mods);
	}

	bool DelegatingWindowEvents::onCursorPos(GLFWwindow* window, double xpos, double ypos)
	{
		return dispatch(&WindowEvents::onCursorPos, window, xpos, ypos);
	}

	bool DelegatingWindowEvents::onFramebufferSize(GLFWwindow* window, int width, int height)
	{
		return dispatch(&WindowEvents::onFramebufferSize, window, width, height);
	}

	bool DelegatingWindowEvents::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		return dispatch(&WindowEvents::onKey, window, key, scancode, action, mods);
	}

	bool DelegatingWindowEvents::onMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		return dispatch(&WindowEvents::onMouseButton, window, button, action, mods);
	}

	bool DelegatingWindowEvents::onScroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		return dispatch(&WindowEvents::onScroll, window, xoffset, yoffset);
	}

	bool DelegatingWindowEvents::onFocus(GLFWwindow* window, bool focused)
	{
		return dispatch(&WindowEvents::onFocus, window, focused);
	}

	bool DelegatingWindowEvents::onIconify(GLFWwindow* window, bool iconified)
	{
		return dispatch(&WindowEvents::onIconify, window, iconified);
	}

	bool DelegatingWindowEvents::onMaximize(GLFWwindow* window, bool maximized)
	{
		return dispatch(&WindowEvents::onMaximize, window, maximized);
	}

	bool DelegatingWindowEvents::onWindowSize(GLFWwindow* window, int width, int height)
	{
		return dispatch(&WindowEvents::onWindowSize, window, width, height);
	}

}