#pragma once
#include "GLData.hpp"
#include "../outside/glm/glm.hpp"

enum LINE_DIRECTION
{
	Y = 0, X = 1, Z = 2
};

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
struct GLLine : public GLData
{
	GLLine(LINE_DIRECTION dir) :
		GLData() 
	{
		data_out.push_back(0.0f); data_out.push_back(0.0f); data_out.push_back(0.0f); //p1
		switch (dir)
		{
		case Y:
			data_out.push_back(0.0f); data_out.push_back(1.0f); data_out.push_back(0.0f); //p2
			break;
		case X:
			data_out.push_back(1.0f); data_out.push_back(0.0f); data_out.push_back(0.0f); //p2
			break;
		case Z:
			data_out.push_back(0.0f); data_out.push_back(0.0f); data_out.push_back(1.0f); //p2
			break;
		}

		out_indicies.push_back(0);
		out_indicies.push_back(1);

		size = data_out.size() * sizeof(float);
		stride = 0;

		attributes = 1;
		indicies = 2;
		hasTexture = false;
		hasNormal = false;

	}


};