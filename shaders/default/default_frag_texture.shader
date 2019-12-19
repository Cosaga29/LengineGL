#version 330 core
//drawn per pixel

//uniform vec3 rgb_color;
//in vec3 f_color;
uniform sampler2D texture_uniform;

in vec3 Normal;
in vec3 world_pos;
in vec2 fragTexCoord;


uniform vec3 lightPos;

out vec4 outColor;



void main()
{
	float ambient_value = 0.1;

	vec3 lightColor;
	lightColor.x = 1.0f; lightColor.y = 1.0f; lightColor.z = 1.0f;

	//get texture color value
	vec4 textureValue = vec4(texture(texture_uniform, fragTexCoord));
	vec3 objectColor;
	objectColor.x = textureValue.x;
	objectColor.y = textureValue.y;
	objectColor.z = textureValue.z;

	vec3 ambient = ambient_value * lightColor * objectColor;

	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - world_pos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;

	outColor = vec4(result, 1.0f); //rgba
}
