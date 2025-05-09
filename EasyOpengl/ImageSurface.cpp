#include "ImageSurface.h"

namespace eogl {
	ImageSurface::ImageSurface(glm::vec2 ld, glm::vec2 rd, bool isInput, std::string imagePath) 
		: BaseSurface(ld, rd, isInput) , texture(imagePath)
	{return ;}
	ImageSurface::ImageSurface(std::string imagePath)
		: BaseSurface(), texture(imagePath)
	{return ;}
	ImageSurface::~ImageSurface() {}
	void ImageSurface::bindTexture(int index) {
		texture.bind(index);
	}
}