#include "Texture.h"
#include<GL/glew.h>
#include<stb_image/stb_image.h>
#include"Debug.h"

namespace eogl {
	Texture::Texture(std::string path, bool isGamma = false)
		: filePath(path), localBuffer(nullptr), width(0), height(0), bpp(0)
	{
		stbi_set_flip_vertically_on_load(1);
		localBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);
		ASSERT(localBuffer);// invalid file
		GlCall(glGenTextures(1, &renderId));
		GlCall(glBindTexture(GL_TEXTURE_2D, renderId));
		
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GlCall(glTexImage2D(GL_TEXTURE_2D, 0,isGamma ? GL_SRGB8_ALPHA8 : GL_RGB8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
		GlCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (localBuffer) {
			stbi_image_free(localBuffer);
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &renderId);
	}

	void Texture::bind(int slot) const
	{
		//GlCall(glActiveTexture(GL_TEXTURE0 + slot));
		GlCall(glBindTextureUnit(slot, renderId));
	}

	void Texture::unBind() const
	{
		GlCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}