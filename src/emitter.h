#pragma once

#include "common.h"
#include "entity.h"
#include "material.h"
#include "particle.h"

class Emitter : public Entity {
public:
	Emitter(const Material& mat, bool autofade=false);
	void setRateRange(float min, float max);
	void setVelocityRange(const glm::vec3& min, const glm::vec3& max);
	void setSpinVelocityRange(float min, float max);
	void setScaleRange(float min, float max);
	void setLifetimeRange(float min, float max);
	void setColorRange(const glm::vec4& min, const glm::vec4& max);
	void emit(bool enable);
	bool isEmitting();
	virtual void update(float deltaTime) override;
	virtual void draw() override;

private:
	Material material;
	bool enable, autofade;
	float minRate, maxRate, minSpinVel, maxSpinVel, minScale, maxScale, minLifetime, maxLifetime, toEmit;
	glm::vec3 minVel, maxVel;
	glm::vec4 minColor, maxColor;
	std::vector<Particle> emitted;
};