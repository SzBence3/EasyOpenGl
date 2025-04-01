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
			unsigned int bufferIndex;
		};
		std::vector<Layer> layers;
	public:
		Layout() = default;
		Layout(const Layout &layout);
		Layout(Layout &&layout) noexcept;
		explicit Layout(const std::vector<Layer> &layers) : layers(layers){}

		template<typename T>  void pushLayer(const int count, const unsigned int bufferIndex = 0, const int divisor = 0, const bool normalized = false) {
			layers.push_back(newLayer<T>(count, bufferIndex, divisor, normalized));
		}
		
		template<typename T>  static Layer newLayer(const int count, const unsigned int bufferIndex = 0, const unsigned int divisor = 0, const bool normalized = false) {
			Layer layer{};
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