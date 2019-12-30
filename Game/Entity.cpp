#include "Entity.h"
#include "../gl_abstractions/GlobalShader.h"


unsigned Entity::id_counter = 0;

Entity::Entity() :
	e_id(id_counter++), position(0), velocity(0), acceleration(0)
{
	this->name = "default" + std::to_string(e_id);
}

Entity::Entity(const std::string model, const std::string name) :
	e_id(id_counter++)
{
	//load the mesh
	MeshLoader ml;
	this->m_mesh.reset(ml.loadFromObj(model.c_str()));
	this->name = name;
}

Entity::Entity(Mesh& mesh_model, const std::string name) :
	e_id(id_counter++), m_mesh(&mesh_model), name(name)
{
}

void Entity::Update(float time)
{
//physics motion equations

	velocity += time * acceleration;
	position += velocity * time + ((0.5f)*acceleration*(time*time));

}


void Entity::Turn(glm::vec3& axis, float fTheta)
{
//physics motion equations


}