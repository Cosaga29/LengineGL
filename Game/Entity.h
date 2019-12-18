#pragma once

#include <string>
#include <memory>
#include "../Graphics/ObjMeshLoader.h"
#include "../gl_abstractions/Mesh.h"
#include "../outside/glm/glm.hpp"
#include "../Graphics/SceneObject.h"


class Entity
{
protected:

	static unsigned id_counter;

public:

	unsigned e_id;
	std::string name;
	std::unique_ptr<Mesh> m_mesh;
	glm::vec3 position; //xyz
	glm::vec3 velocity; 

	Entity(const std::string model, const std::string name = "");
	Entity(Mesh& entity, const std::string name = "");

	inline float GetSpeed() { return glm::length(velocity); };

	virtual void move(glm::vec3& direction);
	virtual void turn(glm::vec3& axis, float fTheta);

	virtual void interact(const Entity& other) = 0;
	virtual void attack(const Entity& other) = 0;
	virtual void defend(const Entity& other) = 0;


};