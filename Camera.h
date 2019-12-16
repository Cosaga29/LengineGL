#pragma once

#include <glew.h>

#include "outside/glm/glm.hpp"
#include "outside/glm/gtc/matrix_transform.hpp"
#include "outside/glm/gtc/type_ptr.hpp"

struct Camera
{
	// View
	glm::vec3 eye_pos;
	glm::vec3 look_at_pos;
	glm::vec3 up_axis;
	glm::mat4 view_matrix;
	glm::mat4 proj_matrix;

	// Projection matrix (perspective)
	float fov;
	float aspect_ratio;
	float zNear;
	float zFar;
	
	inline void SetPerspective(float fov, float aspect_ratio, float zNear, float zFar) 
	{ 
		this->fov = fov;
		this->aspect_ratio = aspect_ratio;
		this->zNear = zNear;
		this->zFar = zFar;
	};

	inline void update()
	{
		view_matrix = glm::lookAt(eye_pos, (eye_pos + look_at_pos), up_axis);
		proj_matrix = glm::perspective(glm::radians(fov), aspect_ratio, zNear, zFar);
	}
};