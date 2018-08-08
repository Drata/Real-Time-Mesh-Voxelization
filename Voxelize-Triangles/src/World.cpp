#include "..\include\World.h"

void World::addEntity(const std::shared_ptr<Entity>& entity)
{

	if (entity == nullptr) {
		return;
	}
		
	std::shared_ptr<Camera> camera = nullptr;

	//Stores the element.
	entities.push_back(entity);

	//If it's a camera stores it.
	camera = std::dynamic_pointer_cast<Camera>(entity);

	if (camera != nullptr) {
		cameras.push_back(camera);
	}
}

void World::removeEntity(const std::shared_ptr<Entity>& entity)
{
	if (entity == nullptr) {
		return;
	}

	std::shared_ptr<Camera> camera = nullptr;

	//Searche the entity in the vector and stores the position.
	std::vector<std::shared_ptr<Entity>>::iterator pos = std::find(entities.begin(), entities.end(), entity);

	if (pos != entities.end()) {
		entities.erase(pos);
	}

	//Checks if the entity is a camera.
	camera = std::dynamic_pointer_cast<Camera>(entity);

	if (camera != nullptr) {
		std::vector<std::shared_ptr<Camera>>::iterator posCamera = std::find(cameras.begin(), cameras.end(), camera);
	
		if (posCamera != cameras.end()) {
			cameras.erase(posCamera);
		}
	}
}

size_t World::getNumEntities() const
{
	return entities.size();
}

const std::shared_ptr<Entity>& World::getEntity(size_t index) const
{
	return entities.at(index);
}

std::shared_ptr<Entity>& World::getEntity(size_t index)
{
	return entities.at(index);
}

void World::update(float deltaTime)
{
	for (auto &entity : entities) {
		entity->update(deltaTime);
	}
}

void World::draw()
{
	for (auto &camera : cameras) {
		camera->prepare();

		for (auto &entity : entities) {
			entity->draw();
		}
	}
}
