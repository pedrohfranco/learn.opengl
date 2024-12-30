#include "Texture.h"
#include "stb/stb_image.h"

Texture::Texture(GLenum target, const char* imagePath, int desired_channels) {
	stbi_set_flip_vertically_on_load(true);
	this->target = target;
	this->bytes = stbi_load(imagePath, &imgWidth, &imgHeight, &nCols, desired_channels);

	glGenTextures(1, &ID);
}

void Texture::SetActive(GLuint unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
}

void Texture::Bind() {
	glBindTexture(target, ID);
}

void Texture::Unbind() {
	stbi_image_free(bytes);
	glBindTexture(target, 0);
	bytes = nullptr;
}

void Texture::Parameter(GLenum pname, GLint param) {
	glTexParameteri(target, pname, param);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}