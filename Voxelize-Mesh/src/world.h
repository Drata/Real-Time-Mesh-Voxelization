#pragma once

#include "camera.h"
#include "common.h"
#include "entity.h"
#include "light.h"

class World {
public:
	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(const std::shared_ptr<Entity>& entity);
	size_t getNumEntities() const;
	const std::shared_ptr<Entity>& getEntity(size_t index) const;
	std::shared_ptr<Entity>& getEntity(size_t index);
	void update(float deltaTime);
	void draw();
	const glm::vec3& getAmbient() const;
	void setAmbient(const glm::vec3& ambient);
private:
	std::list<std::shared_ptr<Entity>> m_entities;
	std::list<std::shared_ptr<Camera>> m_cameras;
	std::vector <std::shared_ptr<Light>> m_lights;
	glm::vec3 ambient;

};