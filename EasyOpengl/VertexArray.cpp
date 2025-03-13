#include"VertexArray.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Debug.h"

namespace eogl{
	VertexArray::VertexArray(unsigned int size, Layout layout, void* data ) :size(size)
	{
		GlCall(glGenVertexArrays(1, &vao));
		GlCall(glBindVertexArray(vao));
		
		unsigned int buff;
		GlCall(glGenBuffers(1, &buff));
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, buff));
		GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
		setLayout(layout);
	}
	VertexArray::VertexArray(int size) :size(size), layoutSize (-1)
	{
		if (size == -1) {
			return;
		}
		GlCall(glGenVertexArrays(1, &vao));
		GlCall(glBindVertexArray(vao));

		unsigned int buff;
		GlCall(glGenBuffers(1, &buff));
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, buff));
		GlCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
	}

	VertexArray::~VertexArray() 
	{
		if (size != -1)
			glDeleteVertexArrays(1, &vao);
	}
	void VertexArray::bind() const
	{
		glBindVertexArray(vao);
	}
	void VertexArray::unBind() const {
		glBindVertexArray(0);
	}
	void VertexArray::subData(unsigned int offset, unsigned int size, void* data) {GL_INVALID_VALUE;
		bind();
		GlCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	}

	void VertexArray::setLayout(Layout layout) {
		auto layers = layout.getLayers();
		int size = 0;
		for (int i = 0; i < layers.size(); i++) {
			size += layers[i].size;
		}
		layoutSize = size;
		int size2 = 0;
		bind();
		for (int i = 0; i < layers.size(); i++) {
			GlCall(glEnableVertexAttribArray(i));
			GlCall(glVertexAttribPointer(i, layers[i].count, layers[i].type, layers[i].normalized, size, (void*)size2));
			size2 += layers[i].size;
		}
	}
}