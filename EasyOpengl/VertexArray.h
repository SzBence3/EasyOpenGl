#pragma once
#include"Layout.h"

namespace eogl {
	class VertexArray {
		unsigned int vao,size, layoutSize;
	public:
		VertexArray(unsigned int size, Layout layout, void* data = nullptr);
		void setLayout(Layout layout);
		VertexArray(int size);
		~VertexArray();
		void bind() const;
		void unBind() const;
		void subData(unsigned int begin, unsigned int size, void* data);
		inline unsigned int getSize() { return size; }
		inline unsigned int getVertexSize() {
			return layoutSize;
		}
	};
}