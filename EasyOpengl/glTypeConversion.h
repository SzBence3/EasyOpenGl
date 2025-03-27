#pragma once
#include<GL/glew.h>
#include<stdexcept>

namespace eogl {

	template<typename T>
	inline unsigned int getGlType() {
		throw std::invalid_argument("there is such type");
	}

	template<>
	inline unsigned int getGlType<float>() {
		return GL_FLOAT;
	}
	template<>
	inline unsigned int getGlType<char>() {
		return GL_BYTE;
	}
	template<>
	inline unsigned int getGlType<unsigned char>() {
		return GL_UNSIGNED_BYTE;
	}
	template<>
	inline unsigned int getGlType<short>() {
		return GL_SHORT;
	}
	template<>
	inline unsigned int getGlType<unsigned short>() {
		return GL_UNSIGNED_SHORT;
	}
	template<>
	inline unsigned int getGlType<int>() {
		return GL_INT;
	}
	template<>
	inline unsigned int getGlType<unsigned int>() {
		return GL_UNSIGNED_INT;
	}
	template<>
	inline unsigned int getGlType<double>() {
		return GL_DOUBLE;
	}
}