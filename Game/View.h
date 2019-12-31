#pragma once

class View
{
public:
	enum ViewType
	{
		DEFAULT,
		GAME,
		USER,
		AI
	};

public:

	unsigned m_viewID;

	virtual void VOnRender(double fTime, float fElapsedTime) = 0;
	virtual void VOnUpdate(unsigned uElapsedTime) = 0;
	inline virtual ViewType GetType() = 0;


};