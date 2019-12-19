#pragma once

#include "Entity.h"


class Player : public Entity
{


private:


public:

	Player();

	virtual void Interact(const Entity& other) override;
	virtual void Attack(const Entity& other) override;
	virtual void Defend(const Entity& other) override;


};