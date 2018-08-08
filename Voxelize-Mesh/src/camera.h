#pragma once

#include "common.h"
#include "entity.h"

class Camera : public Entity {
public:
	Camera(const glm::ivec2& viewportSize = glm::ivec2(0, 0)) : m_viewport(0, 0, viewportSize.x, viewportSize.y), m_clearColor(0, 0, 0.5f) {
		m_projection = glm::perspective<float>(glm::radians(60.0f), viewportSize.y == 0 ? 1 : static_cast<float>(viewportSize.x) / viewportSize.y, 1, 1000);
	}

	const glm::mat4& getProjection() const		{ return m_projection; }
	void setProjection(const glm::mat4& proj)	{ m_projection = proj; }

	const glm::ivec4& getViewport() const		{ return m_viewport; }
	void setViewport(const glm::ivec4& vp)		{ m_viewport = vp; }

	const glm::vec3& getClearColor() const		{ return m_clearColor; }
	void setClearColor(const glm::vec3& color)	{ m_clearColor = color; }

	void prepare();
private:
	glm::mat4	m_projection;
	glm::ivec4	m_viewport;
	glm::vec3	m_clearColor;
};