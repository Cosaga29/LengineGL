#pragma once

#include "outside/glm/glm.hpp"
#include "outside/glm/gtc/matrix_transform.hpp"
#include "outside/glm/gtc/type_ptr.hpp"
#include "outside/glm/gtc/quaternion.hpp"
#include "outside/glm/gtx/quaternion.hpp"

struct Transform
{
	Transform()
	{
		scale = { 1.0f, 1.0f, 1.0f };
		rotationAxis = { 0.0f, 1.0f, 0.0f };
		rotationQuat = { 1.0f, 0.0f, 0.0f , 0.0f };
		translation = { 0.0f, 0.0f, 0.0f };
	}

	//quaternion math: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
	inline void RotateX(const float& degrees) { this->rotationAxis = { 1.0f, 0.0f, 0.0f }; this->rotationQuat *= glm::angleAxis(glm::degrees(degrees), this->rotationAxis); }
	inline void RotateY(const float& degrees) { this->rotationAxis = { 0.0f, 1.0f, 0.0f }; this->rotationQuat *= glm::angleAxis(glm::degrees(degrees), this->rotationAxis); }
	inline void RotateZ(const float& degrees) { this->rotationAxis = { 0.0f, 0.0f, 1.0f }; this->rotationQuat *= glm::angleAxis(glm::degrees(degrees), this->rotationAxis); }

	glm::vec3 scale;
	glm::vec3 rotationAxis;
	glm::quat rotationQuat;
	glm::vec3 translation;
};