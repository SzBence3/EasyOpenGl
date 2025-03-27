#pragma once
#include <string>

namespace eogl {
	class Texture
	{
		unsigned int renderId;
		std::string filePath;
		unsigned char* localBuffer;
		int width, height, bpp;
	public:
		Texture(std::string path, bool isGamma = false);
		~Texture();

		void bind(int slot =0) const;
		void unBind() const;

		inline int getWidth() const { return width; };
		inline int getHeight() const { return height; };

		std::string type;
	};

}