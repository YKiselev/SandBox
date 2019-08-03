#pragma once

#include <stdexcept>
#include <memory>
#include <GLFW/glfw3.h>
#include "SbSpi/DelegatingWindowEvents.h"

namespace app
{
	/*
		AppWindow
	*/
	class AppWindow
	{
	public:
		class Builder;

		AppWindow(GLFWwindow* wnd);
		AppWindow(const AppWindow& src) = delete;
		AppWindow(AppWindow&& src) noexcept;
		~AppWindow();

		void makeContextCurrent() const;
		bool shouldClose() const;
		void swapBuffers() const;
		void routeTo(std::shared_ptr<sb_spi::WindowEvents> events);

		AppWindow& operator = (const AppWindow& src) = delete;
		AppWindow& operator = (AppWindow&& src) noexcept;

	private:
		GLFWwindow* window;
		std::shared_ptr<sb_spi::WindowEvents> events;
	};

	/*
		Inline methods
	*/

	inline void AppWindow::makeContextCurrent() const
	{
		::glfwMakeContextCurrent(window);
	}

	inline bool AppWindow::shouldClose() const
	{
		return ::glfwWindowShouldClose(window);
	}

	inline void AppWindow::swapBuffers() const
	{
		::glfwSwapBuffers(window);
	}

	inline void AppWindow::routeTo(std::shared_ptr<sb_spi::WindowEvents> target)
	{
		events = target;
		::glfwSetWindowUserPointer(window, events.get());
	}

	/*
		AppWindow builder
	*/
	class AppWindow::Builder
	{
	public:
		Builder& withTitle(const char* value)
		{
			title = value;
			return *this;
		}

		Builder& withSize(int w, int h)
		{
			width = w;
			height = h;
			return *this;
		}

		Builder& withContextVersion(int major, int minor)
		{
			majorVersion = major;
			minorVersion = minor;
			return *this;
		}

		Builder& withFullScreen(bool value)
		{
			fullScreen = value;
			return *this;
		}

		AppWindow build();

	private:
		const char* title{ "Playground" };
		int width{ 800 }, height{ 600 };
		int majorVersion{ 4 }, minorVersion{ 0 };
		bool fullScreen{ false };
	};
}