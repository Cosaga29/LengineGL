#include "Application.hpp"


Application::Application(int width, int height) :
	mouse_x(0), mouse_y(0), sensitivity(0.10f), yaw(0), pitch(0), roll(0),
	m_windowWidth(width), m_windowHeight(height), frame_time(0), good(true), m_window(0), last_frame(0)
{
	bool init = true;

	if (!glfwInit())
	{
		std::cout << "GLFW Not initialized" << std::endl;
		init = false;
	}
	else 
	{
		std::cout << "Creating window... " << std::endl;
		m_window = glfwCreateWindow(width, height, "Application Window", NULL, NULL);
	}
	if (!m_window)
	{
		std::cout << "Window could not be created." << std::endl;
		glfwTerminate();
		init = false;
	}
	else
	{
		std::cout << "Window created successfully." << std::endl;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	//set mouse handler
	glfwSetCursorPosCallback(m_window, cursorPositionCallback);

	//init glew
	if (glewInit() != GLEW_OK) {
		std::cout << "Error!" << std::endl;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	/***************************************************************/

	//set a reference to this object so callback functions can change class data
	glfwSetWindowUserPointer(m_window, this);


	//set cursor position to middle of the screen
	mouse_x = width / 2; 
	mouse_y = height / 2;
	glfwSetCursorPos(m_window, mouse_x, mouse_y);

	good = init;

	ss << std::fixed << std::setfill('0');
}

int Application::onCreate()
{
	return 0;
}

int Application::onUpdate()
{

	//Render Loop
	while (!glfwWindowShouldClose(m_window))
	{
		frame_start = std::chrono::high_resolution_clock::now();
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}


		glfwSwapBuffers(m_window);


		frame_end = std::chrono::high_resolution_clock::now();
		frame_time = std::chrono::duration_cast<std::chrono::duration<float>>(frame_end - frame_start).count();
		updateWindowHeader();
		glfwPollEvents();
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();

	return 0;
}

void cursorPositionCallback(GLFWwindow* window, double x_pos, double y_pos)
{
	//get a handle to the class object containing the window
	Application* this_window = (Application*)glfwGetWindowUserPointer(window);

	//calculate the difference in position depending on what the last position was
	float x_difference = x_pos - this_window->mouse_x;
	float y_difference = this_window->mouse_y - y_pos;
	this_window->mouse_x = x_pos;
	this_window->mouse_y = y_pos;


	//change the values by the sensitivity value
	x_difference *= this_window->sensitivity;
	y_difference *= this_window->sensitivity;

	//update the yaw and pitch angles 
	this_window->yaw += x_difference;
	this_window->pitch += y_difference;

	if (this_window->pitch > 89.5f)
	{
		this_window->pitch = 89.5f;
	}
	if (this_window->pitch < -89.5f)
	{
		this_window->pitch = -89.5f;
	}


}

/*
Function that sets the header information of the window (called every frame in the loop)
*/
inline void Application::updateWindowHeader()
{
	frame_time = std::chrono::duration_cast<std::chrono::duration<float>>(frame_end - frame_start).count(); //used for FPS calculation
	ss << "FPS: " << std::to_string((1.0f / frame_time)) << "       Mouse XY: [" << mouse_x << "] " << "[" << mouse_y << "]   "; // Mouse XY [xxx] [yyy]
	ss << "Mouse Normalized XY: [" << (mouse_x / m_windowWidth) << "] " << "[" << (mouse_y / m_windowHeight) << "]";	//Mouse Normalized XY: [xxx] [yyy]

	glfwSetWindowTitle(m_window, ss.str().c_str());
	ss.str(std::string());
}

int Application::run()
{
	onCreate();
	app_start = std::chrono::high_resolution_clock::now();

	int exitCode;
	if (!(exitCode = onUpdate()))
	{
		std::cout << "Application Exited with return value: " << exitCode << std::endl;
	}
	else
	{
		std::cout << "Error exiting application." << exitCode << std::endl;
	}


	return 0;
}
