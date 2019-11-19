#pragma once
#include <glew.h>
#include "gl_abstractions/VertexBuffer.hpp"
#include "gl_abstractions/IndexBuffer.hpp"
#include "Mesh.hpp"
#include "memory"



/*
Class that contains all necessary information regarding the rendering of an
object to the screen.

Contains the raw information of vertex and index data used by the VAO in a draw call.
This class is similar to the mesh class, but is lightweight as it only contains the necessary information

*/
class Model
{
private:

	int stride;
	int attributes;
	unsigned m_vboBufferID;

	std::vector<float> vbo_data;
	std::vector<unsigned> ibo_data;
	VertexBuffer* m_vbo;
	IndexBuffer* m_ibo;

	int generateLayout(gl_data* file_data);


public:

	unsigned verticies;
	unsigned indicies;

	bool hasTexture;
	bool hasNormal;

	Model(const char* filename);
	~Model();

	void Bind();
	void Unbind();

	//TODO:
	void Load(const char* filename);
	void Clear();



};