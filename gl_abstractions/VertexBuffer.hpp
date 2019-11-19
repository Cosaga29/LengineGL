#pragma once

#include <glew.h>
#include "GLLogger.hpp"

class VertexBuffer {

public:

	unsigned int m_bufferID;

	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};