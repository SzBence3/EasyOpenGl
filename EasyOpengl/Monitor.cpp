#include"Monitor.h"
#include <stdexcept>
#include "libinit.h"

 eogl::Monitor::Monitor(int index) {
	int count;
	GLFWmonitor** ptr =glfwGetMonitors(&count);
	if (count < index) {
		throw std::invalid_argument("Monitor index out of range!");
	}
	monitor = ptr[index];
 }
 eogl::Monitor::~Monitor() {
	 
 }