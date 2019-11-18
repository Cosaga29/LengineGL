#pragma once
#include <stdlib.h>
#include <cassert>
#include "glew.h"
#include "Renderer.hpp"

//TODO: Decide if using chars or unsigned int

struct Pixel {
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;
	unsigned char m_alpha;
};

class PixelBuffer {

public:
	unsigned char*	m_data;
	const int		m_width;
	const int		m_height;

private:

	int				m_size;
	int				bytesPerChannel;


public:

	PixelBuffer(int img_width, int img_height);
	~PixelBuffer();
	void Bind() const;
	void Unbind() const;

	inline int getSize() const { return m_size; }



};