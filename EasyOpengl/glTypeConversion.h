#pragma once
#include<GL/glew.h>
#include<stdexcept>

namespace eogl {

	template<typename T>
	unsigned int getGlType() {
		throw std::invalid_argument("there is such type");
	}

	template<>
	unsigned int getGlType<float>() {
		return GL_FLOAT;
	}
	template<>
	unsigned int getGlType<char>() {
		return GL_BYTE;
	}
	template<>
	unsigned int getGlType<unsigned char>() {
		return GL_UNSIGNED_BYTE;
	}
	template<>
	unsigned int getGlType<short>() {
		return GL_SHORT;
	}
	template<>
	unsigned int getGlType<unsigned short>() {
		return GL_UNSIGNED_SHORT;
	}
	template<>
	unsigned int getGlType<int>() {
		return GL_INT;
	}
	template<>
	unsigned int getGlType<unsigned int>() {
		return GL_UNSIGNED_INT;
	}
	template<>
	unsigned int getGlType<double>() {
		return GL_DOUBLE;
	}
}