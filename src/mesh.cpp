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
			// gets the texture from the material.
			pugi::xml_node materialNode = bufferNode.child("material");
			std::string textureStr = materialNode.child("texture").text().as_string();
			std::shared_ptr<Texture> tex;

			if (textureStr != "") {
				std::string texturePath = extractPath(filename) + textureStr;
				// loads texture.
				tex = Texture::load(texturePath.c_str());
				istexture = true;
			}
			

			// gets the index.
			std::string index = bufferNode.child("indices").text().as_string();
			std::vector<uint16_t> indexVec = splitString<uint16_t>(index, ',');

			// gets vertex coordinates.
			std::string coord = bufferNode.child("coords").text().as_string();
			std::vector<float> coordVec = splitString<float>(coord, ',');

			// gets texture coordinates.
			std::vector<float> texCoordVec;

			if (istexture) {
				std::string texCoord = bufferNode.child("texcoords").text().as_string();
				texCoordVec = splitString<float>(texCoord, ',');
			}

			// gets normals values.
			std::string normalsStr = bufferNode.child("normals").text().as_string();
			std::vector<float> normalsVec;

			if (normalsStr != "") {
				normalsVec = splitString<float>(normalsStr, ',');
				isnormals = true;
			}

			// gets bones index
			bool isBones = false;
			std::string bonesIndex = bufferNode.child("bone_indices").text().as_string();
			std::vector<float> bonesVec; 

			if (bonesIndex != "") {
				bonesVec = splitString<float>(bonesIndex, ',');
				isBones = true;
			}

			// gets bones weight
			bool isBonesWeight = false;
			std::string bonesWeight = bufferNode.child("bone_weights").text().as_string();
			std::vector<float> bonesWeightVec;

			if (bonesIndex != "") {
				bonesWeightVec = splitString<float>(bonesWeight, ',');
				isBonesWeight = true;
			}

			// gets color values.
			glm::vec4 color;
			std::string colorStr = materialNode.child("color").text().as_string();

			// if there's color defined.
			if (colorStr != "") {
				std::vector<float> colorVec = splitString<float>(colorStr, ',');
				color = glm::vec4(colorVec.at(0), colorVec.at(1), colorVec.at(2), colorVec.at(3));
			}
			else {
				color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			}

			// gets shininess value
			uint8_t shininess;
			std::string shininessStr = materialNode.child("shininess").text().as_string();
			
			// if there's shininess defined
			if (shininessStr != "") {
				shininess = stoi(shininessStr);
			}
			else {
				shininess = 0;
			}

			// creates the vertex with the extracted data.
			auto coordIterator = coordVec.begin();
			auto texCoordIterator = texCoordVec.begin();
			auto normalsIterator = normalsVec.begin();
			auto bonesIndexIterator = bonesVec.begin();
			auto bonesWeightIterator = bonesWeightVec.begin();

			std::vector<Vertex> vertexVec;

			while(coordIterator != coordVec.end()) {
				Vertex ver;

				float x = *coordIterator;
				coordIterator++;
				float y = *coordIterator;
				coordIterator++;
				float z = *coordIterator;
				ver.position = glm::vec3(x, y, z);

				if (istexture) {
					float u = *texCoordIterator;
					texCoordIterator++;
					float v = *texCoordIterator;
					ver.texture = glm::vec2(u, v);
					texCoordIterator++;
					ver.texture = glm::vec2(u, v);
				}

				if (isnormals) {
					float x = *normalsIterator;
					normalsIterator++;
					float y = *normalsIterator;
					normalsIterator++;
					float z = *normalsIterator;
					normalsIterator++;

					ver.normal = glm::vec3(x, y, z);
				}

				if (isBones) {
					float x = *bonesIndexIterator;
					bonesIndexIterator++;
					float y = *bonesIndexIterator;
					bonesIndexIterator++;
					float z = *bonesIndexIterator;
					bonesIndexIterator++;
					float w = *bonesIndexIterator;
					bonesIndexIterator++;
					ver.bonesIndex = glm::vec4(x, y, z, w);
				}

				if (isBonesWeight) {
					float x = *bonesWeightIterator;
					bonesWeightIterator++;
					float y = *bonesWeightIterator;
					bonesWeightIterator++;
					float z = *bonesWeightIterator;
					bonesWeightIterator++;
					float w = *bonesWeightIterator;
					bonesWeightIterator++;
					ver.bonesWeight = glm::vec4(x, y, z, w);
				}

				vertexVec.push_back(ver);

				coordIterator++;
			}
			  
			// creates material.
			Material mat = Material(tex);
			mat.setShininess(shininess);
			mat.setColor(color);
			mat.setCulling(true);
			mat.setLightning(true);

			// creates buffer.
			std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>(vertexVec, indexVec);
			
			// adds buffer to the mesh.
			mesh->addBuffer(buffer, mat);
		}

		// adds last frame
		uint8_t lastFrame = 0;
		std::string lastFrameStr = meshNode.child("last_frame").text().as_string();

		if (lastFrameStr != "") {
			lastFrame = stoi(lastFrameStr);
		}

		mesh->setLastFrame(lastFrame);

		// loads bones node
		pugi::xml_node bonesNode = meshNode.child("bones");

		for (pugi::xml_node boneNode = bonesNode.child("bone"); boneNode; boneNode = boneNode.next_sibling("bone")) {
			std::string nameStr = boneNode.child("name").text().as_string();
			
			// gets inverted Pose matrix
			glm::mat4 invPoseMat;
			std::string invPoseMatStr = boneNode.child("inv_pose").text().as_string();

			if (invPoseMatStr != "") {
				std::vector<float> invPosVector = splitString<float>(invPoseMatStr, ',');

				// builds matrix
				invPoseMat = glm::mat4(invPosVector.at(0), invPosVector.at(1), invPosVector.at(2), invPosVector.at(3),
									   invPosVector.at(4), invPosVector.at(5), invPosVector.at(6), invPosVector.at(7),
					                   invPosVector.at(8), invPosVector.at(9), invPosVector.at(10), invPosVector.at(11),
					                   invPosVector.at(12), invPosVector.at(13), invPosVector.at(14), invPosVector.at(15));
			}
			else {
				invPoseMat = glm::mat4();
			}

			// loads positions
			bool isPosition = false;
			std::vector<float> positionsVec;
			std::string positionsStr = boneNode.child("positions").text().as_string();
			if (positionsStr != "") {
				positionsVec = splitString<float>(positionsStr, ',');
				isPosition = true;
			}

			// loads scales
			bool isScales = false;
			std::vector<float> scalesVec;
			std::string scalesStr = boneNode.child("scales").text().as_string();
			if (scalesStr != "") {
				scalesVec = splitString<float>(scalesStr, ',');
				isScales = true;
			}
		
			// loads rotations
			bool isRotations = false;
			std::vector<float> rotationsVec;
			std::string rotationsStr = boneNode.child("rotations").text().as_string();
			if (rotationsStr != "") {
				rotationsVec = splitString<float>(rotationsStr, ',');
				isRotations = true;
			}

			// loads parent
			int parent = -1;
			std::string parentStr = boneNode.child("parent").text().as_string();

			if (parentStr != "") {
				parent = mesh->getBoneIndex(parentStr.c_str());
			}

			// builds bone
			Bone bone = Bone(nameStr.c_str(), parent);
			bone.setInvPoseMatrix(invPoseMat);

			// adds pos, rots, scales to the bone
			auto positionsIterator = positionsVec.begin();
			auto rotationsIterator = rotationsVec.begin();
			auto scalesIterator = scalesVec.begin();

			while (positionsIterator != positionsVec.end() || rotationsIterator != rotationsVec.end() || scalesIterator != scalesVec.end()) {
				
				// adds pos 
				if (isPosition && positionsIterator != positionsVec.end()) {
					int pos_frame = *positionsIterator;
					positionsIterator++;
					float x = *positionsIterator;
					positionsIterator++;
					float y = *positionsIterator;
					positionsIterator++;
					float z = *positionsIterator;
					positionsIterator++;

					bone.addPosition(pos_frame, glm::vec3(x, y, z));
				}

				// adds scales
				if (isScales && scalesIterator != scalesVec.end()) {
					int scale_frame = *scalesIterator;
					scalesIterator++;
					float x = *scalesIterator;
					scalesIterator++;
					float y = *scalesIterator;
					scalesIterator++;
					float z = *scalesIterator;
					scalesIterator++;

					bone.addScale(scale_frame, glm::vec3(x, y, z));
				}

				// adds rot 
				if (isRotations && rotationsIterator != rotationsVec.end()) {
					int rot_frame = *rotationsIterator;
					rotationsIterator++;
					float x = *rotationsIterator;
					rotationsIterator++;
					float y = *rotationsIterator;
					rotationsIterator++;
					float z = *rotationsIterator;
					rotationsIterator++;
					float w = *rotationsIterator;
					rotationsIterator++;

					bone.addRotation(rot_frame, glm::quat(x, y, z, w));
				}
			}

			// adds bone to the mesh
			mesh->addBone(bone);
		}

		return mesh;
	}
	else {
		// cannot open xml document.
		std::cout << result.description() << std::endl;
		return nullptr;
	}
}

void Mesh::addBone(const Bone & bone)
{
	boneVector.push_back(bone);
}

const std::vector<Bone>& Mesh::getBones() const
{
	return boneVector;
}

uint16_t Mesh::getLastFrame() const
{
	return lastFrame;
}

void Mesh::setLastFrame(uint16_t lastFrame)
{
	this->lastFrame = lastFrame;
}

int Mesh::getBoneIndex(const char * name) const
{
	for (int i = 0; i < boneVector.size(); i++) {
		if (strcmp(boneVector.at(i).getName(), name) == 0) {
			return i;
		}
	}

	return -1;
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