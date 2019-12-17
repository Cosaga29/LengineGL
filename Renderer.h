#pragma once
#include <glew.h>
#include <string>
#include <queue>
#include <iostream>
#include <functional>
#include "Scene.h"


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
	void DrawScene(const Scene& scene);
	void Clear() const;

};