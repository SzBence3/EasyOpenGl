// EasyOpengl.cpp : Defines the entry point for the application.


#include <iostream>
#include "Window.h"

int main(void)
{
	eogl::Window window(800,600, "Hello World");
	window.setClearColor(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));
	window.setFullScreen(1);
	window.setFullScreen(0);
	

	while (!window.shouldClose())
	{
		window.endFrame();
	}
}