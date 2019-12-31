#pragma once


struct MousePos
{
	double fMouseX;
	double fMouseY;
};

class KeyboardHandler
{
public:
	virtual bool VKeyPressed(unsigned int const code) = 0;
	virtual bool VKeyReleased(unsigned int const code) = 0;
	virtual bool VKeyHeld(unsigned int const code) = 0;
};

class MouseHandler
{

};