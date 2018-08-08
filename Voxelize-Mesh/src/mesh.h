#pragma once

#include "buffer.h"
#include "common.h"
#include "material.h"

class Mesh {
public:
	static std::shared_ptr<Mesh> load(const char* filename, const std::shared_ptr<Shader>& shader = nullptr);

	void addBuffer(const std::shared_ptr<Buffer>& buffer, const Material& material) {
		m_pairs.push_back(std::make_pair(buffer, material));
	}
	size_t getNumBuffers() const { return m_pairs.size(); }
	
	const std::shared_ptr<Buffer>& getBuffer(size_t index) const { return m_pairs[index].first; }
	std::shared_ptr<Buffer>& getBuffer(size_t index) { return m_pairs[index].first; }

	const Material& getMaterial(size_t index) const { return m_pairs[index].second; }
	Material& getMaterial(size_t index) { return m_pairs[index].second; }

	void draw();

private:
	std::vector<
		std::pair<
		std::shared_ptr<Buffer>,
		Material>> m_pairs;
};