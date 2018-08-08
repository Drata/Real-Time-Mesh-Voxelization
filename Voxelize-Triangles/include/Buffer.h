#pragma once
#include "Vertex.h"
#include "Shader.h"
#include <vector>

class Buffer{
public: 
	void draw(const std::shared_ptr<Shader> &shader) const;
	void deleteBuffers();
	static std::shared_ptr<Buffer> create(std::vector<Vertex> vertex, std::vector<uint16_t> index);
protected:
	Buffer(std::vector<Vertex> vertex, std::vector<uint16_t> index);	
	static void destroy(Buffer *p) {
		delete p;
	}
private:
	uint32_t bVertex, bIndex;
	std::vector<Vertex> vertex;
	std::vector<uint16_t> index;

};