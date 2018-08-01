#include "particle.h"

Particle::Particle(const Material & mat, const glm::vec3 & vel, float spinVel, float lifetime, bool autofade) : Billboard(mat)
{
	this->spinVel = spinVel;
	this->lifetime = this->currentLifetime = lifetime;
	this->autofade = autofade;
	this->velocity = vel;
}

float Particle::getRemainingLifetime() const
{
	return this->currentLifetime;
}

void Particle::update(float deltaTime)
{
	//Refresh current lifetime
	currentLifetime -= deltaTime;

	//Sets position
	setPosition(getPosition() + velocity * deltaTime);

	//Rotates particle
	setSpin(getSpin() + spinVel * deltaTime);

	//Refresh opacity
	float alpha;

	if (autofade) {
		glm::vec3 color = getMaterial().getColor();
		getMaterial().setColor(glm::vec4(color.r, color.g, color.b, currentLifetime/lifetime));
	}
}