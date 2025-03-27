#include"WindowManager.h"
#include"ShaderProgram.h"
#include "libinit.h"
#include<stdexcept>

namespace eogl {
	bool isWindowManager = false;
	WindowManager* windowManager = nullptr;

	WindowManager::WindowManager() {
		if (!isWindowManager) {
			isWindowManager = true;
			windowManager = this;
		}
		else throw std::runtime_error("WindowManager already exists!");
		_addObject();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		offscreen_context = glfwCreateWindow(1, 1, "offscreen", nullptr, nullptr);
		glfwMakeContextCurrent(offscreen_context);
		_glewInit();
		ShaderProgram::addDefaultShaders();
	}

	WindowManager::~WindowManager() {
		for (auto window : windows) {
			delete window;
		}
		_removeObject();
		isWindowManager = false;
	}

	void WindowManager::addWindow(Window* window) {
		windows.push_back(window);
	}
	void WindowManager::removeWindow(Window* window) {
		for (auto it = windows.begin(); it != windows.end(); it++) {
			if (*it == window) {
				windows.erase(it);
				break;
			}
		}
	}
	int WindowManager::getMonitorCount() {
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		return count;
	}
	Monitor WindowManager::getIthMonitor(int i) {
		return Monitor(i);
	}
	
	Window* WindowManager::getWindow(GLFWwindow* window) {
		for (auto w : windows) {
			if (w->window == window) {
				return w;
			}
		}
		return nullptr;
	}
}