#pragma once
#include "common.h"
#include "shader.h"
#include "texture.h"

class Material {
public:
	enum BlendMode {ALPHA, ADD, MUL};

	Material(const std::shared_ptr<Texture>& tex = nullptr, const std::shared_ptr<Shader>& shader = nullptr);
	const std::shared_ptr<Shader>& getShader() const;
	std::shared_ptr<Shader>& getShader();
	void setShader(const std::shared_ptr<Shader>& shader);
	const std::shared_ptr<Texture>& getTexture() const;
	void setTexture(const std::shared_ptr<Texture>& tex);
	void prepare();
	const glm::vec4& getColor() const;
	void setColor(const glm::vec4& color);
	uint8_t getShininess() const;
	void setShininess(uint8_t shininess);

	//blend
	BlendMode getBlendMode() const;
	void setBlendMode(BlendMode blendMode);
	bool getLightning() const;
	void setLightning(bool enable);
	bool getCulling() const;
	void setCulling(bool enable);
	bool getDepthWrite() const;
	void setDepthWrite(bool enable);

private:
	std::shared_ptr<Texture> _texture;
	std::shared_ptr<Shader> _shader;
	glm::vec4 color;
	uint8_t shininess;

	BlendMode blendMode;
	bool lightning;
	bool culling;
	bool depthWrite;
};