#pragma once

#include <chrono>

#include "outside/glm/gtc/matrix_transform.hpp"
#include "outside/glm/gtc/type_ptr.hpp"

#include "gl_abstractions/VertexArray.hpp"
#include "gl_abstractions/Shader.hpp"

#include "Renderer.hpp"
#include "Application.hpp"
#include "Model.hpp"
#include "Scene.hpp"

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

	scene = new Scene();
	
	//separate loading and adding to a scene
	scene->AddObject("src/teapot_normals.obj", "teapot", "shaders/frag.shader", "shaders/vert.shader");
	scene->AddObject("src/bigger.obj", "deer", "shaders/frag.shader", "shaders/vert.shader");

	scene->getObjectByName("teapot")->shader->SetUniform3fv("lightPos", light_pos);
	scene->getObjectByName("deer")->transformation.get()->Translation = { 0.0f, -12.0f, 0.0f };
	
	renderer = new Renderer();

	//set initial light position
	light_pos = { 0.0f, 0.0f, -2.0f };
	//teapot_shader->SetUniform3fv("lightPos", light_pos);
	scene->getObjectByName("teapot")->shader->SetUniform3fv("lightPos", light_pos);
	scene->getObjectByName("deer")->shader->SetUniform3fv("lightPos", light_pos);


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


		//pass light vector to openGL
		scene->getObjectByName("teapot")->shader->SetUniform3fv("lightPos", light_pos);
		scene->getObjectByName("deer")->shader->SetUniform3fv("lightPos", light_pos);

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
		light_pos.y -= 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		light_pos.y += 0.1f;
	}

	//calculate the scene->m_camera.look_at_pos vector depending on the pitch and yaw of the mouse
	scene->m_camera.look_at_pos.x = cos(glm::radians(pitch)) * cos((glm::radians(yaw)));
	scene->m_camera.look_at_pos.y = sin(glm::radians(pitch));
	scene->m_camera.look_at_pos.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	scene->m_camera.look_at_pos = glm::normalize(scene->m_camera.look_at_pos);


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
