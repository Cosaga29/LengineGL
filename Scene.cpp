#include "Scene.hpp"

Scene::Scene()
{
	//stet up init position for camera
	m_camera.eye_pos = { 0.0f, 0.0f, 0.0f };
	m_camera.look_at_pos = { 2.0f, 1.0f, 3.0f };
	m_camera.up_axis = { 0.0f, 1.0f, 0.0f };

	m_light.color = { 1.0f, 1.0f, 1.0f }; //default white light
	m_light.position = { 0.0f, 0.0f, -2.0f };

	//set up a default perspective (can be changed with SetPerspective
	SetPerspective();

}

/*
Add an object to the scene to be rendered. fragshader and vert shader are optional
*/
bool Scene::AddObject(const std::string& model_file, const std::string& name, const std::string frag_shader, const std::string vert_shader)
{

	//create vao from the model_file given
	VertexArray* model_vao = new VertexArray();
	model_vao->Bind();

	//create model and bind it to VAO
	model_vao->SetModel(new Model(model_file.c_str()));

	//default transformation
	Transform* transformation = new Transform(
		{
		{1.0f, 1.0f, 1.0f},	//default scale
		{0.0f, 1.0f, 0.0f},	//default rotation axis
		{0.0f, 0.0f, 0.0f, 1.0f},	//default rotation quaternion
		{0.0f, 0.0f, 0.0f}	//default translation
		});

	Shader* model_shader = new Shader(frag_shader, vert_shader);
	objects_to_render.push_back(new SceneObject(model_vao, transformation, model_shader));
	model_shader->Unbind();

	//now that scene object has been added, make references to it by name
	name_obj_map[name] = objects_to_render.back();

	model_vao->Unbind();
	

	return true;
}

bool Scene::AddShader(std::string& frag_shader, std::string& vert_shader)
{
	return true;
}

void Scene::SetPerspective(float fov, float aspectRatio, float zNear, float zFar)
{

	this->m_camera.fov = fov;
	this->m_camera.aspect_ratio = aspectRatio;
	this->m_camera.zNear = zNear;
	this->m_camera.zFar = zFar;

}

SceneObject* Scene::getObjectByName(const std::string& object_name)
{
	// TODO: insert return statement here
	return name_obj_map[object_name];
}

SceneObject* Scene::getObjectById(Object_ID)
{
	// TODO: insert return statement here
	return 0;
}

Shader* Scene::getShaderById(Shader_ID)
{
	// TODO: insert return statement here
	return 0;
}

Shader* Scene::getShaderByName(std::string name)
{
	// TODO: insert return statement here
	return 0;
}
