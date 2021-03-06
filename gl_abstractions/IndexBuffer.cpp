#include <glew.h>

#include "IndexBuffer.hpp"



IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_indice_count(count)
{
	glGenBuffers(1, &m_bufferID); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);

	//Put data into the buffer generated by glGenBuffer
	//IndexBuffer GL_ELEMENT_ARRAY_BUFFER USED TO DRAW BY INDICIE
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,									//Tells OpenGL the type of buffer
		count * sizeof(unsigned int),								//Size in bytes of the new buffer
		data,														//pointer to the first data to be copied into the buffer
		GL_STATIC_DRAW												//Hint for draw mode
	);
}

IndexBuffer::~IndexBuffer() 
{
	glDeleteBuffers(1, &m_bufferID);
}


void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint)m_bufferID);
}


void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

