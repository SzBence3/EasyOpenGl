//#define GLEW_STATIC

#include "libinit.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>

namespace eogl
{
	int OBJECT_COUNT = 0;
	bool GLEW_INITIALIZED = false;

	void addObject() {
		if (OBJECT_COUNT== 0) {
			if (!glfwInit()) {
				std::cout << "glfw error" << std::endl;
				throw std::runtime_error("Error initializing GLFW!");
			}
		}
		OBJECT_COUNT++;
	}
	void removeObject() {
		OBJECT_COUNT--;
		if (OBJECT_COUNT == 0) {
			glfwTerminate();
		}
	}
	void glewInit_() {
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
