#include"VertexBuffer.h"
#include<GL/glew.h>

#include <utility>
#include"Debug.h"

namespace eogl{
    void VertexBuffer::Layout::bind(const unsigned int divisor) const {
        int stride = 0;
        for (const auto& layer : layers) {
            if (stride % layer.size != 0)
                stride += layer.size- stride % layer.size;
            stride+= layer.size*layer.count;
        }
        int offset = 0;
        for (const auto &layer : layers) {
            GlCall(glVertexAttribPointer(layer.index, layer.count, layer.type, layer.normalized, stride, reinterpret_cast<void *>(offset)));
            GlCall(glVertexAttribDivisor(layer.index, divisor));

            offset += layer.size*layer.count;
            if (stride % layer.size != 0)
                offset += layer.size- stride % layer.size;
        }
    }
    void VertexBuffer::Layout::unBind() const {
        for (const auto &layer : layers) {
            GlCall(glDisableVertexAttribArray(layer.index));
        }
    }

    VertexBuffer::VertexBuffer() : id(0), size(0), divisor(0) {
        GlCall(glGenBuffers(1, &id));
    }
    VertexBuffer::VertexBuffer(const unsigned int size, Layout layout, const void* data, const unsigned int divisor)
    : id(0), size(size), divisor(divisor), layout(std::move(layout))
    {
        GlCall(glGenBuffers(1, &id));
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
        GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }
    VertexBuffer::~VertexBuffer()
    {
        GlCall(glDeleteBuffers(1, &id));
    }
    void VertexBuffer::reassign(const unsigned int size, const void* data)
    {
        this->size = size;
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
        GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    void VertexBuffer::subData(const unsigned int offset, const unsigned int size, const void* data)
    {
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
        GlCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    void VertexBuffer::bind() const
    {
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
        layout.bind(divisor); // bind the buffer to the current vao
        GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}