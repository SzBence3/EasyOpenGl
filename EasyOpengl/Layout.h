#pragma once
#include<vector>
#include<stdexcept>
#include<GL/glew.h>
#include"glTypeConversion.h"

namespace eogl {
	class Layout{
		class Layer{
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
}