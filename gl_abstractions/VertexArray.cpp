#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_rendererID);
	glBindVertexArray(m_rendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_rendererID);
}

/*
Adding vertex buffers to the openGL VAO.
For each buffer do the following:
	bind it
	set it's layout

*/
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	/*
	Each element in the layout needs a glVertexAttribPointer created for it.
	*/
	for (unsigned i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i,										//specify which index of the vertex we are modifying
			element.count,							//components per vertex (two points per vertex)
			element.type,							//Tyoe of each data in the array
			element.normalized,						//normalize the data? No
			layout.GetStride(),						//stride between the vertex attribute (two floats between each vertex)
			(const void*)offset						//offset to the component we are modifying (position data starts at 0)
		);
		offset += element.count * AttribElement::GetTypeSize(element.type);
	}

}

void VertexArray::Bind() const
{
	glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
