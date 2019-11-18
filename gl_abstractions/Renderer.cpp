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

void Renderer::Draw(const VertexArray& va, unsigned int indicies, const Shader& shader) const
{

	//draws the current bound buffer 
	GLCall(glDrawElements(GL_TRIANGLES, indicies, GL_UNSIGNED_INT, nullptr));
}


//render scene
void Renderer::DrawScene(Scene& scene)
{

	//build projection matrix from the scene data
	glm::mat4 proj_matrix = glm::perspective(glm::radians(scene.m_camera.fov), scene.m_camera.aspect_ratio, scene.m_camera.zNear, scene.m_camera.zFar);

	//build view matrix to pass to shader program:
	glm::mat4 view_matrix = glm::lookAt(
		scene.m_camera.eye_pos,		//position of the camera
		(scene.m_camera.eye_pos + scene.m_camera.look_at_pos),	//point to be at center of screen
		scene.m_camera.up_axis				//up axis
	);


	//loop through every object in the scene and draw it occording to its shader
	for (int i = 0; i < scene.objects_to_render.size(); i++)
	{
		//upload the projection matrix and the view matrix to the vert shader
		scene.objects_to_render[i].shader->SetUniformMat4fv("proj_matrix", proj_matrix);
		scene.objects_to_render[i].shader->SetUniformMat4fv("view_matrix", view_matrix);


		//build model_matrix
		glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), scene.objects_to_render[i].transformation.get()->Translation);
		glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), scene.objects_to_render[i].transformation.get()->Scale);
		glm::mat4 rotation_matrix = glm::toMat4(glm::quat(scene.objects_to_render[i].transformation.get()->RotationAxis * scene.objects_to_render[i].transformation.get()->Rotation));
		glm::mat4 model_matrix = translate_matrix * rotation_matrix * scale_matrix;

		//upload the model_matrix
		scene.objects_to_render[i].shader->SetUniformMat4fv("model_matrix", model_matrix);


		scene.objects_to_render[i].vao.get()->Bind();
		GLCall(glDrawElements(GL_TRIANGLES, scene.objects_to_render[i].vao.get()->indicies, GL_UNSIGNED_INT, nullptr));
		scene.objects_to_render[i].vao.get()->Unbind();
	}

}

void Renderer::Clear() const
{
	glClearColor(0.0, 0.0, 0.0, 1.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
