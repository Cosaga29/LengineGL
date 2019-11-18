#pragma once


struct AttribLayout
{
	//index into the attrib array
	unsigned index;
	//how many floats per vertex
	int data_per_vertex;
	//specifies GL_TRUE/GL_FALSE for normalization
	bool normalize;
	//starting position of the data in the attribute
	unsigned data_position;
	//stride of the data
	unsigned data_stride;


	AttribLayout(unsigned index, int data_per_vertex, bool normalize, unsigned data_position, unsigned data_stride) :
		index(index), data_per_vertex(data_per_vertex), normalize(normalize), data_position(data_position), data_stride(data_stride) {}

};