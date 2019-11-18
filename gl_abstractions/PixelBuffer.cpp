#include "PixelBuffer.hpp"

PixelBuffer::PixelBuffer(int img_width, int img_height)
	: m_data(0), m_width(img_width), m_height(img_height), m_size(0), bytesPerChannel(4)
{
	
	//allocate enough bytes to store the entire image
	m_data = (unsigned char*)malloc(bytesPerChannel * img_width * img_height * sizeof(unsigned char) * bytesPerChannel);
	assert(m_data != 0);
	m_size = img_width * img_height * bytesPerChannel * sizeof(unsigned char);

}

PixelBuffer::~PixelBuffer()
{
	free(m_data);
}


void PixelBuffer::Bind() const
{
	// after reading is complete back on the main thread
	//GLCall(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo_id));
	//glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mappe0dBuffer);
}

void PixelBuffer::Unbind() const
{
}
