#pragma once
#include <glew.h>
#include <string>

#include "Scene.hpp"

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
	void DrawScene(const Scene& scene);
	void Clear() const;

};