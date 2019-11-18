#pragma once
#include <glew.h>
#include <string>
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "../Scene.hpp"
#include "../outside/glm/glm.hpp"
#include "../outside/glm/gtc/quaternion.hpp"
#include "../outside/glm/gtx/quaternion.hpp"


#define ASSERT(x) if (!(x)) __debugbreak();

//#x turns whatever X is into a string
// '\' removes the new line character from the macro
// x; calls the function passed into the #define macro
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogError(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogError(const char* function, const char* file, int line);


struct DrawContect
{
};


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

	Renderer();
	void Draw(const VertexArray& va, unsigned int indicies, const Shader& shader) const;
	void DrawScene(Scene& scene);
	void Clear() const;

};