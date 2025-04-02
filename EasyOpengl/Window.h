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
		VertexBuffer vbo;
		IndexBuffer ibo;

		VertexArray const* boundVao = nullptr;

		void setEventCallbacks();
		void setAsCurrent() const;
	public:

		Window(int width, int height, const std::string &title);
		Window(const Monitor& monitor, bool isFullScreen, const std::string &title);
		~Window();
		void endFrame();

		glm::vec2 getSize() const {
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			return glm::vec2(width, height);
		}
		bool shouldClose() const {
			return glfwWindowShouldClose(window);
		}

		void setClearColor(glm::vec4 color) const;
		void setSize(const int width, const int height) const {
			glfwSetWindowSize(window, width, height);
		}
		void setPosition(const glm::vec2 pos) {
			glfwSetWindowPos(window, pos.x, pos.y);
		}
		void setWindowShouldClose(const bool b = true) {
			glfwSetWindowShouldClose(window, b);
		}
		void setWindowTitle(const char* title) {
			glfwSetWindowTitle(window, title);
		}
		void setFullScreen(bool b);

		glm::vec2 getCursorPos() const {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			return glm::vec2(x, y);
		}
		glm::vec2 getPosition() const {
			int x, y;
			glfwGetWindowPos(window, &x, &y);
			return glm::vec2(x, y);
		}
		template<class T> void setEventCallback(const int type,const T& func) {
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

		void unBindVertexArray() {
			if (boundVao) {

				try{
					boundVao->unBind();
				}catch (...){} // it may occur if boundVao was deleted
				boundVao = nullptr;
			}
		}
		void bindVertexArray(const VertexArray& vao) {
			setAsCurrent();
			unBindVertexArray();
			vao.bind();
			boundVao = &vao;
			setAsCurrent();
		}
	};

}