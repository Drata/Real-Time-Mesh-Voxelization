#include "..\include\Entity.h"

Entity::Entity()
{
}

const glm::vec3 & Entity::getPosition() const
{
	return position;
}

void Entity::setPosition(const glm::vec3 & pos)
{
	position = pos;
}

const glm::vec3 & Entity::getRotation() const
{
	return rotation;
}

const glm::quat & Entity::getRotationQuat() const
{
	return glm::quat(rotation);
}

const void Entity::setRotation(const glm::vec3 & rot)
{
	rotation = rot;
}

const void Entity::setRotation(const glm::quat & rot)
{
	rotation = glm::eulerAngles(rot);
}

const glm::vec3 & Entity::getScale() const
{
	return scale;
}

void Entity::setScale(const glm::vec3 & scale)
{
	this->scale = scale;
}

void Entity::move(const glm::vec3 & vec)
{
	position += rotation * vec;
}
