#pragma once

#include "Entity.h"


class Player : public Entity
{


private:


public:

	Player(const std::string model);
	Player(Mesh& mesh);


	virtual void move(glm::vec3 direction);
	virtual void turn(glm::vec3 axis, float fTheta);

	virtual void interact(const Entity& other) = 0;
	virtual void attack(const Entity& other) = 0;
	virtual void defend(const Entity& other) = 0;


};