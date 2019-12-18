#pragma once

#include <glew.h>
#include <vector>
#include "memory"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "../Graphics/ObjMeshLoader.h"
#include "Mesh.h"

/*
Condensed old "Model" class into this VAO class. 
The VAO is the closest thing OpenGl has to representing a model. This class contains all
of the information needed for basic rendering (pos, normal, texture)

Need to test with textures still.

*/


/*
A vertex array object consists of multiple meshes
*/
class VertexArray
{
public:

	int initLayout();

	unsigned m_rendererID;
	unsigned int indicies;
	unsigned int attributes;
	bool hasLayout;
	std::unique_ptr<Mesh> model_data;

	//TODO: set multithread to load this file in background
	VertexArray(const std::string& filename); //create vertex array based on a model file
	VertexArray(struct Mesh* data); //create vertex array from simple gl data

	void Bind();
	void Unbind();

};


