#include "..\include\Camera.h"

Camera::Camera()
{
}

const glm::mat4 & Camera::getProjection() const
{
	return projection;
}

void Camera::setProjection(const glm::mat4 & proj)
{
	projection = proj;
}

const glm::ivec4 & Camera::getViewport() const
{
	return viewPort;
}

void Camera::setViewport(const glm::ivec4 & vp)
{
	viewPort = vp;
}

const glm::vec3 & Camera::getClearColor() const
{
	return clearColor;
}

void Camera::setClearColor(const glm::vec3 & color)
{
	clearColor = color;
}

void Camera::prepare()
{
	glm::mat4 v;

	//Sets the State projection matrix.
	State::projectionMatrix = projection;

	v[3] = glm::vec4(-position, 1.0f);

	//Sets the State view matrix.
	State::viewMatrix = v;

	//Sets opengl viewport and scissor.
	glViewport(viewPort.s, viewPort.t, viewPort.p, viewPort.q);
	glScissor(viewPort.s, viewPort.t, viewPort.p, viewPort.q);

	//Clear
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
