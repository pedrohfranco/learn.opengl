#include "Texture2D.h"

void Texture2D::SpecifyTex(int level, int border, GLenum internal_format, GLenum format) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(target, level, internal_format, imgWidth, imgHeight, border, format, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(target);
}