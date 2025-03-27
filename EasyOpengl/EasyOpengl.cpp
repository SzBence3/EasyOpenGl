// EasyOpengl.cpp : Defines the entry point for the application.

#include <GL/glew.h>
#include <iostream>
#include "WindowManager.h"
#include "ShaderProgram.h"
#include "ImageSurface.h"
#include "Texture.h"

int main()
{
	eogl::WindowManager windowManager;
	eogl::Texture tex("res/textures/screenshot.png", true);
	eogl::Window* window = new eogl::Window(800, 600, "helloworld");
	unsigned int id = glCreateProgram();

	tex.bind();
	window->setClearColor(glm::vec4(0.2, 0.3, 0.3, 1.0));

	
	window->setEventCallback(eogl::EOGL_KEY_EVENT, [&window](eogl::Event* e) {
		eogl::KeyEvent* ke = (eogl::KeyEvent*)e;
		//std::cout << "Key: " << ke->key << " Action: " << ke->action << std::endl;
		if (ke->key == GLFW_KEY_ESCAPE && ke->action == GLFW_PRESS) {
			window->setWindowShouldClose();
		}
		return 0;
		});

	//writing out what the user typed in
	window->setEventCallback(eogl::EOGL_CHAR_EVENT, [&window](eogl::Event* e) {
		eogl::CharEvent* ce = (eogl::CharEvent*)e;
		std::cout << (char*) &(ce->codepoint)  << std::flush;
		return 0;
		});

	eogl::ImageSurface* image = new eogl::ImageSurface("res/textures/screenshot.png");
	window->addSurface(image);

	image->setSize({0.5f, 0.5f});
	image->setPos({0,0});

	while (!window->shouldClose())
	{
		window->endFrame();
	}
	delete window;
	delete image;
}