#include "light.h"
#include "state.h"

Light::Type Light::getType() const
{
	return type;
}

void Light::setType(Type type)
{
	type = type;
}

const glm::vec3 & Light::getColor() const
{
	return color;
}

void Light::setColor(const glm::vec3 & color)
{
	this->color = color;
}

float Light::getLinearAttenuation() const
{
	return att;
}

void Light::setLinearAttenuation(float att)
{
	this->att = att;
}

void Light::prepare(int index, std::shared_ptr<Shader>& shader) const
{
	std::stringstream ss;

	// gets mv matrix.
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(glm::mat4(), this->getPosition());
	modelMatrix = glm::rotate(modelMatrix, glm::angle(getQuat()), glm::axis(getQuat()));
	modelMatrix = glm::scale(modelMatrix, getScale());

	glm::mat4 mv = State::viewMatrix * modelMatrix;

	// passes att var to the shader.

	ss << "lights[" << index << "].att";
	int attLoc = shader->getLocation(ss.str().c_str());
	shader->setFloat(attLoc, att);
	ss.str("");
	
	// passes color var to the shader.
	
	ss << "lights[" << index << "].color";
	int colorLoc = shader->getLocation(ss.str().c_str());
	shader->setVec3(colorLoc, color);
	ss.str("");

	// passes light vector to the shader.
	ss << "lights[" << index << "].vec";
	int vecLoc = shader->getLocation(ss.str().c_str());
	glm::vec4 mvVec = mv * glm::vec4(1, 1, 1, type);
	shader->setVec4(vecLoc, mvVec);
}