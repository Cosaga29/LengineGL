#include "Mesh.hpp"


/*
Function that checks to see if the packedVertex has been added to the map.
If it has, the index value is returned.

This function performs look up in O(1) time.
*/
inline bool contains(std::map<packedVertex, unsigned int>& m, struct packedVertex& pv, unsigned int& index)
{
	auto it = m.find(pv);
	if (it == m.end())
	{
		return false;
	}
	else {
		index = it->second;
		return true;
	}
}



Mesh::Mesh()
{
}


void Mesh::loadFromObj(const char* filename)
{

	std::string buffer;
	std::ifstream inputFile(filename);
	std::string mode;
	if (!inputFile.good())
	{
		std::cout << "Cannot open file" << std::endl;
		return;
	}

	std::map<std::string, int> mode_map;
	mode_map["v"] = 1;	//reading pos data
	mode_map["f"] = 2;	//read face data
	mode_map["vn"] = 3; //read normal data
	mode_map["vt"] = 4; //read texture data

	int slash_count;
	int data_count;

	while (std::getline(inputFile, buffer)) 
	{
		std::stringstream ss;
		std::string buf;
		ss << buffer;
		ss >> mode;
		float x, y, z;

		switch (mode_map[mode])
		{
		case 1: //v
			ss >> x;
			ss >> y;
			ss >> z;

			unique_position_data.push_back({x, y, z});
			break;

		case 2: //reading face data
			unsigned f, t, n;

			//determine how many // are in each face line
			slash_count = std::count(buffer.begin(), buffer.end(), '/');
			data_count = slash_count / 3;
			
			switch(data_count)
			{
			case 0:	//reading one set of data (position only)
				unsigned x, y, z;
				ss >> x;
				ss >> y;
				ss >> z;

				pos_index.push_back(x - 1);
				pos_index.push_back(y - 1);
				pos_index.push_back(z - 1);
				break;

			case 1: //reading position data + texture data
				for (int i = 0; i < 3; i++)
				{
					ss >> buf;
					sscanf_s(buf.c_str(), "%i/%i", &f, &t);
					pos_index.push_back(f - 1);
					texture_index.push_back(t - 1);
				}
				break;

			case 2:	//reading data + texture + normal
				if (buffer.find("//") != std::string::npos) //reading pos/normal only
				{
					//reading %i//%i format
					for (int i = 0; i < 3; i++)
					{
						ss >> buf;
						sscanf_s(buf.c_str(), "%i//%i", &f, &n);
						pos_index.push_back(f-1);
						normal_index.push_back(n-1);
					}

				}
				else //reading all three
				{
					for (int i = 0; i < 3; i++)
					{
						ss >> buf;
						sscanf_s(buf.c_str(), "%i/%i/%i", &f, &t, &n);
						pos_index.push_back(f-1);
						texture_index.push_back(t-1);
						normal_index.push_back(n-1);
					}
				}
				break;
			}

		case 3: //reading vn
			ss >> x;
			ss >> y;
			ss >> z;

			unique_normal_data.push_back({ x, y, z });
			break;

		case 4: //reading vt
			ss >> x;
			ss >> y;
			
			unique_texture_data.push_back({ x, y });
			break;
		}



	}


	//expand raw vertex data;
	std::vector<vec3> raw_position;
	std::vector<vec2> raw_texture;
	std::vector<vec3> raw_normal;

	if (unique_texture_data.size() == 0)
	{
		hasTexture = 0;
	}
	if (unique_normal_data.size() == 0)
	{
		hasNormal = 0;
	}

	if (unique_texture_data.size() == 0)
	{
		hasTexture = 0;
		//only expand positon and normals
		for (unsigned i = 0; i < pos_index.size(); i++)
		{
			raw_position.push_back(unique_position_data[pos_index[i]]);
			raw_normal.push_back(unique_normal_data[normal_index[i]]);
		}

		//verticies are now aligned in raw_position[i], raw_normal[i]
		for (unsigned i = 0; i < raw_position.size(); i++)
		{
			//build a packed vertex from the information
			packedVertex pv = { raw_position[i], {0.0f,0.0f}, raw_normal[i] };
			unsigned result;
			if (contains(vert_map, pv, result)) 
			{
				out_indicies.push_back(result);
			}
			else
			{
				out_positions.push_back(raw_position[i]);
				out_textures.push_back({ 0.0f, 0.0f });
				out_normals.push_back(raw_normal[i]);
				unsigned newIndexForMap = out_positions.size() - 1;
				out_indicies.push_back(newIndexForMap);
				vert_map[pv] = newIndexForMap;
			}
			
		}


		//build final packed raw vector of floats for openGL to load from
		for (int i = 0; i < out_positions.size(); i++)
		{
			data_out.push_back(out_positions[i].x);
			data_out.push_back(out_positions[i].y);
			data_out.push_back(out_positions[i].z);

			data_out.push_back(out_normals[i].x);
			data_out.push_back(out_normals[i].y);
			data_out.push_back(out_normals[i].z);
		}



	}
	else
	{
		hasTexture = 1;
		//expand position, texture, and normals
		for (int i = 0; i < pos_index.size(); i++)
		{
			raw_position.push_back(unique_position_data[pos_index[i]]);
			raw_normal.push_back(unique_normal_data[normal_index[i]]);
			raw_texture.push_back(unique_texture_data[texture_index[i]]);
		}

		//verticies are now aligned in raw_position[i], raw_normal[i]
		for (unsigned i = 0; i < raw_position.size(); i++)
		{
			//build a packed vertex from the information
			packedVertex pv = { raw_position[i], raw_texture[i], raw_normal[i] };
			unsigned result;
			if (contains(vert_map, pv, result))
			{
				out_indicies.push_back(result);
			}
			else
			{
				out_positions.push_back(raw_position[i]);
				out_textures.push_back(raw_texture[i]);
				out_normals.push_back(raw_normal[i]);
				unsigned newIndexForMap = out_positions.size() - 1;
				out_indicies.push_back(newIndexForMap);
				vert_map[pv] = newIndexForMap;
			}

		}


		//build final packed raw vector of floats for openGL to load from
		for (int i = 0; i < out_positions.size(); i++)
		{
			data_out.push_back(out_positions[i].x);
			data_out.push_back(out_positions[i].y);
			data_out.push_back(out_positions[i].z);

			data_out.push_back(out_textures[i].u);
			data_out.push_back(out_textures[i].v);

			data_out.push_back(out_normals[i].x);
			data_out.push_back(out_normals[i].y);
			data_out.push_back(out_normals[i].z);
		}

	}

}