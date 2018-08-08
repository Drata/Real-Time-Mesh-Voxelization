#pragma once

#include "common.h"
#include "Entity.h"
#include "Mesh.h"

class Model : public Entity
{
public:
	Model(const std::shared_ptr<Mesh>& mesh);
	virtual void draw() override;

private:
	std::shared_ptr<Mesh> mesh;
};