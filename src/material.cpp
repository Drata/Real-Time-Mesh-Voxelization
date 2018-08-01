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

	//Sets mv in the shader.
	glm::mat4 mv = State::viewMatrix * State::modelMatrix;
	int locMv = sh->getLocation("mv");
	sh->setMatrix(locMv, mv);

	//Sets normal matrix in the shader.
	glm::mat4 normalMatrix = glm::transpose(glm::inverse(mv));
	int locNormalMat = sh->getLocation("normalMat");
	sh->setMatrix(locNormalMat, normalMatrix);

	if (lightning) {
		//Sets number of lights in the shader.
		int nLights = sh->getLocation("nLights");
		sh->setInt(nLights, State::lights.size());

		//Sets shininess in the shader.
		int shininessLoc = sh->getLocation("shininess");
		sh->setInt(shininessLoc, shininess);

		//Sets ambient light in the shader.
		int ambientLoc = sh->getLocation("ambient");
		sh->setVec3(ambientLoc, State::ambient);

		//Prepares the lights.
		for (int i = 0; i < State::lights.size(); i++) {
			State::lights[i]->prepare(i, sh);
		}
	}
	else {
		//Sets number of lights in the shader.
		int nLights = sh->getLocation("nLights");
		sh->setInt(nLights, 0);
	}

	//Sets diffuse color in the shader.
	int diffuseLoc = sh->getLocation("diffuse");
	sh->setVec4(diffuseLoc, color);

	//Sets texture boolean in the shader.
	int locTexBool = sh->getLocation("isTexture");
	if (_texture) {
		sh->setInt(locTexBool, 1);

		//Sets sampler in the shader.
		int locSampler = sh->getLocation("sampler");
		sh->setInt(locSampler, 0);
		_texture->bind();
		
	} else {
		sh->setInt(locTexBool, 0);

		//Sets sampler in the shader.
		int locSampler = sh->getLocation("sampler");
		sh->setInt(locSampler, 0);
	}

	//Blending mode.
	switch (blendMode) {
		case BlendMode::ADD:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case BlendMode::ALPHA:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case BlendMode::MUL:
			glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			break;
		default:
			break;
	}

	//Culling mode
	if (culling) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	//Sets animation info in the shaderd
	int isAnimationLoc = sh->getLocation("isAnimation");
	sh->setInt(isAnimationLoc, State::animation);

	if (State::animation) {
		for (int i = 0; i < State::animMatrices->size(); i++) {
			std::stringstream ss;
			ss.str("");
			ss << "animMat[" << i << "]";
			int animMatLoc = sh->getLocation(ss.str().c_str());
			sh->setMatrix(animMatLoc, State::animMatrices->at(i));
			ss.str("");
		}
	}


	//Depth buffer
	glDepthMask(depthWrite);

}

const glm::vec4 & Material::getColor() const
{
	return color;
}

void Material::setColor(const glm::vec4 & color)
{
	this->color = color;
}

uint8_t Material::getShininess() const
{
	return shininess;
}

void Material::setShininess(uint8_t shininess)
{
	this->shininess = shininess;
}

Material::BlendMode Material::getBlendMode() const
{
	return blendMode;
}

void Material::setBlendMode(BlendMode blendMode)
{
	this->blendMode = blendMode;
}

bool Material::getLightning() const
{
	return lightning;
}

void Material::setLightning(bool enable)
{
	lightning = enable;
}

bool Material::getCulling() const
{
	return culling;
}

void Material::setCulling(bool enable)
{
	culling = enable;
}

bool Material::getDepthWrite() const
{
	return depthWrite;
}

void Material::setDepthWrite(bool enable)
{
	depthWrite = enable;
}
