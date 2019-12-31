#pragma once

#include <memory>

class View;

typedef unsigned int ScreenID;
typedef std::shared_ptr<View> StrongViewPtr;
typedef std::weak_ptr<View> WeakViewPtr;

class ScreenElement
{
public:

	StrongViewPtr pOwner;
	ScreenID m_id;

protected:
	virtual ~ScreenElement();
	virtual void VOnUpdate(unsigned uElapsedTime) = 0;
	virtual void VOnInit();
	virtual void VOnDestroy();
	virtual void Draw();



};