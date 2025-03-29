#pragma once
//#include"Layout.h"
#include"Window.h"
#include"VertexBuffer.h"
#include<vector>
#include<stdexcept>

namespace eogl {
	class VertexArray {
	public:
		class Layout{
				friend class VertexArray;
				class Layer{
					friend class VertexArray;
					friend class Layout;
					unsigned char count;
					unsigned short size;
					bool normalized;
					unsigned int divisor;
					unsigned int type;
					int bufferIndex;
				};
				std::vector<Layer> layers;
			public:
				Layout() = default;
				template<typename T>  void pushLayer(int count,unsigned int bufferIndex = 0, int divisor = 0, bool normalized = false) {
					layers.push_back(newLayer<T>(count, bufferIndex, divisor, normalized));
				}
				template<typename T>  static Layer newLayer(int count,unsigned int bufferIndex = 0, int divisor = 0, bool normalized = false) {
					Layer layer;
					layer.count = count;
					layer.divisor = divisor;
					layer.normalized = normalized;
					layer.size = count * sizeof(T);
					layer.type = getGlType<T>();
					layer.bufferIndex = bufferIndex;
					return layer;
				}
			};
	
			private:
		std::vector<VertexBuffer*> vbos;
		Layout layout;
	public:
		VertexArray(unsigned int vboCount, Layout layout = Layout());
		VertexArray() = default;
		~VertexArray();
		void setVbo(unsigned int index, VertexBuffer* vbo);
		inline void setVboCount(unsigned int count) { vbos.resize(count); };
		void setLayout(Layout layout);
		inline unsigned int getvboCount() const { return vbos.size(); };
		inline Layout getLayout() const { return layout; };
		inline VertexBuffer* getVbo(unsigned int index) const { return vbos[index]; };
		void bind(Window& window) const;
		void unBind(Window& window) const;
	};
}