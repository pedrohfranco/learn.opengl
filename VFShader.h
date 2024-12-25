#ifndef VFSHADER_CLASS_H
#define VFSHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class VFShader {
public:
	GLuint ID;
	VFShader(const char* vertexFile, const char* fragmFile);
	void Activate();
	void Delete();
};

#endif
