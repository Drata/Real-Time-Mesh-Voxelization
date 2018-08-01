#pragma once
#include "common.h"
#include "../lib/glew/glew.h"

class Texture {

public:
	Texture(uint32_t id, glm::ivec2 size) : id(id), _size(size) {}
	
	static std::shared_ptr<Texture> load(const char *filename);
	uint32_t getId() const;
	const glm::ivec2& getSize() const;
	void bind() const;
private:
	uint32_t id;
	glm::ivec2 _size;
};