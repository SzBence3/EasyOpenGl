#pragma once
//#include"Layout.h"
#include"VertexBuffer.h"
#include<vector>
#include<stdexcept>
#include<memory>

namespace eogl {
	class VertexArray {
		std::vector<std::shared_ptr<VertexBuffer>> vbos;
	public:
		explicit VertexArray(unsigned int vboCount);
		explicit VertexArray(std::initializer_list<std::shared_ptr<VertexBuffer>> vbos) : vbos(vbos) {}
		VertexArray() = default;
		void setVbo(const unsigned int index, std::shared_ptr<VertexBuffer>& vbo){
            if (index >= vbos.size()) {
                throw std::out_of_range("Index out of range");
            }
            vbos[index] = vbo;
        }
		void setVboCount(const unsigned int count) { vbos.resize(count); };
		[[nodiscard]] unsigned int getVboCount() const { return vbos.size(); };
		[[nodiscard]] std::shared_ptr<VertexBuffer> getVbo(const unsigned int index) const { return vbos[index]; };
		void addVbo(std::shared_ptr<VertexBuffer>& vbo) { vbos.push_back(vbo); unBind();};
		void bind() const;
		void unBind() const;
	};
}