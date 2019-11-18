#version 330 core
//drawn per vertex


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
//in vec3 position;
//in vec3 color;

//out vec3 f_color;
uniform mat4 rotateZ;
uniform mat4 rotateX;
//uniform mat4 mvp_matrix;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform vec3 camera_line;

out vec3 Normal;
out vec3 world_pos;

void main() {

	world_pos = vec3(model_matrix * vec4(position, 1.0));

	mat4 mvp_matrix = proj_matrix * view_matrix * model_matrix;

	Normal = normal;

	gl_Position = mvp_matrix * vec4(position, 1.0); //transform positions to view space
}
