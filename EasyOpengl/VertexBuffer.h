
#pragma once

namespace eogl {
    class VertexBuffer {
        unsigned int id, size;
    public:
        VertexBuffer();
        //size is in bytes
        VertexBuffer(unsigned int size, void* data);
        ~VertexBuffer();
        //size is in bytes
        void reassign(unsigned int size, void* data);
        void subData(unsigned int offset, unsigned int size, void* data);
        void bind() const;
        void unBind() const;
    };
}