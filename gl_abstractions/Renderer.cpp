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

Renderer::Renderer()
{
}

void Renderer::Draw(const VertexArray& va, const Model& model, const Shader& shader) const
{

	//draws the current bound buffer 
	GLCall(glDrawElements(GL_TRIANGLES, model.indicies, GL_UNSIGNED_INT, nullptr));
}


//render scene
void Renderer::DrawScene(Scene& scene)
{
	//loop through every object in the scene and draw it occording to its shader


}

void Renderer::Clear() const
{
	glClearColor(0.0, 0.0, 0.0, 1.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
