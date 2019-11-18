#include "VAO.hpp"




VertexArrayObject::VertexArrayObject() :
	m_rendererID(0)
{
	glGenVertexArrays(1, &m_rendererID);
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(m_rendererID);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::AddBufferLayout(VertexBuffer& vbo, AttribLayout& attrib)
{
	buffer_attrib_pairs.push_back(std::pair< VertexBuffer, AttribLayout>(vbo, attrib));
	//bind attributes to the buffer
	glVertexAttribPointer(attrib.index, attrib.data_per_vertex, GL_FLOAT, attrib.normalize, attrib.data_position, (void*)attrib.data_stride);
	glEnableVertexAttribArray(attrib.index);

}
