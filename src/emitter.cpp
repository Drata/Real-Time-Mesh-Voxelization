#include "emitter.h"
#include "state.h"

Emitter::Emitter(const Material & mat, bool autofade)
{
	this->material = mat;
	this->autofade = autofade;
	this->toEmit = 0;
}

void Emitter::setRateRange(float min, float max)
{
	minRate = min;
	maxRate = max;
}

void Emitter::setVelocityRange(const glm::vec3 & min, const glm::vec3 & max)
{
	minVel = min;
	maxVel = max;
}

void Emitter::setSpinVelocityRange(float min, float max)
{
	minSpinVel = min;
	maxSpinVel = max;
}

void Emitter::setScaleRange(float min, float max)
{
	minScale = min;
	maxScale = max;
}

void Emitter::setLifetimeRange(float min, float max)
{
	minLifetime = min;
	maxLifetime = max;
}

void Emitter::setColorRange(const glm::vec4 & min, const glm::vec4 & max)
{
	minColor = min;
	maxColor = max;
}

void Emitter::emit(bool enable)
{
	this->enable = enable;
}

bool Emitter::isEmitting()
{
	return enable;
}

void Emitter::update(float deltaTime)
{
	//Checks if emitter is enabled
	if (enable) {
		//Calculates number of particles to emit
		float nParticles = glm::linearRand(minRate, maxRate) * deltaTime;
		nParticles += toEmit;

		//Gets integer part of the number of particles to emit
		float nParticlesCurrent = static_cast<int>(nParticles) / 1;

		//Accumulates decimal par of the number of particles to emit
		toEmit = nParticles - nParticlesCurrent;

		//Creates all particles
		for (int i = 0; i < nParticlesCurrent; i++) {
			//Calculates ranges
			glm::vec4 color = glm::linearRand(minColor, maxColor);
			glm::vec3 velocity = glm::linearRand(minVel, maxVel);
			float spinVel = glm::linearRand(minSpinVel, maxSpinVel);
			float lifetime = glm::linearRand(minLifetime, maxLifetime);
			float scale = glm::linearRand(minScale, maxScale);
			//Creates particle
			Particle particle = Particle(material, velocity, spinVel, lifetime, autofade);
			particle.setPosition(this->getPosition());
			particle.setScale(glm::vec3(scale, scale, 1.0f));
			particle.getMaterial().setColor(color);

			//Adds particle to the list
			emitted.push_back(particle);
		}
	}

	//Upgrades existing particles
	for (int i = emitted.size() - 1; i >= 0; i--) {

		emitted.at(i).update(deltaTime);

		//Checks remaining lifetime and erases "dead" particles.
		if (emitted.at(i).getRemainingLifetime() <= 0) {
			emitted.erase(emitted.begin() + i);
		}
	}
}

void Emitter::draw()
{
	for (int i = 0; i < emitted.size(); i++) 
	{
		emitted.at(i).draw();
	}
}