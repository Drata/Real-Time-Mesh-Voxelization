#include "bone.h"

Bone::Bone(const char * name, int parentIndex)
{
	strcpy_s(this->name, name);
	this->parentIndex = parentIndex;
}

const char * Bone::getName() const
{
	return name;
}

int Bone::getParentIndex() const
{
	return parentIndex;
}

const glm::mat4 & Bone::getInvPoseMatrix() const
{
	return invPoseMatrix;
}

void Bone::setInvPoseMatrix(const glm::mat4 & m)
{
	invPoseMatrix = m;
}

void Bone::addPosition(uint16_t frame, const glm::vec3 & position)
{
	std::pair<uint16_t, glm::vec3> newPos(frame, position);
	posVector.push_back(newPos);
}

void Bone::addRotation(uint16_t frame, const glm::quat & rotation)
{
	std::pair<uint16_t, glm::quat> newRotation(frame, rotation);
	rotationsVector.push_back(newRotation);
}

void Bone::addScale(uint16_t frame, const glm::vec3 & scale)
{
	std::pair<uint16_t, glm::vec3> newScale(frame, scale);
	scalesVector.push_back(newScale);
}

glm::mat4 Bone::calculateAnimMatrix(float frame) const
{
	glm::mat4 animMat = glm::mat4();

	// gets transformations
	glm::vec3 position = calculatePosition(frame);
	glm::vec3 scale = calculateScale(frame);
	glm::quat rotation = calculateRotation(frame);

	// builds matrix
	glm::mat4 translateMat = glm::translate(animMat, position);
	glm::mat4 rotateMat = glm::rotate(translateMat, glm::angle(rotation), glm::axis(rotation));
	glm::mat4 scaleMat = glm::scale(rotateMat, scale);
	
	return scaleMat;
}

glm::vec3 Bone::calculatePosition(float frame) const
{
	for (int i = 0; i < posVector.size(); i++) {
		if (posVector.at(i).first == frame) {
			return posVector.at(i).second;
		}
		else {
			if (posVector.at(i).first > frame) {
				auto actual = posVector.at(i);
				auto anterior = posVector.at(i - 1);
				float a = (frame - anterior.first) / (actual.first - anterior.first);
				return glm::mix(anterior.second, actual.second, a);
			}
		}
	}

	if (posVector.size() > 0) {
		return posVector.back().second;
	}

	return glm::vec3();
}

glm::quat Bone::calculateRotation(float frame) const
{
	for (int i = 0; i < rotationsVector.size(); i++) {
		if (rotationsVector.at(i).first == frame) {
			return rotationsVector.at(i).second;
		}
		else {
			if (rotationsVector.at(i).first > frame) {
				auto actual = rotationsVector.at(i);
				auto anterior = rotationsVector.at(i - 1);
				float a = (frame - anterior.first) / (actual.first - anterior.first);
				return glm::slerp(anterior.second, actual.second, a);
			}
		}
	}

	if (rotationsVector.size() > 0) {
		return rotationsVector.back().second;
	}

	return glm::quat();
}

glm::vec3 Bone::calculateScale(float frame) const
{
	for (int i = 0; i < scalesVector.size(); i++) {
		if (scalesVector.at(i).first == frame) {
			return scalesVector.at(i).second;
		}
		else {
			if (scalesVector.at(i).first > frame) {
				auto actual = scalesVector.at(i);
				auto anterior = scalesVector.at(i - 1);
				float a = (frame - anterior.first) / (actual.first - anterior.first);
				return glm::mix(anterior.second, actual.second, a);
			}
		}
	}

	if (scalesVector.size() > 0) {
		return scalesVector.back().second;
	}

	return glm::vec3();
}
