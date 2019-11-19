#pragma once
#include <glew.h>
#include <string>
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "../Scene.hpp"
#include "../outside/glm/glm.hpp"
#include "../outside/glm/gtc/quaternion.hpp"
#include "../outside/glm/gtx/quaternion.hpp"



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