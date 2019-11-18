#pragma once
#include <vector>
#include "VertexBuffer.hpp"

class VertexBufferLayout;

class VertexArray {

	unsigned int m_rendererID;

private:

	std::vector<std::pair<VertexBuffer, VertexBufferLayout> > vertexArrays;

public:


	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;

};