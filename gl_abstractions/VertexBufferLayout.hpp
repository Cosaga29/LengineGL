#pragma once

#include "../Graphics/Renderer.hpp"
#include <cassert>
/*
Class that stores a particular layout for glVertexAttribPointer
*/

#include <glew.h>
#include <vector>

struct AttribElement {

	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetTypeSize(unsigned int type) 
	{
		switch (type) 
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		assert(false);
		return 0;
	}
};

class VertexBufferLayout {

private:

	std::vector<AttribElement> m_attrib_elements;
	unsigned int m_stride;


public:

	VertexBufferLayout() :
		m_stride(0) {};

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) 
	{
		m_attrib_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += AttribElement::GetTypeSize(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_attrib_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += AttribElement::GetTypeSize(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_attrib_elements.push_back({ GL_UNSIGNED_INT, count, GL_TRUE });
		m_stride += AttribElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
	}



	inline std::vector<AttribElement> GetElements() const { return m_attrib_elements; }
	inline unsigned int GetStride() const { return m_stride; }

};