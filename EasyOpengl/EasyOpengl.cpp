﻿// EasyOpengl.cpp : Defines the entry point for the application.


#include <iostream>
#include "WindowManager.h"

int main()
{
	eogl::WindowManager windowManager;
	eogl::Window* window = new eogl::Window(800, 600, "helloworld");
	window->setClearColor(glm::vec4(0.2, 0.3, 0.3, 1.0));
	//window->setFullScreen(1);
	window->setEventCallback(eogl::EOGL_KEY_EVENT, [&window](eogl::Event* e) {
		eogl::KeyEvent* ke = (eogl::KeyEvent*)e;
		std::cout << "Key: " << ke->key << " Action: " << ke->action << std::endl;
		if (ke->key == GLFW_KEY_ESCAPE && ke->action == GLFW_PRESS) {
			window->setWindowShouldClose();
		}
		return 0;
		});
	
	while (!window->shouldClose())
	{
		window->endFrame();
	}
	delete window;
}