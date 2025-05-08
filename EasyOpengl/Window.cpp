#include<GL/glew.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include"Window.h"
#include"WindowManager.h"
#include"libinit.h"
#include "Event.h"
#include "Debug.h"
#include "config.h"

#define EOGL_TEXTURE_SLOTS 16

namespace eogl {

	struct vertex{
		glm::vec2 pos;
		glm::vec2 texCoord;
		float texIndex;
	};

	void Window::setEventCallbacks() {
		setAsCurrent();
		{
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
		}
		if (!isWindowManager)
			throw std::logic_error("WindowManager not initialized!");
		windowManager->addWindow(this);
		_glewInit();
		setAsCurrent();
		glDebugMessageCallback(
			[](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
				std::cout << "GL ERROR: ";
				switch (severity) {
					case GL_DEBUG_SEVERITY_HIGH:
						std::cout  << message << std::endl;
						break;
					case GL_DEBUG_SEVERITY_MEDIUM:
						std::cout << message << std::endl;
						break;
					case GL_DEBUG_SEVERITY_LOW:
						std::cout << message << std::endl;
						break;
					default:
						break;
				}
				std::cout << "Source: ";
				switch (source) {
					case GL_DEBUG_SOURCE_API:
						std::cout << "API";
						break;
					case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
						std::cout << "WINDOW SYSTEM";
						break;
					case GL_DEBUG_SOURCE_SHADER_COMPILER:
						std::cout << "SHADER COMPILER";
						break;
					case GL_DEBUG_SOURCE_THIRD_PARTY:
						std::cout << "THIRD PARTY";
						break;
					case GL_DEBUG_SOURCE_APPLICATION:
						std::cout << "APPLICATION";
						break;
					default:
						std::cout << "UNKNOWN";
						break;
				}
				std::cout << " Type: ";
				switch (type) {
					case GL_DEBUG_TYPE_ERROR:
						std::cout << "ERROR";
						break;
					case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
						std::cout << "DEPRECATED BEHAVIOR";
						break;
					case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
						std::cout << "UNDEFINED BEHAVIOR";
						break;
					case GL_DEBUG_TYPE_PORTABILITY:
						std::cout << "PORTABILITY";
						break;
					case GL_DEBUG_TYPE_PERFORMANCE:
						std::cout << "PERFORMANCE";
						break;
					default:
						std::cout << "UNKNOWN";
						break;
				}
				std::cout << std::endl;
				1;
		},
			nullptr
		);

		//setting up ibo
		std::vector<int> indices(6*EOGL_TEXTURE_SLOTS);
		for(int i = 0; i < EOGL_TEXTURE_SLOTS; i++) {
			indices[i*6] = 0+i*4;
			indices[i*6+1] = 1+i*4;
			indices[i*6+2] = 2+i*4;
			indices[i*6+3] = 0+i*4;
			indices[i*6+4] = 2+i*4;
			indices[i*6+5] = 3+i*4;
		}
		ibo.subData(0, indices.size(), indices.data());
		
		//setting up shader textur array
		for(int i = 0; i < EOGL_TEXTURE_SLOTS; i++) {
			shader.setUniform("textures[" + std::to_string(i) + "]", i);
		}
		
		//setting up vertex buffer
		vbo = std::shared_ptr<VertexBuffer>(new VertexBuffer(
			sizeof(vertex) * 4 * EOGL_TEXTURE_SLOTS,
			VertexBuffer::Layout({
				VertexBuffer::Layout::newLayer<float>(2, 0), 
				VertexBuffer::Layout::newLayer<float>(2, 1), 
				VertexBuffer::Layout::newLayer<float>(1, 2)
			}))
		);
		vao.addVbo(vbo);

		//an actual vao for the rendering here
		glGenVertexArrays(1,&localVao);
		glBindVertexArray(localVao);
	}
	

	Window::Window(const int width, const int height, const std::string &title) 
		: window(nullptr),
		shader("multiTexture"),
		vao(),
		ibo(6*EOGL_TEXTURE_SLOTS)
	{
		if (!isWindowManager)
			throw std::runtime_error("WindowManager not initialized!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		glfwWindowHint(GLFW_CONTEXT_CREATION_API , GLFW_NATIVE_CONTEXT_API);
#ifdef EOGL_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, windowManager->getOffscreenContext());
		if (!window) {
			glfwTerminate();
			throw std::runtime_error("Error creating window!");
		}
		setAsCurrent();
		setEventCallbacks();
	}
	
	Window::Window(const Monitor& monitor, const bool isFullScreen, const std::string &title)
	: window(nullptr),
		shader("multiTexture"),
		vao(),
		ibo(6*EOGL_TEXTURE_SLOTS)
	{
		if(!isWindowManager)
			throw std::runtime_error("WindowManager not initialized!");
		GLFWmonitor* mon = monitor.getMonitor();
		glfwWindowHint(GLFW_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		glfwWindowHint(GLFW_CONTEXT_CREATION_API , GLFW_NATIVE_CONTEXT_API);
#ifdef EOGL_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
		if (isFullScreen) {
			const GLFWvidmode* mode = glfwGetVideoMode(mon);
			window = glfwCreateWindow(mode->width, mode->height, title.c_str(), mon, windowManager->getOffscreenContext());
		}
		else {
			auto size = monitor.getSize();
			window = glfwCreateWindow(size.x, size.y-40, title.c_str(), nullptr, windowManager->getOffscreenContext());
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
		unBindVertexArray();
		if (isWindowManager) {
			windowManager->removeWindow(this);
		}

		glDeleteVertexArrays(1,&localVao);

		glfwDestroyWindow(window);
	}
	
	void Window::endFrame() {
		glfwMakeContextCurrent(window);
		shader.setUniform("trans", glm::mat4(1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for(int i = 0; i < surfaces.size(); i+= EOGL_TEXTURE_SLOTS) {

			std::vector<vertex> vbo(4*std::min(EOGL_TEXTURE_SLOTS, (int)surfaces.size()-i));
			
			for (int j = 0; j < std::min(EOGL_TEXTURE_SLOTS, (int)surfaces.size() - i); j++) {
				vbo[j*4] = {surfaces[i + j]->getPos(getSize()), glm::vec2(0,0), float(j)};
				vbo[j*4+1] = {vbo[j*4].pos + glm::vec2(0.0f,surfaces[i + j]->getSize(getSize()).y), glm::vec2(0,1), float(j)};
				vbo[j*4+2] = {vbo[j*4].pos + surfaces[i + j]->getSize(getSize()), glm::vec2(1,1),float(j)};
				vbo[j*4+3] = {vbo[j*4].pos + glm::vec2(surfaces[i + j]->getSize(getSize()).x,0.0f), glm::vec2(1,0), float(j)};
				surfaces[i + j]->Render();
				surfaces[i + j]->bindTexture(j);
			}
			
			setAsCurrent();
			this->vbo->subData(0, sizeof(vertex) * vbo.size(), vbo.data());
			vao.bind();
			this->ibo.bind();
			shader.bind();


			GlCall(glDrawElements(GL_TRIANGLES, std::min(EOGL_TEXTURE_SLOTS, (int)surfaces.size() - i), GL_UNSIGNED_INT, nullptr));

			shader.unBind();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
		windowManager->setBackgroundContextActive();
	}
	void Window::setClearColor(glm::vec4 color) const {
		setAsCurrent();
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void Window::setAsCurrent() const {
		glfwMakeContextCurrent(window);
	}
	void Window::setFullScreen(const bool b){
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
	void Window::pushEvent(int type, void *data) const {
		if (eventCallback[type]) {
			eventCallback[type]->call((Event*)data);
		}
	}
	void Window::addSurface(std::shared_ptr<Surface> surface, int index) {
		if (index == -1) {
			surfaces.push_back(surface);
		}
		else {
			surfaces.insert(surfaces.begin() + index, surface);
		}
	}
	void Window::removeSurface(std::shared_ptr<Surface> surface) {
		auto it = std::find(surfaces.begin(), surfaces.end(), surface);
		if (it != surfaces.end()) {
			surfaces.erase(it);
		}
	}
	void Window::removeAllSurfaces() {
		surfaces.clear();
	}

}