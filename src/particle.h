#pragma once

#include "common.h"
#include "material.h"
#include "billboard.h"

class Particle : public Billboard {
public:
	Particle(const Material& mat, const glm::vec3& vel, float spinVel, float lifetime, bool autofade);
	float getRemainingLifetime() const;
	virtual void update(float deltaTime) override;
private:
	glm::vec3 velocity;
	float spinVel;
	float lifetime;
	float currentLifetime;
	bool autofade;
};