#pragma once
#include <vector>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include "../outside/glm/glm.hpp"
#include "../gl_abstractions/Mesh.h"

/*
Eventually this class will be referred to as the "model loader" as the Model class encapsulates the 
underlying information needed by the VAO and VBO.

This class still needs to be tested with textures

ONLY USE WITH .OBJ
*/

struct packedVertex;

typedef std::map<struct packedVertex, unsigned int> VertexMap;
typedef std::unordered_map<std::string, int> ModeMap;

struct vec3
{
	float x, y, z;
};

struct vec2
{
	float u, v;
};


struct packedVertex
{
	vec3 position;
	vec2 texture;
	vec3 normal;
	bool operator<(const packedVertex v2) const
	{
		return memcmp((void*)this, &v2, sizeof(vec3) + sizeof(vec2) + sizeof(vec3)) > 0;
	};
};


class MeshLoader
{
public:

	std::vector<vec3> unique_position_data;	//v
	std::vector<vec3> unique_normal_data;	//vn
	std::vector<vec2> unique_texture_data;	//vt

	std::vector<unsigned int> pos_index;		//first f component 1/x/y 2/x/y 3/x/y
	std::vector<unsigned int> texture_index;	//second f component x/1/y x/2/y x/3/y
	std::vector<unsigned int> normal_index;		//third f component x/y/1 x/y/2 x/y/3

	std::vector<vec3> out_positions;
	std::vector<vec2> out_textures;
	std::vector<vec3> out_normals;

	bool hasTexture = 1;
	bool hasNormal = 1;

	VertexMap vert_map;	//one index'ed map of vertecies

	MeshLoader();

	Mesh* loadFromObj(const char* filepath);
	
};