#include "Model.hpp"


Model::Model(const char* filename) :
	stride(0), attributes(0), m_vboBufferID(0), m_vbo(0), m_ibo(0), verticies(0), indicies(0), hasTexture(1), hasNormal(1)
{

	Mesh mesh;
	mesh.loadFromObj(filename);
	vbo_data = mesh.data_out;
	ibo_data = mesh.out_indicies;

	stride = 8;
	attributes = 3;

	if (!mesh.hasNormal)
	{
		hasNormal = false;
		stride -= 3; // no xyz for normal
		attributes--;
	}
	if (!mesh.hasTexture)
	{
		hasTexture = false;
		stride -= 2; //no uv
		attributes--;
	}

	m_vbo = new VertexBuffer(vbo_data.data(), vbo_data.size() * sizeof(float));
	m_vboBufferID = m_vbo->m_bufferID;

	if (!generateLayout())
	{
		std::cout << "Error generating attributes..." << std::endl;
		return;
	}

	m_ibo = new IndexBuffer(ibo_data.data(), ibo_data.size());

	verticies = vbo_data.size();
	indicies = ibo_data.size();


}


/*
setting attrib pointers for the bound VAO
//Load position data into a vbo and bind it
vbo = new VertexBuffer(testmesh.data_out.data(), testmesh.data_out.size() * sizeof(float));
//vbo->Bind();
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
glEnableVertexAttribArray(0);
*/

int Model::generateLayout()
{

	//set attrib pointer for position data in vbo
	int attributes_bound = 0;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	attributes_bound++;

	if (hasTexture)
	{
		glVertexAttribPointer(attributes_bound, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(attributes_bound);
		attributes_bound++;
	}

	if (hasNormal)
	{
		glVertexAttribPointer(attributes_bound, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
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
