#include "mesh.h"
#include "state.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include <iostream>

inline std::string extractPath(std::string filename) {
	while (filename.find('\\') != std::string::npos)
		filename.replace(filename.find('\\'), 1, 1, '/');
	size_t pos = filename.rfind('/');
	if (pos == std::string::npos) return "";
	filename = filename.substr(0, pos);
	if (filename.size() > 0) filename += '/';
	return filename;
}

template<typename T>
std::vector<T> splitString(const std::string& str, char delim) {
	std::vector<T> elems;
	if (str != "") {
		std::stringstream ss(str);
		std::string item;
		while (std::getline(ss, item, delim)) {
			T value;
			std::stringstream ss2(item);
			ss2 >> value;
			elems.push_back(value);
		}
	}
	return elems;
}

std::shared_ptr<Mesh> Mesh::load(const char * filename, const std::shared_ptr<Shader>& shader)
{
	bool isnormals = false, istexture = false;

	// creates mesh.
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

	// loads xml document.
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename);

	if (result) {
		// parses xml document.
		pugi::xml_node meshNode = doc.child("mesh");
		pugi::xml_node buffersNode = meshNode.child("buffers");

		// iterates all buffers.
		for (pugi::xml_node bufferNode = buffersNode.child("buffer"); bufferNode; bufferNode = bufferNode.next_sibling("buffer")) 
		{
			// gets the index.
			std::string index = bufferNode.child("indices").text().as_string();
			std::vector<uint16_t> indexVec = splitString<uint16_t>(index, ',');

			// gets vertex coordinates.
			std::string coord = bufferNode.child("coords").text().as_string();
			std::vector<float> coordVec = splitString<float>(coord, ',');

			// creates the vertex with the extracted data.
			auto coordIterator = coordVec.begin();

			std::vector<Vertex> vertexVec;

			while(coordIterator != coordVec.end()) {
				Vertex ver;

				float x = *coordIterator;
				coordIterator++;
				float y = *coordIterator;
				coordIterator++;
				float z = *coordIterator;
				coordIterator++;
				ver.position = glm::vec3(x, y, z);

				vertexVec.push_back(ver);				
			}

			std::shared_ptr<Texture> tex;


			// creates material.
			Material mat = Material();
		
			// creates buffer.
			std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>(vertexVec, indexVec);
			
			// adds buffer to the mesh.
			mesh->addBuffer(buffer, mat);
		}

		return mesh;
	}
	else {
		// cannot open xml document.
		std::cout << result.description() << std::endl;
		return nullptr;
	}
}

void Mesh::draw() {
	for (auto& pair : m_pairs) {
		std::shared_ptr<Buffer> buffer = pair.first;
		Material material = pair.second;
		std::shared_ptr<Shader> sh = material.getShader();
		material.prepare();
		buffer->draw(*sh);
	}
}