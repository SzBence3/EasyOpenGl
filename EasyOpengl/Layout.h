#pragma once
#include<vector>
#include<stdexcept>
#include<GL/glew.h>
#include"glTypeConversion.h"

namespace eogl {

	struct Layer {
		unsigned int size, count;
		unsigned int type;
		bool normalized;
	};

	class Layout {
	private:
		std::vector<Layer>layers;
	public:
		Layout() {};
		~Layout() {};
		template<typename T>
		void pushLayer(unsigned int count, bool normalized = 0) {
			layers.push_back(Layer{ (unsigned int)sizeof(T) * count, count, getGlType<T>(), normalized});
		}
		const std::vector<Layer>& getLayers() const { return layers; };
	};

}