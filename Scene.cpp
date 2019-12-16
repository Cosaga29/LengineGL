#include "Scene.hpp"

Scene::Scene()
{
	//stet up init position for camera
	m_camera.eye_pos = { 0.0f, 0.0f, 0.0f };
	m_camera.look_at_pos = { 2.0f, 1.0f, 3.0f };
	m_camera.up_axis = { 0.0f, 1.0f, 0.0f };
	
	//set up a default perspective (can be changed with SetPerspective
	SetPerspective();

	m_camera.update();
	
	m_light.color = { 1.0f, 1.0f, 1.0f }; //default white light
	m_light.position = { 0.0f, 0.0f, -2.0f };

}

Scene::~Scene()
{
	ClearScene();
}

/*
Add an object to the loaded objects containers. fragshader and vert shader are optional
The object must be made visible and added to the visible objects container
*/
bool Scene::LoadObject(const std::string& model_file, const std::string& name, const std::string& frag_shader, const std::string& vert_shader)
{

	printf("Scene:\nLoading Object [%i]:\t%s\n%s\tFragment Shader: %s\n\tVertex Shader: %s\n\n\n", objects_loaded.size(), name.c_str(), model_file.c_str(), frag_shader.c_str(), vert_shader.c_str());

	//create scene object from file
	objects_loaded.push_back
	(
		new SceneObject(new VertexArray(model_file.c_str()), new Transform(), new Shader(frag_shader, vert_shader))
	);

	//now that scene object has been added, make references to it by name
	name_obj_map[name] = objects_loaded.back();

	return true;
}


/*
Add an object to the loaded objects containers. fragshader and vert shader are optional
The object must be made visible and added to the visible objects container
*/
bool Scene::LoadObject(Mesh* raw_obj, const std::string& name, const std::string& frag_shader, const std::string& vert_shader)
{

	//printf("Scene:\nLoading Object [%i]:\t%s\n%s\tFragment Shader: %s\n\tVertex Shader: %s\n\n\n", objects_loaded.size(), name.c_str(), model_file.c_str(), frag_shader.c_str(), vert_shader.c_str());
		//create scene object from file
	objects_loaded.push_back
	(
		new SceneObject(new VertexArray(raw_obj), new Transform(), new Shader(frag_shader, vert_shader))
	);

	//now that scene object has been added, make references to it by name
	name_obj_map[name] = objects_loaded.back();

	return true;
}


/*
Function that adds a loaded object to the scene, if that object has been loaded.
*/
bool Scene::AddObject(const std::string& name)
{
	if (isLoaded(name))
	{
		visible_objects.push_back(GetObjectByName(name));
	}

	return false;
}

/*
Function that removes a loaded object 
*/
bool Scene::RemoveObject(const std::string& name)
{
	return false;
}

void Scene::ClearScene()
{
	for (unsigned i = 0; i < objects_loaded.size(); i++)
	{
		delete objects_loaded[i];
	}
	for (unsigned i = 0; i < visible_objects.size(); i++)
	{
		if (visible_objects[i])
		{
			delete visible_objects[i];
		}
	}

	visible_objects.clear();
	objects_loaded.clear();

}

bool Scene::AddShader(std::string& frag_shader, std::string& vert_shader)
{
	return true;
}

void Scene::SetPerspective(float fov, float aspectRatio, float zNear, float zFar)
{

	m_camera.SetPerspective(fov, aspectRatio, zNear, zFar);

}

SceneObject* Scene::GetObjectByName(const std::string& object_name)
{
	// TODO: insert return statement here
	return name_obj_map[object_name];

}

SceneObject* Scene::GetObjectById(Object_ID)
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
