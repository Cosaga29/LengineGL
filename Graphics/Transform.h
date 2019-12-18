#pragma once

#include "../outside/glm/glm.hpp"
#include "../outside/glm/gtc/matrix_transform.hpp"
#include "../outside/glm/gtc/type_ptr.hpp"
#include "../outside/glm/gtc/quaternion.hpp"
#include "../outside/glm/gtx/quaternion.hpp"

struct Transform
{
	Transform()
	{
		scale = { 1.0f, 1.0f, 1.0f };
		rotationAxis = { 0.0f, 1.0f, 0.0f };
		rotationQuat = { 1.0f, 0.0f, 0.0f , 0.0f };
		translation = { 0.0f, 0.0f, 0.0f };

		translation_matrix = glm::translate(glm::mat4(1.0f), translation);
		scale_matrix = glm::scale(glm::mat4(1.0f), scale);
		rotation_matrix = glm::toMat4(glm::quat(rotationQuat));
	}

	//quaternion math: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
	inline void RotateX(const float& degrees) { this->rotationAxis = { 1.0f, 0.0f, 0.0f }; this->rotationQuat *= glm::angleAxis(glm::degrees(degrees), this->rotationAxis); }
	inline void RotateY(const float& degrees) { this->rotationAxis = { 0.0f, 1.0f, 0.0f }; this->rotationQuat *= glm::angleAxis(glm::degrees(degrees), this->rotationAxis); }
	inline void RotateZ(const float& degrees) { this->rotationAxis = { 0.0f, 0.0f, 1.0f }; this->rotationQuat *= glm::angleAxis(glm::degrees(degrees), this->rotationAxis); }

	glm::vec3 scale;
	glm::vec3 rotationAxis;
	glm::quat rotationQuat;
	glm::vec3 translation;

	//testing:
	glm::mat4 translation_matrix;
	glm::mat4 scale_matrix;
	glm::mat4 rotation_matrix;
	glm::mat4 model_matrix;
	glm::mat4 normal_matrix;

	//only call when the model has been moved
	inline void UpdateModel()
	{
		//build model_matrix
		translation_matrix = glm::translate(glm::mat4(1.0f), translation);
		scale_matrix = glm::scale(glm::mat4(1.0f), scale);
		rotation_matrix = glm::toMat4(glm::quat(rotationQuat));
		model_matrix = translation_matrix * rotation_matrix * scale_matrix;
		normal_matrix = glm::mat4(glm::transpose(glm::inverse(model_matrix)));
	}

};