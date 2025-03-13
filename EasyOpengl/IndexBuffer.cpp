#include "IndexBuffer.h"
#include<GL/glew.h>
#include "Debug.h"
#include<iostream>

IndexBuffer::IndexBuffer(int size, void* data) : size(size/4)
{
	GlCall(glGenBuffers(1, &ibo));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &ibo);
}
void IndexBuffer::bind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo));
}
void IndexBuffer::unBind() const {
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
void IndexBuffer::subData(unsigned int offset, unsigned int size, void* data) {
	bind();
	GlCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
}
