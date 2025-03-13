#pragma once
#include<stdexcept>

#define ASSERT(x) if(!(x)) throw std::runtime_error("Assertion failed!")
#define GlCall(x) GlClearError(); x; ASSERT(glCheckError())
/*
#define ASSERT(x) x
#define GlCall(x) x; ASSERT(glCheckError())
//*/
void GlClearError();

bool glCheckError_(const char* file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__) 

