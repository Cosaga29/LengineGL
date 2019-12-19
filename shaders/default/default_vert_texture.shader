#version 330 core
//drawn per vertex


layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertTexCoord;
layout(location = 2) in vec3 normal;

uniform sampler2D texture_uniform;


uniform mat4 rotateZ;
uniform mat4 rotateX;

uniform mat4 model_matrix; //NEEDED
uniform mat4 view_matrix;  //NEEDED
uniform mat4 proj_matrix;  //NEEDED
uniform mat4 normal_matrix;

out vec3 Normal;
out vec2 fragTexCoord;
out vec3 world_pos;


void main() {

	fragTexCoord = vertTexCoord;

	world_pos = vec3(model_matrix * vec4(position, 1.0));

	Normal = vec3(normal_matrix * vec4(normal, 1.0));

	gl_Position = proj_matrix * view_matrix * vec4(world_pos, 1.0); //transform positions to view space
}
