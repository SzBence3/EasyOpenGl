
#pragma once
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>

namespace eogl {
	

	class Monitor {
		GLFWmonitor* monitor;
	public:
		// in mm
		Monitor(int index);
		~Monitor();
		inline glm::vec2 getPhysicalSize() const {
			int w, h;
			glfwGetMonitorPhysicalSize(monitor, &w, &h);
			return glm::vec2(w, h);
		}
		inline glm::vec2 getPos() const {
			int x, y;
			glfwGetMonitorPos(monitor, &x, &y);
			return glm::vec2(x, y);
		}
		inline const char* getName() const {
			return glfwGetMonitorName(monitor);
		}
		inline glm::vec2 getSize()const  {
			int x, y, w, h;
			glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);
			return glm::vec2(w, h);
		}
		inline GLFWmonitor* getMonitor() const {
			return monitor;
		}

	};
}