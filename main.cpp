#include <chrono>

#include "Application.hpp"
#include "Model.hpp"
#include "Scene.hpp"

#include "outside/glm/gtc/matrix_transform.hpp"
#include "outside/glm/gtc/type_ptr.hpp"

#include "gl_abstractions/VertexArray.hpp"
#include "gl_abstractions/Renderer.hpp"
#include "gl_abstractions/Shader.hpp"








class GraphicsApplication : public Application
{
public:
	GraphicsApplication(int width, int height) :
		Application(width, height) {}


	//declare variables here
	
	Scene* scene;
	Renderer* renderer;
	
	//Mesh testmesh;



	VertexArray* vao;
	Model* teapot;
	Shader* teapot_shader;

	//method to move the matrix defined in here into the vertex shader
	GLint uniTransZ;
	GLint uniTransX;

	//declare variables that make up view transformation

	//declare variable for storing the line from the camera to where its looking
	glm::vec3 camera_line;
	glm::vec3 light_pos;

	//model matrix and proj_matrix
	glm::mat4 proj_matrix;
	glm::mat4 model_matrix;

	//glm::mat4 mvp = proj_matrix * view_matrix * model_matrix;
	GLint uni_mvp;
	GLint uni_model_matrix;
	GLint uni_view_matrix;
	GLint uni_proj_matrix;
	GLint uni_camera_line;
	GLint uni_light_pos;

	float speed = 0.5f;

private:

	void inline processInput(GLFWwindow* window);

	virtual inline void updateWindowHeader() override;

	//void inline gl_clear() { glClearColor(0.0, 0.0, 0.0, 1.0); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	virtual int onCreate() override;

	/*Ran every frame*/
	virtual int onUpdate() override;

};


int GraphicsApplication::onCreate()
{

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	scene = new Scene();
	scene->AddObject("src/teapot_normals.obj", "shaders/frag.shader", "shaders/vert.shader");
	renderer = new Renderer();

	vao = new VertexArray();
	vao->Bind();


	teapot = new Model("src/teapot_normals.obj");
	teapot->Bind();

	//load and bind shader
	teapot_shader = new Shader("shaders/frag.shader", "shaders/vert.shader");
	teapot_shader->Bind();


	//build proj matrix
	proj_matrix = glm::perspective(glm::radians(90.0f), ((float)m_windowWidth / m_windowHeight), 0.1f, 1000.0f);

	//build model matrix
	model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 3.0f });

	//set initial light position
	light_pos = { 0.0f, 0.0f, -2.0f };
	teapot_shader->SetUniform3fv("lightPos", light_pos);

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



		//build camera every frame : renderer does this
		glm::mat4 view_matrix = glm::lookAt(
			scene->m_camera.eye_pos,		//position of the camera
			(scene->m_camera.eye_pos + scene->m_camera.look_at_pos),	//point to be at center of screen
			scene->m_camera.up_axis				//up axis
		);



		//build rotation matricies using time since app started for the theta value
		//renderer does this
		glm::mat4 rotateZ = glm::mat4(1.0f);
		glm::mat4 rotateX = glm::mat4(1.0f);
		auto now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(now - app_start).count();
		rotateZ = glm::rotate(rotateZ, speed * (0.5f) * time * glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		rotateX = glm::rotate(rotateX, speed * time * glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		//upload rotation matrix to gpu for use in vert shader

		teapot_shader->SetUniformMat4fv("rotateZ", rotateZ);
		teapot_shader->SetUniformMat4fv("rotateX", rotateX);

		//pass light vector to openGL
		teapot_shader->SetUniform3fv("lightPos", light_pos);

		//upload view matrix for changes in the vert shader
		teapot_shader->SetUniformMat4fv("model_matrix", model_matrix);
		teapot_shader->SetUniformMat4fv("view_matrix", view_matrix);
		teapot_shader->SetUniformMat4fv("proj_matrix", proj_matrix);

		




		renderer->Draw(*vao, *teapot, *teapot_shader);








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
