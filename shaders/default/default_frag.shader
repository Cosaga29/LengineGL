#version 330 core
//drawn per pixel

//uniform vec3 rgb_color;
//in vec3 f_color;
in vec3 Normal;
in vec3 world_pos;

uniform vec3 lightPos;

out vec4 outColor;



void main()
{

	float ambient_light_value = 0.1;
	vec3 lightColor;
	lightColor.x = 1.0f; lightColor.y = 1.0f; lightColor.z = 1.0f;

	vec3 objectColor;
	objectColor.x = 1.0f; objectColor.y = 1.0f; objectColor.z = 1.0f;

	vec3 ambient = ambient_light_value * lightColor;

	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - world_pos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;

	//outColor = vec4(f_color, 1.0f);
	outColor = vec4(result, 1.0f); //rgba
}
