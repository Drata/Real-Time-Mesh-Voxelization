#pragma once

#include "common.h"
#include "entity.h"
#include "state.h"

class Model : public Entity {
public:
	Model(const std::shared_ptr<Mesh>& mesh) : m_mesh(mesh) {}
	virtual void draw() override {
		if (m_mesh) {
			State::modelMatrix = glm::translate(glm::mat4(), getPosition());
			State::modelMatrix = glm::rotate(State::modelMatrix, glm::angle(getQuat()), glm::axis(getQuat()));
			State::modelMatrix = glm::scale(State::modelMatrix, getScale());
			m_mesh->draw();
		}
	}
private:
	std::shared_ptr<Mesh> m_mesh;
};