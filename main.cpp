#pragma once

#include <chrono>

#include "Renderer.hpp"
#include "Application.hpp"
#include "Scene.hpp"
#include "gl_abstractions/GLLine.hpp"



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);



/*
Class for creating a graphics application:
Consists of three main parts:
Declare variables to be used in the onUpdate and onCreate methods

onCreate is what is initialized at the beginning of the program
onUpdate is what is performed every frame while rendering

*/
class GraphicsApplication : public Application
{
public:
	GraphicsApplication(int width, int height) :
		Application(width, height) {}

	//declare variables here
	Scene* scene;
	Renderer* renderer;

	//NEXT: WORK ON ROTATIONS FOR OBJECTS
	glm::vec3 light_pos;
	glm::mat4 model_matrix;

	float speed = 0.5f;

private:

	void inline processInput(GLFWwindow* window);

	virtual inline void updateWindowHeader() override;

	virtual int onCreate() override;

	/*Ran every frame*/
	virtual int onUpdate() override;

};


int GraphicsApplication::onCreate()
{

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(m_window, key_callback);

	scene = new Scene();
	renderer = new Renderer();

	
	
	//separate loading and adding to a scene
	scene->LoadObject("src/teapot_normals.obj", "teapot");
	scene->LoadObject(new GLLine(X), "testlineX");
	scene->LoadObject(new GLLine(Y), "testlineY");
	scene->LoadObject(new GLLine(Z), "testlineZ");
	

	scene->getObjectByName("teapot")->transformation->translation = { 0.0f, 0.0f, 2.0f };
	scene->AddObject("teapot");


	scene->getObjectByName("testlineX")->transformation->scale = { 5.0, 5.0, 5.0 };
	scene->getObjectByName("testlineY")->transformation->scale = { 5.0, 5.0, 5.0 };
	scene->getObjectByName("testlineZ")->transformation->scale = { 5.0, 5.0, 5.0 };

	scene->getObjectByName("testlineX")->mode = LINES;
	scene->getObjectByName("testlineY")->mode = LINES;
	scene->getObjectByName("testlineZ")->mode = LINES;

	scene->getObjectByName("testlineX")->mode = LINES;
	scene->getObjectByName("testlineY")->mode = LINES;
	scene->getObjectByName("testlineZ")->mode = LINES;

	scene->AddObject("testlineX");
	scene->AddObject("testlineY");
	scene->AddObject("testlineZ");


	//set initial light position
	light_pos = { 0.0f, 0.0f, -2.0f };
	scene->SetGlobalLightPos(light_pos);

	//enable depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}



int GraphicsApplication::onUpdate()
{
	while (!glfwWindowShouldClose(m_window))
	{
		frame_start = std::chrono::high_resolution_clock::now();
		frame_time = std::chrono::duration_cast<std::chrono::duration<float>>(frame_start - frame_end).count(); //used for FPS calculation
		frame_end = frame_start;

		//clear screen & depth buffer
		renderer->Clear();

		//handle user input and mouse pitch yaw
		processInput(m_window);

		//rotate the teapot
		scene->getObjectByName("teapot")->transformation->RotateX(0.015f * frame_time);
		scene->getObjectByName("teapot")->transformation->RotateY(0.015f * frame_time);
		scene->getObjectByName("teapot")->transformation->RotateZ(0.015f * frame_time);

		//pass the scene to the renderer to draw
		renderer->DrawScene(*scene);


		glfwSwapBuffers(m_window);
		updateWindowHeader();
		glfwPollEvents();
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();

	return 0;
}


void GraphicsApplication::processInput(GLFWwindow* window) 
{
	if (!cursor_disabled)
	{
		return;
	}

	float cameraSpeed = 7.0f * frame_time;
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_window, GL_TRUE);
	}

	//control camera translation
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		scene->m_camera.eye_pos += cameraSpeed * scene->m_camera.look_at_pos;
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		scene->m_camera.eye_pos -= cameraSpeed * scene->m_camera.look_at_pos;
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		scene->m_camera.eye_pos -= glm::normalize(glm::cross(scene->m_camera.look_at_pos, scene->m_camera.up_axis	)) * cameraSpeed;
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		scene->m_camera.eye_pos += glm::normalize(glm::cross(scene->m_camera.look_at_pos, scene->m_camera.up_axis	)) * cameraSpeed;
	}
	if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
	{
		scene->m_camera.eye_pos.z += 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
	{
		scene->m_camera.eye_pos.z -= 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		scene->m_camera.eye_pos.y -= 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		scene->m_camera.eye_pos.y += 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		scene->m_light.position.y += 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		scene->m_light.position.y -= 0.1f;
	}



	//calculate the scene->m_camera.look_at_pos vector depending on the pitch and yaw of the mouse
	scene->m_camera.look_at_pos.x = cos(glm::radians(pitch)) * cos((glm::radians(yaw)));
	scene->m_camera.look_at_pos.y = sin(glm::radians(pitch));
	scene->m_camera.look_at_pos.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	scene->m_camera.look_at_pos = glm::normalize(scene->m_camera.look_at_pos);


}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key != GLFW_KEY_LEFT_ALT || action == GLFW_RELEASE) { return; }
	Application* this_app = (Application*)glfwGetWindowUserPointer(window);
	if (this_app->cursor_disabled)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	this_app->cursor_disabled = !this_app->cursor_disabled;
}




inline void GraphicsApplication::updateWindowHeader()
{

	ss << "FPS: " << std::setprecision(1) << (1.0f / frame_time) << std::setprecision(0) << "  M_pos: [" <<
		std::setw(4) << mouse_x << "] " << "[" <<
		std::setw(4) << mouse_y << "]   "; // Mouse XY [xxxx] [yyyy]
	ss << "MN: [" << std::setw(4) << std::setprecision(3) << std::fixed << (mouse_x / m_windowWidth) << "] " << "[" << (mouse_y / m_windowHeight) << "]";	//Mouse Normalized XY: [xxx] [yyy]
	ss << "  C_Pos: [" << scene->m_camera.eye_pos.x << ", " << scene->m_camera.eye_pos.y << ", " << scene->m_camera.eye_pos.z << "]";
	ss << "  L_pos: [" << scene->m_camera.look_at_pos.x << ", " << scene->m_camera.look_at_pos.y << ", " << scene->m_camera.look_at_pos.z << "]";

	glfwSetWindowTitle(m_window, ss.str().c_str());
	ss.str(std::string());

}





int main() {


	//Application app(800, 600);
	GraphicsApplication app(800, 600);
	app.run();


}
