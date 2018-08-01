#pragma once

#include "common.h"

struct Vertex {
	glm::vec3	position;
	glm::vec2	texture;
	glm::vec3	normal;

	Vertex();
	Vertex(const glm::vec3& position, const glm::vec2& texture, const glm::vec3& normal) : position(position), texture(texture), normal(normal) {}

	glm::vec4 bonesIndex;
	glm::vec4 bonesWeight;
};