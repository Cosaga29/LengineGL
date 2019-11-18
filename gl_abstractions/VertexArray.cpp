#include "VertexArray.hpp"


VertexArray::VertexArray() :
	m_rendererID(0), indicies(0)
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

void VertexArray::SetModel(Model* model)
{

	m_model.reset(model);
	indicies = model->indicies;
	model->Bind();

}

void VertexArray::Clear()
{

	m_model.release();

}
