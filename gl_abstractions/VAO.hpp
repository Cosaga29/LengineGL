#pragma once

#include "VertexBuffer.hpp"
#include "AttribLayout.hpp"
#include <glew.h>
#include <vector>


class VertexArrayObject
{
public:
	unsigned m_rendererID;
	std::vector<std::pair<VertexBuffer, AttribLayout> > buffer_attrib_pairs;

	VertexArrayObject();
	void Bind();
	void Unbind();

	void AddBufferLayout(VertexBuffer& vbo, AttribLayout& attrib);

};


