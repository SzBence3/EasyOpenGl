#include"Debug.h"
#include<GL/glew.h>
#include<iostream>

void GlClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool glCheckError_(const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << (void*)error << "): " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

