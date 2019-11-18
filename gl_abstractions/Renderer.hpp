#pragma once
#include <glew.h>
#include <string>
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();

//#x turns whatever X is into a string
// '\' removes the new line character from the macro
// x; calls the function passed into the #define macro
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogError(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogError(const char* function, const char* file, int line);

/*
Class to handle creation of openGL calls and binds to render data to the screen.

Things needed to draw to screen:
	VAO -> VBO
	Index Buffer
	Shader


*/
class Renderer
{
private:





public:

	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear() const;

};