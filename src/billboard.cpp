#include "billboard.h"
#include "vertex.h"
#include "state.h"
#include <iostream>
#include <vector>

Billboard::Billboard(const Material & mat)
{

	material = mat;
	size = material.getTexture()->getSize();
	spin = glm::linearRand(0.0f, 360.0f);

	std::vector<Vertex> vertexVec;
	std::vector<uint16_t> indexVec = { 0, 1, 2, 2, 3, 0 };
	
	Vertex v;

	// v1
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v.texture = glm::vec2(0, 0);
	vertexVec.push_back(v);

	// v2
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v.texture = glm::vec2(1, 0);
	vertexVec.push_back(v);

	// v3
	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	v.texture = glm::vec2(1, 1);
	vertexVec.push_back(v);
	
	// v4
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	v.texture = glm::vec2(0, 1);
	vertexVec.push_back(v);
	
	// Creates buffer.
	buffer = std::make_shared<Buffer>(vertexVec, indexVec);
	
	// Sets entity position.
	setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

}

const Material & Billboard::getMaterial() const
{
	return material;
}

Material & Billboard::getMaterial()
{
	return material;
}

const glm::vec2 & Billboard::getSize() const
{
	return size;
}

void Billboard::setSize(const glm::vec2 & size)
{
	this->size = size;
}

float Billboard::getSpin()
{
	return spin;
}

void Billboard::setSpin(float spin)
{
	this->spin = spin;
}

void Billboard::draw()
{
	//Builds the model matrix
	glm::mat4 model = glm::transpose(State::viewMatrix);
	glm::vec3 pos = getPosition();

	model[0][3] = 0;
	model[1][3] = 0;
	model[2][3] = 0;
	model[3] = glm::vec4(pos.x, pos.y, pos.z, 1.0f);

	//Rotates the billboard
	model = glm::rotate(model, glm::radians(spin), glm::vec3(0.0f, 0.0f, 1.0f));

	//Scales the billboard
	glm::vec3 billboardScale = glm::vec3(size, 1) * getScale();
	model = glm::scale(model, billboardScale);

	//Overrides the model matrix at State class
	State::modelMatrix = model;
	
	//Prepares material and calls draw method from buffer
	material.prepare();
	std::shared_ptr<Shader> shader = material.getShader();
	buffer->draw(*shader);
}
