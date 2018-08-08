#include "..\include\Mesh.h"

Mesh::Mesh(){}

Mesh::~Mesh(){}

void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, const std::shared_ptr<Shader>& shader)
{
	buffers.push_back(buffer);
	
	if (shader != nullptr) {
		shaders.push_back(shader);
	}
	else {
		shaders.push_back(State::defaultShader);
	}
}

size_t Mesh::getNumBuffers() const
{
	return buffers.size();
}

const std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index) const
{
	if (index < 0 || index > buffers.size())
		return nullptr;

	return buffers.at(index);
}

std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index)
{
	if (index < 0 || index > buffers.size()) {
		std::shared_ptr<Buffer> p = nullptr;
		return p;
	}
		
	return buffers.at(index);
}

void Mesh::draw()
{
	int mvpLoc;

	for (int i = 0; i < buffers.size(); i++) {
		std::shared_ptr<Shader> sh = shaders.at(i);

		//Activates the shader.
		sh->use();

		//Gets location of the mvp.
		mvpLoc = sh->getLocation("mvp");

		//Calculates mvp.
		glm::mat4 mv = State::viewMatrix * State::modelMatrix;
		glm::mat4 mvp = State::projectionMatrix * mv;

		//Sends mvp to the shader.
		sh->setMatrix(mvpLoc, mvp);

		//Draws
		buffers.at(i)->draw(sh);
	}
}