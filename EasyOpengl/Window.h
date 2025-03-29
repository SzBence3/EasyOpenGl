#pragma once

#include "VertexArray.h"
#include "ShaderProgram.h"
#include"Monitor.h"
#include "EventCallback.h"
#include "Surface.h"
#include "IndexBuffer.h"


#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <string>
#include<stdexcept>
#include<vector>

//EasyOpenGL namespace
namespace eogl {
	extern bool isWindowManager;
	class Window {
		friend class WindowManager;
		
		GLFWwindow* window;
		EventCallback* eventCallback[EOGL_EVENT_COUNT] = { nullptr };
		std::vector<Surface*> surfaces;

		ShaderProgram shader;
		VertexArray vao;
		IndexBuffer ibo;

		void setEventCallbacks();
	public:
		void setAsCurrent() const;

		Window(int width, int height, const std::string &title);
		Window(const Monitor& monitor, bool isFullScreen, const std::string &title);
		~Window();
		void endFrame();
		void setClearColor(glm::vec4 color) const;
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
		template<class T> void setEventCallback(int type,const T& func) {
			if (eventCallback[type]) {
				delete eventCallback[type];
				eventCallback[type] = nullptr; // Ensure it is set to nullptr after deletion
			}
			eventCallback[type] = createEventCallback(func);
			if (!eventCallback[type]) {
				throw std::runtime_error("Error creating event callback!");
			}
		}
		void pushEvent(int type, void* data) const;
		void addSurface(Surface* surface, int index = -1);
		void removeSurface(Surface* surface);
		void removeAllSurfaces();
	};

}