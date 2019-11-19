#pragma once
#include <glew.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

//#x turns whatever X is into a string
// '\' removes the new line character from the macro
// x; calls the function passed into the #define macro
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogError(#x, __FILE__, __LINE__))


void GLClearError();

bool GLLogError(const char* function, const char* file, int line);