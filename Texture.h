#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>

class Texture {
public:
	
	Texture(GLenum target, const char* imagePath, int desired_channels);

	GLuint getID() { return ID; };
	void SetActive(GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
	void Parameter(GLenum pname, GLint param);
	virtual void SpecifyTex(
		int level, int border, GLenum internal_format, GLenum format
	) = 0;

protected:
	GLenum target;
	GLuint ID;
	unsigned char* bytes;
	int imgWidth, imgHeight, nCols;
};

#endif