#include "material.h"
#include "state.h"

Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader)
{
	_texture = tex;
	_shader = shader;
}

const std::shared_ptr<Shader>& Material::getShader() const
{

	return _shader ? _shader : State::defaultShader;
}

std::shared_ptr<Shader>& Material::getShader()
{
	return _shader ? _shader : State::defaultShader;
}

void Material::setShader(const std::shared_ptr<Shader>& shader)
{
	_shader = shader;
}

const std::shared_ptr<Texture>& Material::getTexture() const
{
	return _texture;
}

void Material::setTexture(const std::shared_ptr<Texture>& tex)
{
	_texture = tex;
}

void Material::prepare()
{
	std::shared_ptr<Shader> sh = getShader(); 

	//Activates shader.
	sh->use();

	//Sets mvp in the shader.
	glm::mat4 mvp = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
	int locMvp = sh->getLocation("mvp");
	sh->setMatrix(locMvp, mvp);
}
