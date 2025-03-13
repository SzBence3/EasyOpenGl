#include "libinit.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

namespace eogl
{
	int OBJECT_COUNT = 0;
	bool GLEW_INITIALIZED = false;

	void _addObject() {
		if (OBJECT_COUNT== 0) {
			if (!glfwInit()) {
				std::cout << "glfw error" << std::endl;
				throw std::runtime_error("Error initializing GLFW!");
			}
		}
		OBJECT_COUNT++;
	}
	void _removeObject() {
		OBJECT_COUNT--;
		if (OBJECT_COUNT == 0) {
			glfwTerminate();
		}
	}
	void _glewInit() {
		if (!GLEW_INITIALIZED) {
			glewExperimental = GL_TRUE;
			if (glewInit()) {
				std::cout << "glew error" << std::endl;
				throw std::runtime_error("Error initializing GLEW!");
			}
			GLEW_INITIALIZED = true;
		}
	}
}
