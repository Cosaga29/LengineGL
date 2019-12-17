#include "Renderer.h"

Renderer::Renderer()
{
}

//render scene
void Renderer::DrawScene(const Scene& scene)
{

	/* For all objects to be rendered, draw them*/
	for (auto const &obj : scene.visible_objects)
	{
		//TODO: Batch this or change to single upload for the global shader
		//upload camera data into shader
		obj->shader->SetUniformMat4fv("proj_matrix", scene.m_camera.proj_matrix);
		obj->shader->SetUniformMat4fv("view_matrix", scene.m_camera.view_matrix);

		//fetch normal matrix and pass to shader
		obj->shader->SetUniformMat4fv("normal_matrix", obj->transformation->normal_matrix);

		//fetch model matrix and pass to shader
		obj->shader->SetUniformMat4fv("model_matrix", obj->transformation->model_matrix);

		//set the global light_pos
		obj->shader->SetUniform3fv("lightPos", scene.m_light.position);

		//bind VAO for the object
		obj->vao->Bind();
		obj->shader->Bind();

		//determine draw mode based on object's mode
		switch (obj->mode)
		{
		case TRIANGLES:
			GLCall(glDrawElements(GL_TRIANGLES, obj->vao->indicies, GL_UNSIGNED_INT, nullptr));
			break;

		case LINES:
			GLCall(glDrawElements(GL_LINES, obj->vao->indicies, GL_UNSIGNED_INT, nullptr));
			break;
		}

		obj->vao->Unbind();
		obj->shader->Unbind();
	}


}

void Renderer::Clear() const
{
	glClearColor(0.0, 0.0, 0.0, 1.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

