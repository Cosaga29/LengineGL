#pragma once
#include <iostream>
#include "Renderer.hpp"

void GLClearError() {

	while (glGetError() != GL_NO_ERROR);	//clear all the error flags

}

bool GLLogError(const char* function, const char* file, int line) {

	while (GLenum error = glGetError()) {
		std::cout << "[Error]:\t " << error << "\n" <<
			function << " " << file << ": " << "On line number: " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	//draws the current bound buffer 
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
