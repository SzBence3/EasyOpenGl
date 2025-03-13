#pragma once
#include<GL/glew.h>
#include<stdexcept>

namespace eogl {

	template<typename T>
	static unsigned int getGlType() {
		throw std::invalid_argument("there is such type");
	}

	template<>
	static unsigned int getGlType<float>() {
		return GL_FLOAT;
	}
	template<>
	static unsigned int getGlType<char>() {
		return GL_BYTE;
	}
	template<>
	static unsigned int getGlType<unsigned char>() {
		return GL_UNSIGNED_BYTE;
	}
	template<>
	static unsigned int getGlType<short>() {
		return GL_SHORT;
	}
	template<>
	static unsigned int getGlType<unsigned short>() {
		return GL_UNSIGNED_SHORT;
	}
	template<>
	static unsigned int getGlType<int>() {
		return GL_INT;
	}
	template<>
	static unsigned int getGlType<unsigned int>() {
		return GL_UNSIGNED_INT;
	}
	template<>
	static unsigned int getGlType<double>() {
		return GL_DOUBLE;
	}
}