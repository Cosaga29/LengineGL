#pragma once
#include "Renderer.hpp"
#include <iomanip>

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
	void Refresh();

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

	void writeToFile() const;


};