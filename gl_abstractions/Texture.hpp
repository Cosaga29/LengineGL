#pragma once

#include <iomanip>

#include "GLLogger.hpp"

class Texture {

private:

	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_LocalBuffer;
	int m_width, m_height, m_BPP;


public:

	Texture(const std::string& path);
	Texture(unsigned char* data, int width, int height);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	inline GLint GetTexture() const { return m_rendererID; };

};