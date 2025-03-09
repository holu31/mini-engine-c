#include "texture.h"
#include "string.h"
#include "glad/glad.h"
#include "stb_image.h"

texture_t* Texture_Create() {
	texture_t* texture = malloc(sizeof(texture_t));
	if (!texture) return NULL;

	glGenTextures(1, &texture->id);
	texture->mag_filter = FILTER_LINEAR;
	texture->min_filter = FILTER_LINEAR_TO_NEAREST;

	return texture;
}

void Texture_Load(texture_t* texture, asset_t* source) {
	if (!source || !texture) return;

	int width, height, channels;
	texture->data = stbi_load_from_memory(source->data, source->size, &width, &height, &channels, 4);
	texture->size[0] = width;
	texture->size[1] = height;

	Texture_Apply(texture);
	stbi_image_free(texture->data);
}

void Texture_Apply(texture_t* texture) {
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->size[0], texture->size[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture_Bind(texture_t* texture) {
	glBindTexture(GL_TEXTURE_2D, texture->id);
}

void Texture_Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
