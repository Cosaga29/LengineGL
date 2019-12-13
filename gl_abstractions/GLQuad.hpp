#pragma once
#include "GLData.hpp"


/*
Class that is used by the scene class in order to build primitive lines.

This line class should strictly be used for debugging, as this data is passed to its own VAO


unsigned int size;	//size in bytes
unsigned int stride;	//stride of the data
unsigned int attributes;	//how many different attributes were read
unsigned int indicies;		//number of indicies read
bool hasTexture;
bool hasNormal;
std::vector<float> data_out;	//raw data ready for VBO
std::vector<unsigned int> out_indicies;	//raw index data for IBO
*/
struct GLQuad : public GLData
{
	GLQuad() :
		GLData()
	{
		data_out =
		{
			-1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f
		};

		out_indicies = { 0, 1, 2, 2, 3, 0};

		size = data_out.size() * sizeof(float);
		stride = 0;

		attributes = 1;
		indicies = out_indicies.size();
		hasTexture = false;
		hasNormal = false;

	}


};