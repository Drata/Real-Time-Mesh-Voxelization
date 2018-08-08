#pragma once

#include "common.h"
#include <iostream>

class Entity
{
public:
	Entity();
	virtual ~Entity() {};
	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& pos);
	const glm::vec3& getRotation() const;
	const glm::quat& getRotationQuat() const;
	const void setRotation(const glm::vec3& rot);
	const void setRotation(const glm::quat& rot);
	const glm::vec3& getScale() const;
	void setScale(const glm::vec3& scale);
	void move(const glm::vec3& vec);

	virtual void update(float deltaTime) {}
	virtual void draw() {}

protected:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};