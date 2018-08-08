#pragma once
#include "common.h"

class Vertex {
public:
	glm::vec3 position;
	Vertex(float x, float y, float z) : position(x, y, z) {}
};