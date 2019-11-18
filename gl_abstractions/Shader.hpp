#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <unordered_map>


class Shader {
private:

	const std::string frag;
	const std::string vert;

public:
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_uniformLocation;

public:
	//file to read shader data from
	Shader(const std::string& frag, const std::string& vert);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void BindAttribLocation(unsigned int index, const char* location);

private:

	unsigned int CompileShader(unsigned int type, const std::string& source);

	unsigned int CreateShader(const std::string& fragment, const std::string& vertex);

	int GetUniformLocation(const std::string& name);

};