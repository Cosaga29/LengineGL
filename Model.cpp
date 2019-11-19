#include "Model.hpp"


Model::Model(const char* filename) :
	stride(0), attributes(0), m_vboBufferID(0), m_vbo(0), m_ibo(0), verticies(0), indicies(0), hasTexture(1), hasNormal(1)
{

	Mesh mesh;
	std::unique_ptr<gl_data> file_data(mesh.loadFromObj(filename));


	m_vbo = new VertexBuffer(file_data->data_out.data(), file_data->size);
	m_vboBufferID = m_vbo->m_bufferID;

	if (!generateLayout(file_data.get()))
	{
		std::cout << "Error generating attributes..." << std::endl;
		return;
	}

	m_ibo = new IndexBuffer(file_data->out_indicies.data(), file_data->out_indicies.size());

	verticies = file_data->out_indicies.size();
	indicies = file_data->out_indicies.size();

}


/*
setting attrib pointers for the bound VAO
//Load position data into a vbo and bind it
vbo = new VertexBuffer(testmesh.data_out.data(), testmesh.data_out.size() * sizeof(float));
//vbo->Bind();
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
glEnableVertexAttribArray(0);
*/

int Model::generateLayout(gl_data* file_data)
{

	//set attrib pointer for position data in vbo
	int attributes_bound = 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, file_data->stride * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	attributes_bound++;

	if (file_data->hasTexture)
	{
		glVertexAttribPointer(attributes_bound, 2, GL_FLOAT, GL_FALSE, file_data->stride * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(attributes_bound);
		attributes_bound++;
	}

	if (file_data->hasNormal)
	{
		glVertexAttribPointer(attributes_bound, 3, GL_FLOAT, GL_FALSE, file_data->stride * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(attributes_bound);
		attributes_bound++;
	}

	return attributes_bound;

}


Model::~Model()
{
	delete(m_vbo);
	delete(m_ibo);
	m_vbo = 0;
	m_ibo = 0;
}

void Model::Bind()
{
	m_vbo->Bind();
	m_ibo->Bind();
}

void Model::Unbind()
{
	m_vbo->Unbind();
	m_ibo->Unbind();
}

void Model::Load(const char* filename)
{

}

void Model::Clear()
{

}
