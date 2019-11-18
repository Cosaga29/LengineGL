#include "Shader.hpp"
#include "Renderer.hpp"
#pragma once

Shader::Shader(const std::string& frag, const std::string& vert) :
	frag(frag), vert(vert), m_rendererID(0)
{
	m_rendererID = CreateShader(frag, vert);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_rendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_rendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniformMat4fv(const std::string& name, glm::mat4& matrix_value)
{

	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix_value)));

}

void Shader::SetUniform3fv(const std::string& name, glm::vec3& vector_value)
{

	GLCall(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vector_value)));

}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::BindAttribLocation(unsigned int index, const char* location)
{
	glBindAttribLocation(m_rendererID, index, location);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error handling for source code syntax
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Compilation failed: " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& fragment, const std::string& vertex)
{
	//vertexShader, fragmentShader - actual source code
	//read source code in from file
	std::ifstream fragCode(fragment);
	std::ifstream vertCode(vertex);

	if (!(fragCode.good() && vertCode.good()))
	{
		std::cout << "Error opening file\n" << std::endl;
		return 0;
	}

	//process files
	std::string fBuffer;
	std::string vBuffer;
	std::stringstream fss;
	std::stringstream vss;
	if (fragCode.good() && vertCode.good()) {
		while (std::getline(fragCode, fBuffer)) {
			fss << fBuffer;
			fss << "\n";
		}

		while (std::getline(vertCode, vBuffer)) {
			vss << vBuffer;
			vss << "\n";
		}
	}
	else {
		std::cout << "File could not be opened." << std::endl;
		return 0;
	}


	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vss.str().c_str());
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fss.str().c_str());

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
	//if location is not found
	if (m_uniformLocation.find(name) == m_uniformLocation.end()) {

		GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
		m_uniformLocation.insert(std::pair<std::string, int>({ name, location }));

		//error creating location, or name doesnt exist
		if (location == -1) {
			std::cout << "Uniform: " << name << " doesn't exist." << std::endl;
		}

		return location;
	}
	else {
		return m_uniformLocation[name];
	}
}
