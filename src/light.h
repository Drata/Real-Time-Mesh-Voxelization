#pragma once

#include "common.h"
#include "entity.h"
#include "shader.h"

class Light : public Entity {
	
public:

	enum Type {
		DIRECTIONAL = 0,
		POINT
	};

	Light() : type(Light::DIRECTIONAL), color(1.0f, 1.0f, 1.0f), att(0.2f) {}
	~Light() {}

	Type getType() const;
	void setType(Type type);
	const glm::vec3& getColor() const;
	void setColor(const glm::vec3& color);
	float getLinearAttenuation() const;
	void setLinearAttenuation(float att);
	void prepare(int index, std::shared_ptr<Shader>& shader) const;
private: 
	Type type;
	glm::vec3 color;
	float att;

};