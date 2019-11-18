#pragma once

#define GLEW_STATIC

#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <chrono>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <sstream>
#include <iomanip>

/*
Class that manages a window, mouse and key states.
This class is designed to be used as an interface; however, I have left some default behavior
in to remind myself how I build this.

*/

//extern double mouse_x;
//extern double mouse_y;

void cursorPositionCallback(GLFWwindow* window, double x_pos, double y_pos);

class Application
{
public:
	double mouse_x;
	double mouse_y;
	float sensitivity;
	float yaw;
	float pitch;
	float roll;

protected:

	int m_windowWidth;
	int m_windowHeight;
	float frame_time;
	bool good;
	std::stringstream ss;
	std::chrono::steady_clock::time_point app_start;
	std::chrono::steady_clock::time_point frame_end;
	std::chrono::steady_clock::time_point frame_start;
	float last_frame;

	GLFWwindow* m_window;
	virtual inline void updateWindowHeader();


public:
	int run();

	Application(int width, int height);

	virtual int onCreate();
	virtual int onUpdate();

};
