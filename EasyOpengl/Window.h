#pragma once

#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include"Monitor.h"
#include <string>
#include "EventCallback.h"

//EasyOpenGL namespace
namespace eogl {
	class Window {
		GLFWwindow* window;
		void setAsCurrent();
		
	public:

		Window(int width, int height, std::string title);
		Window(const Monitor& monitor, bool isFullScreen, std::string title);
		~Window();
		void endFrame();
		
		void setClearColor(glm::vec4 color);
		inline glm::vec2 getSize() {
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			return glm::vec2(width, height);
		}
		inline bool shouldClose() {
			return glfwWindowShouldClose(window);
		}
		inline void setSize(int width, int height) {
			glfwSetWindowSize(window, width, height);
		}
		inline void setPosition(glm::vec2 pos) {
			glfwSetWindowPos(window, pos.x, pos.y);
		}
		inline void setWindowShouldClose(bool b = 1) {
			glfwSetWindowShouldClose(window, b);
		}
		inline void setWindowTitle(const char* title) {
			glfwSetWindowTitle(window, title);
		}
		inline glm::vec2 getCursorPos() {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			return glm::vec2(x, y);
		}
		inline glm::vec2 getPosition() {
			int x, y;
			glfwGetWindowPos(window, &x, &y);
			return glm::vec2(x, y);
		}
		void setFullScreen(bool b);

		/*template<class T> void setEventCallback(T func) {
			if (eventCallback) {
				delete eventCallback;
			}
			eventCallback = createEventCallback(func);
		}
		*/
		
	};

}