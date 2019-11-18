#pragma once
#include <glew.h>
#include "gl_abstractions/VertexBuffer.hpp"
#include "gl_abstractions/IndexBuffer.hpp"
#include "Mesh.hpp"



/*
Class that contains all necessary information regarding the rendering of an
object to the screen.

It will consist of the VAO used to bind the state of the draw call.

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

	int generateLayout();


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