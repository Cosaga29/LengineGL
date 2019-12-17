#pragma once

#include <unordered_map>
#include <map>
#include "Camera.h"
#include "Transform.h"
#include "SceneObject.h"

#ifndef DEFAULT_FRAG_SHADER
#define DEFAULT_FRAG_SHADER "shaders/default/default_frag.shader"
#endif

#ifndef DEFAULT_VERT_SHADER
#define DEFAULT_VERT_SHADER "shaders/default/default_vert.shader"
#endif


//this is the VertexArray's m_rendererID
typedef unsigned Object_ID;
typedef unsigned Shader_ID;

struct DiffuseLight
{
	glm::vec3 color;
	glm::vec3 position;
};


enum LOAD_FLAGS
{
	DEFAULT = 0
};

/*


Scene class:
This class stores the state of the world that will be rendered by the renderer.

The class defines: 
	transform struct that is used to build the model matrix
	Camera struct that stores the state of the proj_matrix and view_matrix (perspective and camera)
	The diffuse light struct stores a light position and color to be used in the world for lighting

The SceneObject:
	The scene object contains all of the information needed to render an object in the 3D world.
	The VAO is the openGL VAO, but encapsulated to store the necessary VBO and shader uniforms.

The Scene class works by storing a collection of all scene objects to be rendered.
A hash map is used to quickly relate the nickname of a model and it's data.

Objects in the scene can have their data modified and accessed:
scene.objects_to_render[i].transformation.get()->RotationAxis
scene.objects_to_render[i].transformation.get()->Rotation


*/


/*
Class that contains all the necessary information to render objects to the screen
*/

class Scene
{
private:

	//hashmap that stores name reference to the scene object
	std::unordered_map<std::string, SceneObject*> name_obj_map;
	//hashmap that stores name reference to index into objects_loaded vector for O(1) fast removal
	std::unordered_map<std::string, int> name_index_map;

public:

	//TODO: Sort contained by z-value to improve rendering
	std::vector<SceneObject*> visible_objects;
	std::vector<SceneObject*> objects_loaded;

	Scene();
	~Scene();

	Camera m_camera;
	DiffuseLight m_light;
	static Shader* m_globalShader;

	//add an object from a model file, a frag and vert shader, and give it a nickname
	bool LoadObject(const std::string& model_file, const std::string& name, LOAD_FLAGS flags = DEFAULT, const std::string& frag_shader = DEFAULT_FRAG_SHADER, const std::string& vert_shader = DEFAULT_VERT_SHADER);
	//bool LoadObject(const std::string& model_file, const std::string& name, Shader* shader = m_globalShader);
	bool LoadObject(Mesh* raw_obj, const std::string& name, const std::string& frag_shader = DEFAULT_FRAG_SHADER, const std::string& vert_shader = DEFAULT_VERT_SHADER);
	
	bool AddObject(const std::string& name);
	bool RemoveObject(const std::string& name);
	void ClearScene();

	bool AddShader(std::string& frag_shader, std::string& vert_shader);
	void SetPerspective(float fov = 65.0f, float aspectRatio = 1.333, float fNear = 0.1f, float fFar = 1000.0f);
	
	inline bool isLoaded(const std::string& name) { return (name_obj_map.find(name) == name_obj_map.end()) ? 0 : 1; }
	inline void SetGlobalLightPos(const glm::vec3& light_pos = { 0.0f, 3.0f, 0.0f }) { m_light.position = light_pos; }
	inline void SetGlobalLightCol(const glm::vec3& light_col = { 1.0f, 1.0f, 1.0f }) { m_light.color = light_col; }

	SceneObject* GetObjectByName(const std::string& object_name);
	SceneObject* GetObjectById(Object_ID);

	Shader* getShaderById(Shader_ID);
	Shader* getShaderByName(std::string name);



};