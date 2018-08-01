#pragma once

#include "common.h"

class Bone {
public:
	Bone(const char* name, int parentIndex);
	
	const char* getName() const;
	int getParentIndex() const;

	const glm::mat4& getInvPoseMatrix() const;
	void setInvPoseMatrix(const glm::mat4& m);

	void addPosition(uint16_t frame, const glm::vec3& position);
	void addRotation(uint16_t frame, const glm::quat& rotation);
	void addScale(uint16_t frame, const glm::vec3& scale);

	glm::mat4 calculateAnimMatrix(float frame) const;
	glm::vec3 calculatePosition(float frame) const;
	glm::quat calculateRotation(float frame) const;
	glm::vec3 calculateScale(float frame) const;

private:
	int parentIndex = -1;
	char name[255];
	glm::mat4 invPoseMatrix, animationMatrix;
	std::vector<std::pair<uint16_t, glm::quat>> rotationsVector;
	std::vector<std::pair<uint16_t, glm::vec3>> posVector, scalesVector;
};