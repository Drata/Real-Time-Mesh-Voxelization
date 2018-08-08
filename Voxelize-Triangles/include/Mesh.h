#pragma once
#include "common.h"
#include "Buffer.h"
#include "State.h"
#include <vector>

class Mesh {
public:
	Mesh();
	~Mesh();

	void addBuffer(const std::shared_ptr<Buffer> &buffer, const std::shared_ptr<Shader> &shader = nullptr);
	size_t getNumBuffers() const;
	const std::shared_ptr<Buffer> &getBuffer(size_t index) const;
	std::shared_ptr<Buffer> &getBuffer(size_t index);
	void draw();

private:
	std::vector<std::shared_ptr<Buffer>> buffers;
	std::vector<std::shared_ptr<Shader>> shaders;
};