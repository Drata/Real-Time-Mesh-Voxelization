#include "../lib/glew/glew.h"
#include "buffer.h"

Buffer::Buffer(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) {
	glGenBuffers(2, m_buffers.data());
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);
	m_numIndices = indices.size();
}

Buffer::~Buffer() {
	glDeleteBuffers(2, m_buffers.data());
}

void Buffer::draw(const Shader& shader) const {
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[1]);
	shader.setupAttribs();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_numIndices), GL_UNSIGNED_SHORT, nullptr);
}
