#include <chrono>

#include "Application.hpp"
#include "Mesh.hpp"

#include "Model.hpp"

#include "gl_abstractions/VertexBuffer.hpp"
#include "gl_abstractions/IndexBuffer.hpp"
#include "gl_abstractions/Shader.hpp"

#include "outside/glm/gtc/matrix_transform.hpp"
#include "outside/glm/gtc/type_ptr.hpp"


class GraphicsApplication : public Application
{
public:
	GraphicsApplication(int width, int height) :
		Application(width, height) {}


	//declare variables here
	GLuint vao;
	Mesh testmesh;
	VertexBuffer* vbo;
	IndexBuffer* ibo;

	Model* teapot;

	//method to move the matrix defined in here into the vertex shader
	GLint uniTransZ;
	GLint uniTransX;

	//declare variables that make up view transformation
	glm::vec3 eye_pos;
	glm::vec3 look_at_pos;
	glm::vec3 up_axis;

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

	void inline gl_clear() { glClearColor(0.0, 0.0, 0.0, 1.0); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	virtual int onCreate() override;

	/*Ran every frame*/
	virtual int onUpdate() override;

};


int GraphicsApplication::onCreate()
{

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//generate vertex array object: holds vertex buffer, shader, and index buffer state
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	teapot = new Model("src/teapot_normals.obj");
	teapot->Bind();


	/*
	testmesh.loadFromObj("src/teapot_normals.obj");
	vbo = new VertexBuffer(testmesh.data_out.data(), testmesh.data_out.size() * sizeof(float));
	vbo->Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//Load normal data into a vbo and bind it
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);


	//Load index data from mesh into ibo and bind it
	ibo = new IndexBuffer(testmesh.out_indicies.data(), testmesh.out_indicies.size());
	ibo->Bind();
	*/
	
	
	
	//load and bind shader
	Shader gl_shader("src/frag.shader", "src/vert.shader");
	gl_shader.Bind();


	uniTransZ = glGetUniformLocation(gl_shader.m_rendererID, "rotateZ");
	uniTransX = glGetUniformLocation(gl_shader.m_rendererID, "rotateX");


	//declare variables for starting camera position
	eye_pos = { 0.0f, 0.0f, 5.0f };
	look_at_pos = { 0.0f, 0.0f, -1.0f };
	up_axis = { 0.0f, 1.0f, 0.0f };

	//build proj matrix
	proj_matrix = glm::perspective(glm::radians(90.0f), ((float)m_windowWidth / m_windowHeight), 0.1f, 1000.0f);

	//build model matrix
	model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 1.0f });

	//set uniforms to upload matrix data into vertex shader
	uni_mvp = glGetUniformLocation(gl_shader.m_rendererID, "mvp_matrix");
	uni_model_matrix = glGetUniformLocation(gl_shader.m_rendererID, "model_matrix");
	uni_view_matrix = glGetUniformLocation(gl_shader.m_rendererID, "view_matrix");
	uni_proj_matrix = glGetUniformLocation(gl_shader.m_rendererID, "proj_matrix");

	uni_camera_line = glGetUniformLocation(gl_shader.m_rendererID, "camera_line");
	uni_light_pos = glGetUniformLocation(gl_shader.m_rendererID, "lightPos");

	//LIGHTING
	light_pos = { 0.0f, 0.0f, -2.0f };
	glUniform3fv(uni_light_pos, 1, glm::value_ptr(light_pos));

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
		gl_clear();

		//handle user input and mouse pitch yaw
		processInput(m_window);

		//build camera every frame
		glm::mat4 view_matrix = glm::lookAt(
			eye_pos,		//position of the camera
			(eye_pos + look_at_pos),	//point to be at center of screen
			up_axis			//up axis
		);

		//calculate line from the camera to where its looking
		camera_line = (eye_pos)-(eye_pos - look_at_pos);

		//pass line to openGL
		glUniform3fv(uni_camera_line, 1, glm::value_ptr(camera_line));

		//pass light vector to openGL
		glUniform3fv(uni_light_pos, 1, glm::value_ptr(light_pos));



		//calculate the look_at_pos vector depending on the pitch and yaw of the mouse
		look_at_pos.x = cos(glm::radians(pitch)) * cos((glm::radians(yaw)));
		look_at_pos.y = sin(glm::radians(pitch));
		look_at_pos.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		look_at_pos = glm::normalize(look_at_pos);


		//build rotation matricies using time since app started for the theta value
		glm::mat4 rotateZ = glm::mat4(1.0f);
		glm::mat4 rotateX = glm::mat4(1.0f);
		auto now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(now - app_start).count();
		rotateZ = glm::rotate(rotateZ, speed * (0.5f) * time * glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		rotateX = glm::rotate(rotateX, speed * time * glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		//upload rotation matrix to gpu for use in vert shader
		glUniformMatrix4fv(uniTransZ, 1, GL_FALSE, glm::value_ptr(rotateZ)); //how many matricies to upload, matrix should be transposed? last param: converts matrix to 4x4 floats
		glUniformMatrix4fv(uniTransX, 1, GL_FALSE, glm::value_ptr(rotateX)); //how many matricies to upload, matrix should be transposed? last param: converts matrix to 4x4 floats

		//upload view matrix for changes in the vert shader
		glUniformMatrix4fv(uni_model_matrix, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(uni_view_matrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(uni_proj_matrix, 1, GL_FALSE, glm::value_ptr(proj_matrix));

		

		glDrawElements(GL_TRIANGLES, teapot->indicies, GL_UNSIGNED_INT, 0);

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
		eye_pos += cameraSpeed * look_at_pos;
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		eye_pos -= cameraSpeed * look_at_pos;
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		eye_pos -= glm::normalize(glm::cross(look_at_pos, up_axis)) * cameraSpeed;
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		eye_pos += glm::normalize(glm::cross(look_at_pos, up_axis)) * cameraSpeed;
	}
	if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
	{
		eye_pos.z += 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
	{
		eye_pos.z -= 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		eye_pos.y -= 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		eye_pos.y += 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		light_pos.y -= 0.1f;
	}
	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		light_pos.y += 0.1f;
	}

	//calculate the look_at_pos vector depending on the pitch and yaw of the mouse
	look_at_pos.x = cos(glm::radians(pitch)) * cos((glm::radians(yaw)));
	look_at_pos.y = sin(glm::radians(pitch));
	look_at_pos.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	look_at_pos = glm::normalize(look_at_pos);


}



inline void GraphicsApplication::updateWindowHeader()
{

	ss << "FPS: " << std::setprecision(1) << (1.0f / frame_time) << std::setprecision(0) << "  M_pos: [" <<
		std::setw(4) << mouse_x << "] " << "[" <<
		std::setw(4) << mouse_y << "]   "; // Mouse XY [xxxx] [yyyy]
	ss << "MN: [" << std::setw(4) << std::setprecision(3) << std::fixed << (mouse_x / m_windowWidth) << "] " << "[" << (mouse_y / m_windowHeight) << "]";	//Mouse Normalized XY: [xxx] [yyy]
	ss << "  C_Pos: [" << eye_pos.x << ", " << eye_pos.y << ", " << eye_pos.z << "]";
	ss << "  L_pos: [" << look_at_pos.x << ", " << look_at_pos.y << ", " << look_at_pos.z << "]";

	glfwSetWindowTitle(m_window, ss.str().c_str());
	ss.str(std::string());

}





int main() {


	//Application app(800, 600);
	GraphicsApplication app(800, 600);
	app.run();

	//Mesh testmesh;
	//testmesh.loadFromObj("src/teapot_normals.obj");

}
