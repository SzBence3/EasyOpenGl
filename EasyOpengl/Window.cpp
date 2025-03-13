#include<GL/glew.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include"Window.h"
#include"WindowManager.h"
#include"libinit.h"
#include "Event.h"
#include "Vertex.h"
#include "VertexArray.h"

#define EOGL_TEXTURE_SLOTS 16

namespace eogl {
	void Window::setEventCallbacks() {
		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				Window* win = windowManager->getWindow(window);
				KeyEvent event(key, scancode, action, mods);
				win->pushEvent(EOGL_KEY_EVENT, &event);
			});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			Window* win = windowManager->getWindow(window);
			MousePosEvent event(glm::vec2(xpos, ypos));
			win->pushEvent(EOGL_MOUSE_POS_EVENT, &event);
			});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			Window* win = windowManager->getWindow(window);
			MouseButtonEvent event(button, action, mods);
			win->pushEvent(EOGL_MOUSE_BUTTON_EVENT, &event);
			});
		glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int codepoint) {
			Window* win = windowManager->getWindow(window);
			CharEvent event(codepoint);
			win->pushEvent(EOGL_CHAR_EVENT, &event);
			});
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Window* win = windowManager->getWindow(window);
			MouseScrollEvent event(glm::vec2(xoffset, yoffset));
			win->pushEvent(EOGL_MOUSE_SCROLL_EVENT, &event);
			});
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			Window* win = windowManager->getWindow(window);
			WindowResizeEvent event(glm::vec2(width, height));
			win->pushEvent(EOGL_WINDOW_RESIZE_EVENT, &event);
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

		for(int i = 0; i < surfaces.size(); i+= EOGL_TEXTURE_SLOTS) {
			
			std::vector<std::pair<glm::vec2, glm::vec2>> vbo(4*std::min(EOGL_TEXTURE_SLOTS, (int)surfaces.size()-i));
			std::vector<int> ibo(6 * std::min(EOGL_TEXTURE_SLOTS, (int)surfaces.size() - i));
			
			for (int j = 0; j < std::min(EOGL_TEXTURE_SLOTS, (int)surfaces.size() - i); j++) {
				vbo[j*4] = {surfaces[i + j]->getPosition(getSize()).first, glm::vec2(0,0)};
				vbo[j*4+1] = {vbo[j*4].first + glm::vec2(0.0f,surfaces[i + j]->getSize().y), glm::vec2(0,1)};
				vbo[j*4+2] = {vbo[j*4].first + surfaces[i + j]->getSize(), glm::vec2(1,1)};
				vbo[j*4+3] = {vbo[j*4].first + glm::vec2(surfaces[i + j]->getSize().x,0.0f), glm::vec2(1,0)};
				surfaces[i + j]->bindTexture(j);
				
				//Index buffer				
				ibo[j*6] = 0+j*4;
				ibo[j*6+1] = 1+j*4;
				ibo[j*6+2] = 2+j*4;
				ibo[j*6+3] = 0+j*4;
				ibo[j*6+4] = 2+j*4;
				ibo[j*6+5] = 3+j*4;
			}
			Layout layout;
			layout.pushLayer<float>(2);
			layout.pushLayer<float>(2);
			VertexArray vao(vbo.size(),layout, vbo.data());
			vao.bind();
			
		}
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
	void Window::pushEvent(int type, void* data) {
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