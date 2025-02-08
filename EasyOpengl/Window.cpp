#include<GL/glew.h>
#include"Window.h"
#include"libinit.h"
#include <stdexcept>
#include <iostream>

namespace eogl {

	Window::Window(int width, int height, std::string title) 
		: window(nullptr)
	{
		addObject();
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		setAsCurrent();
		glewInit_();
	}
	Window::Window(const Monitor& monitor, bool isFullScreen, std::string title)
		: window(nullptr)
	{
		addObject();
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
		glewInit_();
	}
	Window::~Window() {
		glfwDestroyWindow(window);
		removeObject();
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
}