#include "Entity.h"
#include "../gl_abstractions/GlobalShader.h"


unsigned Entity::id_counter = 0;

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

void Entity::move(glm::vec3& direction)
{
//physics motion equations

}


void Entity::turn(glm::vec3& axis, float fTheta)
{
//physics motion equations


}