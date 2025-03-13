#include<GL/glew.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include"Window.h"
#include"WindowManager.h"
#include"libinit.h"
#include "Event.h"

namespace eogl {
	void Window::setEventCallbacks() {
		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				Window* win = windowManager->getWindow(window);
				KeyEvent event(key, scancode, action, mods);
				win->callEventCallback(EOGL_KEY_EVENT, &event);
			});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			Window* win = windowManager->getWindow(window);
			MousePosEvent event(glm::vec2(xpos, ypos));
			win->callEventCallback(EOGL_MOUSE_POS_EVENT, &event);
			});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			Window* win = windowManager->getWindow(window);
			MouseButtonEvent event(button, action, mods);
			win->callEventCallback(EOGL_MOUSE_BUTTON_EVENT, &event);
			});
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
			Window* win = windowManager->getWindow(window);
			CharEvent event(codepoint);
			win->callEventCallback(EOGL_CHAR_EVENT, &event);
			});
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Window* win = windowManager->getWindow(window);
			MouseScrollEvent event(glm::vec2(xoffset, yoffset));
			win->callEventCallback(EOGL_MOUSE_SCROLL_EVENT, &event);
			});
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			Window* win = windowManager->getWindow(window);
			WindowResizeEvent event(glm::vec2(width, height));
			win->callEventCallback(EOGL_WINDOW_RESIZE_EVENT, &event);
			});
		if (!isWindowManager)
			throw std::logic_error("WindowManager not initialized!");
		windowManager->addWindow(this);
		
	}

	Window::Window(int width, int height, std::string title) 
		: window(nullptr)
	{
		if (!isWindowManager)
			throw std::runtime_error("WindowManager not initialized!");
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		setAsCurrent();
		setEventCallbacks();
	}
	Window::Window(const Monitor& monitor, bool isFullScreen, std::string title)
		: window(nullptr)
	{
		if(!isWindowManager)
			throw std::runtime_error("WindowManager not initialized!");
		GLFWmonitor* mon = monitor.getMonitor();
		if (isFullScreen) {
			const GLFWvidmode* mode = glfwGetVideoMode(mon);
			window = glfwCreateWindow(mode->width, mode->height, title.c_str(), mon, nullptr);
		}
		else {
			auto size = monitor.getSize();
			window = glfwCreateWindow(size.x, size.y-40, title.c_str(), nullptr, nullptr);
			setPosition(monitor.getPos()+glm::vec2(0,40));
		}
		if (!window) {
			glfwTerminate();
			throw std::runtime_error("Error creating window!");
		}
		setAsCurrent();
		setEventCallbacks();
	}

	Window::~Window() {
		if (isWindowManager) {
			windowManager->removeWindow(this);
		}
		glfwDestroyWindow(window);
	}
	void Window::endFrame() {
		glfwMakeContextCurrent(window);


		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	void Window::setClearColor(glm::vec4 color) {
		setAsCurrent();
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void Window::setAsCurrent() {
		glfwMakeContextCurrent(window);
	}
	void Window::setFullScreen(bool b){
		if (b) {
			GLFWmonitor* mon = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(mon);
			glfwSetWindowMonitor(window, mon, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else {
			glfwSetWindowMonitor(window, nullptr, 0, 0, 800, 600, 60);
			setPosition(glm::vec2(100, 100));
		}
	}
	void Window::callEventCallback(int type, void* data) {
		if (eventCallback[type]) {
			eventCallback[type]->call((Event*)data);
		}
	}
	void Window::addSurface(Surface* surface, int index = -1) {
		if (index == -1) {
			surfaces.push_back(surface);
		}
		else {
			surfaces.insert(surfaces.begin() + index, surface);
		}
	}
	void Window::removeSurface(Surface* surface) {
		auto it = std::find(surfaces.begin(), surfaces.end(), surface);
		if (it != surfaces.end()) {
			surfaces.erase(it);
		}
	}
	void Window::removeAllSurfaces() {
		surfaces.clear();
	}
}