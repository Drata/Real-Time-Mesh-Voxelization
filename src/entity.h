#pragma once

#include "common.h"

class Entity : public std::enable_shared_from_this<Entity> {
public:
	typedef void(* UpdateCallbackFunc)(std::shared_ptr<Entity>, float);

	Entity() : m_scale(1, 1, 1), m_updateCallback(nullptr) {}
	virtual ~Entity() {}

	const glm::vec3&	getPosition() const { return m_position; }
	void				setPosition(const glm::vec3& pos) { m_position = pos; }
	const				glm::vec3& getEuler() const { return m_euler; }
	const void			setEuler(const glm::vec3& rot) { m_euler = rot; m_quat = glm::quat(glm::radians(rot)); }
	const				glm::quat& getQuat() const { return m_quat; }
	const void			setQuat(const glm::quat& rot) { m_quat = rot; m_euler = glm::degrees(glm::eulerAngles(m_quat)); }
	const glm::vec3&	getScale() const { return m_scale; }
	void				setScale(const glm::vec3& scale) { m_scale = scale; }

	void				move(const glm::vec3& vec) { m_position += m_quat * vec; }

	const std::shared_ptr<void>&	getUserData() const { return m_userData; }
	std::shared_ptr<void>&			getUserData()		{ return m_userData; }
	void							setUserData(const std::shared_ptr<void>& data) { m_userData = data; }

	UpdateCallbackFunc				getUpdateCallback() { return m_updateCallback; }
	void							setUpdateCallback(UpdateCallbackFunc func) { m_updateCallback = func; }

	virtual void update(float deltaTime) {
		if (m_updateCallback) {
			m_updateCallback(shared_from_this(), deltaTime);
		}
	}
	
	virtual void		draw() {}
private:
	glm::vec3				m_position;
	glm::vec3				m_euler;
	glm::quat				m_quat;
	glm::vec3				m_scale;
	std::shared_ptr<void>	m_userData;
	UpdateCallbackFunc		m_updateCallback;
};