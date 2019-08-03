#pragma once

namespace sb_spi
{
	class WindowEvents
	{
	public:
		virtual ~WindowEvents()
		{
		}

		virtual bool onChar(GLFWwindow* window, unsigned int ch)
		{
			return false;
		}

		virtual bool onCharMods(GLFWwindow* window, unsigned int ch, int mods)
		{
			return false;
		}

		virtual bool onCursorPos(GLFWwindow* window, double xpos, double ypos)
		{
			return false;
		}

		virtual bool onFramebufferSize(GLFWwindow* window, int width, int height)
		{
			return false;
		}

		virtual bool onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			return false;
		}

		virtual bool onMouseButton(GLFWwindow* window, int button, int action, int mods)
		{
			return false;
		}

		virtual bool onScroll(GLFWwindow* window, double xoffset, double yoffset)
		{
			return false;
		}

		virtual bool onFocus(GLFWwindow* window, bool focused)
		{
			return false;
		}

		virtual bool onIconify(GLFWwindow* window, bool iconified)
		{
			return false;
		}

		virtual bool onMaximize(GLFWwindow* window, bool maximized)
		{
			return false;
		}

		virtual bool onWindowSize(GLFWwindow* window, int width, int height)
		{
			return false;
		}
	};
}