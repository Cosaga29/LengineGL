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
#define DEFAULT_FRAG_SHADER "../shaders/default/default_frag.shader"
#endif

#ifndef DEFAULT_VERT_SHADER
#define DEFAULT_VERT_SHADER "../shaders/default/default_vert.shader"
#endif

//this is the VertexArray's m_rendererID
typedef unsigned Object_ID;
typedef unsigned Shader_ID;

struct Transform
{
	glm::vec3 Scale;
	glm::vec3 RotationAxis;
	glm::quat Rotation;
	glm::vec3 Translation;
};

struct Camera
{
	// View
	glm::vec3 eye_pos;
	glm::vec3 look_at_pos;
	glm::vec3 up_axis;

	// Projection
	float fov;
	float aspect_ratio;
	float ZNear;
	float ZFar;
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
	//std::unordered_map<std::string, VertexArray> vao_models;

	//std::unordered_map<std::string, Shader> shaders;

	std::vector<SceneObject> objects_to_render;
	std::unordered_map<std::string, SceneObject*> name_obj_map;

	Scene();
	Camera m_camera;
	DiffuseLight m_light;

	bool AddObject(std::string model_file, std::string frag_shader = DEFAULT_FRAG_SHADER, std::string vert_shader = DEFAULT_VERT_SHADER);
	bool AddShader(std::string frag_shader, std::string vert_shader);

	SceneObject* getObjectByName(std::string& object_name);
	SceneObject* getObjectById(Object_ID);

	Shader* getShaderById(Shader_ID);
	Shader* getShaderByName(std::string name);



};