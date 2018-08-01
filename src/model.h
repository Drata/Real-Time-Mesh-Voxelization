#pragma once

#include "common.h"
#include "entity.h"
#include "mesh.h"
#include "state.h"

class Model : public Entity {
public:
	Model(const std::shared_ptr<Mesh>& mesh) : m_mesh(mesh) {}
	virtual void draw() override {
		if (m_mesh) {
			if (isAnimate) {
				State::animation = true;
				State::animMatrices = animationMatVec;
			}

			State::modelMatrix = glm::translate(glm::mat4(), getPosition());
			State::modelMatrix = glm::rotate(State::modelMatrix, glm::angle(getQuat()), glm::axis(getQuat()));
			State::modelMatrix = glm::scale(State::modelMatrix, getScale());

			m_mesh->draw();
		}
	}

	void animate(bool animate);
	int getFps() const;
	void setFps(int fps);
	float getCurrentFrame() const;
	void setCurrentFrame(float frame);
	void calculateAnimMatrices(float frame, const std::vector<Bone>& bones);

	void update(float deltaTime);
private:
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<std::vector<glm::mat4>> animationMatVec = std::make_shared<std::vector<glm::mat4>>();
	int fps;
	float frame = 0;
	bool isAnimate;

};