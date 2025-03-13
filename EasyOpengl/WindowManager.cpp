#include"WindowManager.h"
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