#pragma once

#include "common.h"
#include "material.h"
#include "entity.h"
#include "buffer.h"

class Billboard : public Entity {
public:
	Billboard() {};
	Billboard(const Material& mat);
	const Material& getMaterial() const;
	Material& getMaterial();
	const glm::vec2& getSize() const;
	void setSize(const glm::vec2& size);
	float getSpin();
	void setSpin(float spin);
	virtual void draw() override;
private:
	Material material;
	glm::vec2 size;
	float spin;
	std::shared_ptr<Buffer> buffer;
};