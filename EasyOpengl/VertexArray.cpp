#include"VertexArray.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"Debug.h"
#include<stdexcept>

namespace eogl{
	VertexArray::VertexArray(unsigned int vboCount, Layout layout) : layout(layout), vbos(vboCount) {}
	VertexArray::~VertexArray() {}
	
	void VertexArray::setVbo(unsigned int index, VertexBuffer* vbo) {
		if (index >= vbos.size()) throw std::out_of_range("Index out of range in VertexArray::setVbo()");
		vbos[index] = vbo;
	}
	
	void VertexArray::setLayout(Layout layout) {
		this->layout = layout;
	}
	
	void VertexArray::bind(Window& window) const {
		window.setAsCurrent();
		for(int i = 0; i < layout.layers.size(); i++){
			glEnableVertexAttribArray(i);

			if(vbos[layout.layers[i].bufferIndex] == nullptr) 
				throw std::runtime_error("VertexBuffer not set in VertexArray::bind()");
			vbos[layout.layers[i].bufferIndex]->bind();

			glVertexAttribPointer(i, layout.layers[i].count, layout.layers[i].type, layout.layers[i].normalized, layout.layers[i].size, (void*)0);
			glVertexAttribDivisor(i, layout.layers[i].divisor);

			vbos[layout.layers[i].bufferIndex]->unBind();
		}
	}
	
	void VertexArray::unBind(Window& window) const {
		window.setAsCurrent();
		for(int i = 0; i < layout.layers.size(); i++){
			glDisableVertexAttribArray(i);
		}
	}
}