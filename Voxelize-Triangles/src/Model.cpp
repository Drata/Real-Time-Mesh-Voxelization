#include "..\include\Model.h"

Model::Model(const std::shared_ptr<Mesh>& mesh)
{
	this->mesh = mesh;
}

void Model::draw()
{
	glm::quat rotationQuat = glm::quat(rotation);
	glm::mat4 identity = glm::mat4();

	//Generates the model matrix with the position, translation and scale.
	glm::mat4 m = glm::translate(identity, position);
	m = glm::rotate(m, glm::angle(rotationQuat), glm::axis(rotationQuat));
	m = glm::scale(m, scale);

	//Sets the matrix in State.
	State::modelMatrix = m;

	//Calls the draw method of the mesh.
	mesh->draw();
}
