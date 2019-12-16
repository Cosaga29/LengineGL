#pragma once


#include "gl_abstractions/VertexArray.hpp"
#include "gl_abstractions/Shader.hpp"

#include "Transform.h"

enum DRAW_MODE
{
	TRIANGLES = 0, LINES = 1
};


/*
Each object passed to the renderer will have a
	vao for vbo/ibo information
	transformation matrix (model matrix)
	Shader to be used
*/
struct SceneObject
{
	SceneObject(VertexArray* vao, Transform* transform, Shader* shader) :
		vao(vao), transformation(transform), shader(shader), isVisible(1), mode(TRIANGLES)
	{
		if (!vao->hasLayout)
		{
			vao->initLayout();
		}
		shader->Unbind();
		vao->Unbind();
	}

	std::unique_ptr<VertexArray> vao;
	std::unique_ptr<Transform> transformation;
	std::unique_ptr<Shader> shader;

	DRAW_MODE mode;
	bool isVisible;
};