#pragma once

#include <glew.h>
#include <vector>
#include "../Model.hpp"
#include "memory"


/*
A vertex array object consists of multiple meshes
*/
class VertexArray
{

public:

	unsigned m_rendererID;
	unsigned int indicies;
	std::unique_ptr<Model> m_model;

	VertexArray();
	void Bind();
	void Unbind();

	void SetModel(Model* model);
	void Clear();

};


