#pragma once
//#include"Layout.h"
#include"Window.h"
#include"VertexBuffer.h"
#include"glTypeConversion.h"
#include<vector>
#include<stdexcept>

namespace eogl {
	class VertexArray {
		std::vector<VertexBuffer*> vbos;
	public:
		explicit VertexArray(unsigned int vboCount);
		VertexArray() = default;
		void setVbo(const unsigned int index, VertexBuffer* vbo){
            if (index >= vbos.size()) {
                throw std::out_of_range("Index out of range");
            }
            vbos[index] = vbo;
        }
		void setVboCount(const unsigned int count) { vbos.resize(count); };
		unsigned int getVboCount() const { return vbos.size(); };
		VertexBuffer* getVbo(const unsigned int index) const { return vbos[index]; };
		void bind() const;
		void unBind() const;
	};
}