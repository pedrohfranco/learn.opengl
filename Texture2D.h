#ifndef TEXTURE_2D_CLASS_H
#define TEXTURE_2D_CLASS_H

#include "Texture.h"
#include "stb/stb_image.h"

class Texture2D : public Texture {
public:
	Texture2D(const char* imagePath, int desired_channels)
		: Texture(GL_TEXTURE_2D, imagePath, desired_channels) {};

	void SpecifyTex(int level, int border, GLenum internal_format, GLenum format) override;
};

#endif
