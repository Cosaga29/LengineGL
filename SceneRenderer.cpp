#include "SceneRenderer.h"

Renderer::Renderer()
{
}

void Renderer::DrawObj(const Scene& scene, const SceneObject& obj) const
{
	obj.shader->SetUniformMat4fv("proj_matrix", scene.m_camera.proj_matrix);
	obj.shader->SetUniformMat4fv("view_matrix", scene.m_camera.view_matrix);

	//build model_matrix
	glm::mat4 translate_matrix = glm::translate(glm::mat4(1.0f), obj.transformation.get()->translation);
	glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), obj.transformation.get()->scale);
	glm::mat4 rotation_matrix = glm::toMat4(glm::quat(obj.transformation.get()->rotationQuat));
	glm::mat4 model_matrix = translate_matrix * rotation_matrix * scale_matrix;

	//build normal matrix to pass to shader program:
	glm::mat4 normal_matrix = glm::mat4(glm::transpose(glm::inverse(model_matrix)));
	obj.shader->SetUniformMat4fv("normal_matrix", normal_matrix);

	//upload the model_matrix
	obj.shader->SetUniformMat4fv("model_matrix", model_matrix);

	//set the global light_pos
	obj.shader->SetUniform3fv("lightPos", scene.m_light.position);

	//bind VAO for the object
	obj.vao->Bind();
	obj.shader->Bind();

	//determine draw mode based on object's mode
	switch (obj.mode)
	{
	case TRIANGLES:
		GLCall(glDrawElements(GL_TRIANGLES, obj.vao->indicies, GL_UNSIGNED_INT, nullptr));
		break;

	case LINES:
		GLCall(glDrawElements(GL_LINES, obj.vao->indicies, GL_UNSIGNED_INT, nullptr));
		break;
	}

	obj.vao->Unbind();
	obj.shader->Unbind();

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
