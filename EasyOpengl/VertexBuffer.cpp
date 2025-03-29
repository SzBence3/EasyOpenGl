#include"VertexBuffer.h"
#include<GL/glew.h>
#include"Debug.h"

namespace eogl{
    VertexBuffer::VertexBuffer() : id(0), size(0) {
        GlCall(glGenBuffers(1, &id));
    }
    VertexBuffer::VertexBuffer(unsigned int size, void* data) : id(0), size(size) {
        GlCall(glGenBuffers(1, &id));
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
        GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }
    VertexBuffer::~VertexBuffer() {
        GlCall(glDeleteBuffers(1, &id));
    }
    void VertexBuffer::reassign(unsigned int size, void* data) {
        this->size = size;
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
        GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }
    void VertexBuffer::subData(unsigned int offset, unsigned int size, void* data) {
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
        GlCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
    }
    void VertexBuffer::bind() const {
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    }
    void VertexBuffer::unBind() const {
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}