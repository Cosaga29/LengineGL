#pragma once
#include <vector>


/*
Class that contains all of the necessary data needed by openGL in order to build a VAO

Can either be populated from an obj file or manually
*/
struct GLData
{
	GLData() { size = 0; stride = 0; attributes = 0; indicies = 0; hasTexture = 0; hasNormal = 0; }

	unsigned int size;	//size in bytes
	unsigned int stride;	//stride of the data
	unsigned int attributes;	//how many different attributes were read
	unsigned int indicies;		//number of indicies read
	bool hasTexture;
	bool hasNormal;
	std::vector<float> data_out;	//raw data ready for VBO
	std::vector<unsigned int> out_indicies;	//raw index data for IBO
};