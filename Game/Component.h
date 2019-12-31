#pragma once

#include <memory>

class Actor;

typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::weak_ptr<Actor> WeakActorPtr;
typedef unsigned int ComponentID;

class Component
{
public:

	StrongActorPtr pOwner;
	ComponentID m_id;

protected:

	virtual ~Component();
	virtual void VOnUpdate(unsigned uElapsedTime) = 0;
	virtual void VOnInit() = 0;
	virtual void VOnDestroy() = 0;

};