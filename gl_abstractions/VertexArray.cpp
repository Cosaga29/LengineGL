#include "VertexArray.hpp"



/*
Constructor to call when loading data from file
*/
VertexArray::VertexArray(const std::string& filename) :
	m_rendererID(0), indicies(0), attributes(0), hasLayout(0)
{
	glGenVertexArrays(1, &m_rendererID);
	
	try
	{
		MeshLoader mesh_file;
		model_data.reset(mesh_file.loadFromObj(filename.c_str()));
		indicies = model_data->indicies;
	}
	catch (...)
	{
		std::cout << "Error loading data from file:\t" << filename << std::endl;
	}
}

/*
Constructor to call when loading a model from memory (pre-defined gl_data struct)
*/
VertexArray::VertexArray(struct gl_data* data) :
	m_rendererID(0), indicies(0), attributes(0), hasLayout(0)
{
	glGenVertexArrays(1, &m_rendererID);
	model_data.reset(data);
	indicies = model_data->indicies;
}


int VertexArray::initLayout()
{
	glBindVertexArray(m_rendererID);

	//populate vbo, ibo and attributes
	VertexBuffer vbo(model_data->data_out.data(), model_data->size);
	IndexBuffer ibo(model_data->out_indicies.data(), model_data->out_indicies.size());

	//vao, vbo and ibo are bound at this point: set attributes

	//set attrib pointer for position data in vbo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, model_data->stride * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	attributes++;

	if (model_data->hasTexture)
	{
		glVertexAttribPointer(attributes, 2, GL_FLOAT, GL_FALSE, model_data->stride * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(attributes);
		attributes++;
	}

	if (model_data->hasNormal)
	{
		glVertexAttribPointer(attributes, 3, GL_FLOAT, GL_FALSE, model_data->stride * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(attributes);
		attributes++;
	}

	//unbind for now
	glBindVertexArray(0);

	hasLayout = true;
	return attributes;

}

void VertexArray::Bind()
{
	glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

