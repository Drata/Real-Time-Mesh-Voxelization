#include "../include/Buffer.h"

Buffer::Buffer(std::vector<Vertex> vertex, std::vector<uint16_t> index)
{

	this->vertex = vertex;
	this->index = index;

	//Create gl buffer
	bVertex = 0;
	bIndex = 0;
	glGenBuffers(1, &bVertex);
	glGenBuffers(1, &bIndex);

	//Send data to buffers
	glBindBuffer(GL_ARRAY_BUFFER, bVertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bIndex);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), vertex.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), index.data(), GL_STATIC_DRAW);
}

void Buffer::draw(const std::shared_ptr<Shader> &shader) const
{	
	//Setups attribute variables
	shader->setupAttribs();

	//Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, bVertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bIndex);
	
	//Draw the array
	glDrawArrays(GL_POINTS, 0, (GLsizei) vertex.size());
}

void Buffer::deleteBuffers()
{
	glDeleteBuffers(1, &bVertex);
	glDeleteBuffers(1, &bIndex);
}

std::shared_ptr<Buffer> Buffer::create(std::vector<Vertex> vertex, std::vector<uint16_t> index)
{
	std::shared_ptr<Buffer> bf(new Buffer(vertex, index), destroy);
	return bf;
}
