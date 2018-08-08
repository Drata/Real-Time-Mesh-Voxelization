#include "world.h"
#include "state.h"

void World::addEntity(const std::shared_ptr<Entity>& entity) {
	if ( std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end() ) {
		m_entities.push_back(entity);
		std::shared_ptr<Camera> cam = std::dynamic_pointer_cast<Camera>(entity);
		if (cam) m_cameras.push_back(cam);

		std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(entity);
		if (light) m_lights.push_back(light);
	}
}

void World::removeEntity(const std::shared_ptr<Entity>& entity) {
	auto it = std::find(m_entities.begin(), m_entities.end(), entity);
	if (it != m_entities.end()) {
		m_entities.erase(it);
		std::shared_ptr<Camera> cam = std::dynamic_pointer_cast<Camera>(entity);
		if (cam) m_cameras.erase(std::find(m_cameras.begin(), m_cameras.end(), cam));

		std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light>(entity);
		if (light) m_lights.erase(std::find(m_lights.begin(), m_lights.end(), light));
	}
}

size_t World::getNumEntities() const {
	return m_entities.size();
}

const std::shared_ptr<Entity>& World::getEntity(size_t index) const {
	auto it = m_entities.begin();
	std::advance(it, index);
	return *it;
}

std::shared_ptr<Entity>& World::getEntity(size_t index) {
	auto it = m_entities.begin();
	std::advance(it, index);
	return *it;
}

void World::update(float deltaTime) {
	for ( auto& entity : m_entities ) {
		entity->update(deltaTime);
	}
}

void World::draw() {
	State::ambient = ambient;
	State::lights = m_lights;

	for ( auto camera : m_cameras ) {
		camera->prepare();
		for ( auto entity : m_entities ) {
			entity->draw();
		}
	}
}

const glm::vec3 & World::getAmbient() const
{
	return ambient;
}

void World::setAmbient(const glm::vec3 & ambient)
{
	this->ambient = ambient;
}
