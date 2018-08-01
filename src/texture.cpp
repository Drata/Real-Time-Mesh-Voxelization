#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::shared_ptr<Texture> Texture::load(const char * filename)
{
	int x, y;
	glm::ivec2 size;
	uint32_t id;
	unsigned char *texture;

	stbi_set_flip_vertically_on_load(true);
	texture = stbi_load(filename, &x, &y, nullptr, 4);

	if (texture == nullptr) {
		return nullptr;
	}

	size = { x, y };

	//Generate texture
	glGenTextures(1, &id);

	//Activates texture
	glBindTexture(GL_TEXTURE_2D, id);

	//Applies filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Loads image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);

	//Generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(texture);

	std::shared_ptr<Texture> p(new Texture(id, size), [](Texture* p) { delete p; });

	return p;
}


uint32_t Texture::getId() const
{
	return id;
}

const glm::ivec2 & Texture::getSize() const
{
	return _size;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}
