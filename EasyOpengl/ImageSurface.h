#pragma once

#include "BaseSurface.h"
#include "Texture.h"

namespace eogl {
	class ImageSurface : public BaseSurface {
		Texture texture;
	public:
		ImageSurface(glm::vec2 ld, glm::vec2 rd, bool isInput, std::string imagePath);
		ImageSurface(std::string ImagePath);
		~ImageSurface();
		void bindTexture(int index) override;
	};
}