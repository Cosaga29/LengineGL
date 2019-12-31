#pragma once

#include <memory>
#include <map>

#include "Component.h"

typedef unsigned int ActorID;
typedef std::shared_ptr<Component> StrongComponentPtr;
typedef std::weak_ptr<Component> WeakComponentPtr;
typedef std::map<ComponentID, StrongComponentPtr> ActorComponents;

class Actor
{
public:

	ActorID m_id;
	ActorComponents m_components;

protected:
	virtual ~Actor();
	virtual void VOnUpdate(unsigned uElapsedTime) = 0;
	virtual void VOnInit() {};
	virtual void VOnDestroy() {};

};