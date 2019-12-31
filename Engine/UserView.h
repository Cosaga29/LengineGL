#pragma once

#include "View.h"
#include "Actor.h"
#include "ScreenElement.h"
#include "InputDevice.h"
#include "../outside/glm/glm.hpp"

class UserView : public View
{
typedef std::map<ScreenID, std::shared_ptr<ScreenElement> > ScreenElements;

protected:

	ScreenElements m_elements;
	ActorID m_actorID;

	std::shared_ptr<KeyboardHandler> m_KeyboardHandler; //TODO: Work on these
	std::shared_ptr<MouseHandler> m_mouseHandler;

	float m_currTime; //current time in the program
	float m_lastRender; //time since last rendered frame

	virtual void RenderText() {};

public:
	//View Interface Overrides
	virtual void VOnRender(double fTime, float fElapsedTime) override; //draw all components on render
	virtual void VOnUpdate(unsigned uElapsedTime) override;
	inline virtual ViewType GetType() { return USER; };

	virtual void VSetCameraOffset(const glm::vec4& camOffset) {};

	void TogglePause(bool active);


};