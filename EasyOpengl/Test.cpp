#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

int main(){
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    eogl::ShaderProgram shader("shaders/2dMultiTexture.vert", "shaders/multiTexture.fs", true);
    shader.setUniform("trans", glm::mat4(1.0f));

    uint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    eogl::VertexBuffer vbo(sizeof(float) * 4 * 4, eogl::VertexBuffer::Layout({
        eogl::VertexBuffer::Layout::newLayer<float>(2, 0),
        eogl::VertexBuffer::Layout::newLayer<float>(2, 1),
        eogl::VertexBuffer::Layout::newLayer<float>(1, 2)
    }));
    eogl::IndexBuffer ibo(6);
    ibo.subData(0, 6, new unsigned int[6]{0, 1, 2, 0, 2, 3});


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
    }

}