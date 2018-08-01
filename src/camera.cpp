#include "camera.h"
#include "state.h"

void Camera::prepare() {
	State::projectionMatrix = m_projection;
	
	State::viewMatrix = glm::rotate(glm::mat4(), -glm::angle(getQuat()), glm::axis(getQuat()));
	State::viewMatrix = glm::translate(State::viewMatrix, -getPosition());

	glDepthMask(true);

	glViewport(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);
	glScissor(m_viewport.x, m_viewport.y, m_viewport.z, m_viewport.w);

	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}