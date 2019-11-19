#pragma once

#include <unordered_map>
#include <memory>
#include <glew.h>

#include "outside/glm/gtc/matrix_transform.hpp"
#include "outside/glm/gtc/type_ptr.hpp"
#include "outside/glm/gtc/quaternion.hpp"
#include "gl_abstractions/VertexArray.hpp"
#include "gl_abstractions/Shader.hpp"

#ifndef DEFAULT_FRAG_SHADER
#define DEFAULT_FRAG_SHADER "shaders/default/default_frag.shader"
#endif

#ifndef DEFAULT_VERT_SHADER
#define DEFAULT_VERT_SHADER "shaders/default/default_vert.shader"
#endif


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

//this is the VertexArray's m_rendererID
typedef unsigned Object_ID;
typedef unsigned Shader_ID;

struct Transform
{
	Transform()
	{
		scale = { 1.0f, 1.0f, 1.0f };
		rotationAxis = { 0.0f, 1.0f, 0.0f };
		rotationQuat = { 1.0f, 0.0f, 0.0f , 0.0f };
		translation = { 0.0f, 0.0f, 0.0f };
	}

	//quaternion math: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
	inline void RotateX(const float& degrees) { this->rotationAxis = { 1.0f, 0.0f, 0.0f }; this->rotationQuat *= glm::angleAxis(glm::degrees(degrees), this->rotationAxis); }
	inline void RotateY(const float& degrees) { this->rotationAxis = { 0.0f, 1.0f, 0.0f }; this->rotationQuat *= glm::angleAxis(glm::degrees(degrees), this->rotationAxis); }
	inline void RotateZ(const float& degrees) { this->rotationAxis = { 0.0f, 0.0f, 1.0f }; this->rotationQuat *= glm::angleAxis(glm::degrees(degrees), this->rotationAxis); }

	glm::vec3 scale;
	glm::vec3 rotationAxis;
	glm::quat rotationQuat;
	glm::vec3 translation;
};

struct Camera
{
	// View
	glm::vec3 eye_pos;
	glm::vec3 look_at_pos;
	glm::vec3 up_axis;

	// Projection matrix (perspective)
	float fov;
	float aspect_ratio;
	float zNear;
	float zFar;
};

struct DiffuseLight
{
	glm::vec3 color;
	glm::vec3 position;
};


/*
Each object passed to the renderer will have a
	vao for vbo/ibo information
	transformation matrix (model matrix)
	Shader to be used 
*/
struct SceneObject
{
	SceneObject(VertexArray* vao, Transform* transform, Shader* shader) :
		vao(vao), transformation(transform), shader(shader)
	{}
	std::unique_ptr<VertexArray> vao;
	std::unique_ptr<Transform> transformation;
	std::unique_ptr<Shader> shader;
};


/*
Class that contains all the necessary information to render objects to the screen
*/

class Scene
{

public:

	//Each object has a vao(vbo + ibo), transformation model and a shader to be used
	std::vector<SceneObject*> objects_to_render;
	std::vector<SceneObject*> objects_loaded;

	std::unordered_map<std::string, SceneObject*> name_obj_map;

	Scene();
	Camera m_camera;
	DiffuseLight m_light;

	//add an object from a model file, a frag and vert shader, and give it a nickname
	bool LoadObject(const std::string& model_file, const std::string& name, const std::string& frag_shader = DEFAULT_FRAG_SHADER, const std::string& vert_shader = DEFAULT_VERT_SHADER);
	bool AddObject(const std::string& name);
	bool RemoveObject(const std::string& name);

	bool AddShader(std::string& frag_shader, std::string& vert_shader);
	void SetPerspective(float fov = 90.0f, float aspectRatio = 1.333, float fNear = 0.1f, float fFar = 1000.0f);
	
	inline bool isLoaded(const std::string& name) { return (name_obj_map.find(name) == name_obj_map.end()) ? 0 : 1; }
	inline void SetGlobalLightPos(const glm::vec3& light_pos = { 0.0f, 3.0f, 0.0f }) { m_light.position = light_pos; }
	inline void SetGlobalLightCol(const glm::vec3& light_col = { 1.0f, 1.0f, 1.0f }) { m_light.color = light_col; }


	SceneObject* getObjectByName(const std::string& object_name);
	SceneObject* getObjectById(Object_ID);

	Shader* getShaderById(Shader_ID);
	Shader* getShaderByName(std::string name);



};