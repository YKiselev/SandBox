#pragma once

#include <memory>
#include <functional>
#include <GLFW/glfw3.h>
#include "WindowEvents.h"

namespace sb_spi
{
	class DelegatingWindowEvents : public WindowEvents
	{
	public:
		DelegatingWindowEvents();
		DelegatingWindowEvents(std::shared_ptr<WindowEvents> delegate);
		virtual ~DelegatingWindowEvents() override;

		void delegateTo(std::shared_ptr<WindowEvents> value);

		virtual bool onChar(GLFWwindow* window, unsigned int ch) override;
		virtual bool onCharMods(GLFWwindow* window, unsigned int ch, int mods) override;
		virtual bool onCursorPos(GLFWwindow* window, double xpos, double ypos) override;
		virtual bool onFramebufferSize(GLFWwindow* window, int width, int height) override;
		virtual bool onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
		virtual bool onMouseButton(GLFWwindow* window, int button, int action, int mods) override;
		virtual bool onScroll(GLFWwindow* window, double xoffset, double yoffset) override;
		virtual bool onFocus(GLFWwindow* window, bool focused) override;
		virtual bool onIconify(GLFWwindow* window, bool iconified) override;
		virtual bool onMaximize(GLFWwindow* window, bool maximized) override;
		virtual bool onWindowSize(GLFWwindow* window, int width, int height) override;

	private:
		std::shared_ptr<WindowEvents> target;

		template <typename Emf, typename... Args>
		inline bool dispatch(Emf emf, Args...args)
		{
			return target ? std::invoke(emf, target.get(), args...) : false;
		}
	};
}