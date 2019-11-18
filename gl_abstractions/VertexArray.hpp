#pragma once

#include <glew.h>
#include <vector>
#include "../Model.hpp"


/*
A vertex array object consists of multiple meshes
*/
class VertexArray
{

public:

	unsigned m_rendererID;
	std::vector<Model>  buffer_models;

	VertexArray();
	void Bind();
	void Unbind();

	void AddModel(Model& model);
	void Clear();

};


