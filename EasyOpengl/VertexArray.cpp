#include"VertexArray.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Debug.h"
#include<stdexcept>

namespace eogl{
	VertexArray::VertexArray(const unsigned int vboCount) : vbos(vboCount){}

	void VertexArray::bind() const {
		for (auto& vbo : vbos) {
            vbo->bind();
        }
    }


}