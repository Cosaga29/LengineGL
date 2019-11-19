#pragma once
#include "Texture.hpp"
#include "../outside/stb_image.h"

Texture::Texture(const std::string& path) 
	: m_rendererID(0), m_filePath(path), m_LocalBuffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
	//load image
	stbi_set_flip_vertically_on_load(1);	//needed because PNG is produced from top left to bottom right; openGL expects bottom left = 0,0
	//data where the pixel data is actually stored
	m_LocalBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);
	
	std::cout << std::hex;
	//print out byte data for testing
	//write a white line at the bottom of the picture to be displayed
	int pixelWidth = 15;
	for (unsigned i = 0; i < m_width * sizeof(unsigned int) * pixelWidth; i += 4) {
		//red channel
		m_LocalBuffer[i] = 0;
		//green channel
		m_LocalBuffer[i + 1] = 255;
		//blue channel
		m_LocalBuffer[i + 2] = 0;
		//alpha channel
		m_LocalBuffer[i + 3] = 255;
	}

	


	printf("Texture Pixel Width:\t%i\nTexture Pixel Height:\t%i\nNumber of 8-bit components per pixel:\t%i\n", m_width, m_height, m_BPP);
	if (!m_LocalBuffer) {
		std::cout << "Error loading texture" << std::endl;
	}

	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	//set up texture settings NEED TO SPECIFY
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));	//if image needs scaled down
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));	//if image needs scaled up
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));		
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//give open gl data from local buffer
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

/*
Function for setting up texture to raster from a raw data buffer
*/
Texture::Texture(unsigned char* data, int width, int height) 
	: m_rendererID(0), m_filePath(""), m_LocalBuffer(data), m_width(width), m_height(height), m_BPP(0)
{

	/*Create texture buffer in graphics memory*/
	GLCall(glGenTextures(1, &m_rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	//set up texture settings NEED TO SPECIFY
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));		//if image needs scaled down
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));		//if image needs scaled up
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//give open gl data from local buffer
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_rendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot)); //bind to first slot
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Refresh()
{
	//give open gl data from local buffer
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
}

/*
Function to write raw byte data in buffer to a file for inspection
*/
void Texture::writeToFile() const
{


}
