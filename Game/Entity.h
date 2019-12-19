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
	glm::vec3 acceleration;

	Entity();
	Entity(const std::string model, const std::string name = "");
	Entity(Mesh& entity, const std::string name = "");

	inline void PrintState() { std::cout << position.x << position.y << position.z << std::endl; }
	inline float GetSpeed() { return glm::length(velocity); };

	virtual void Move(float time);
	virtual void Turn(glm::vec3& axis, float fTheta);

	virtual void Interact(const Entity& other) = 0;
	virtual void Attack(const Entity& other) = 0;
	virtual void Defend(const Entity& other) = 0;



};