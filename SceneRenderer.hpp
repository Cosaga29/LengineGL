#pragma once
#include <glew.h>
#include <string>
#include <queue>
#include "Scene.hpp"
#include <functional>


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
	void DrawObj(const Scene& scene, const SceneObject& obj) const;
	void DrawScene(Scene& scene);
	void Clear() const;

};