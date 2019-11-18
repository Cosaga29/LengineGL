#include "VertexArray.hpp"


VertexArray::VertexArray() :
	m_rendererID(0)
{
	glGenVertexArrays(1, &m_rendererID);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::AddModel(Model& model)
{

	buffer_models.push_back(model);
	model.Bind();

}

void VertexArray::Clear()
{

	buffer_models.clear();

}
