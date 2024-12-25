#include "VFShader.h"

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw (errno);
}

VFShader::VFShader(const char* vertexFile, const char* fragmFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmCode = get_file_contents(fragmFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmSource = fragmCode.c_str();
	
	GLuint vShader, fShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vertexSource, NULL);
	glCompileShader(vShader);

	glShaderSource(fShader, 1, &fragmSource, NULL);
	glCompileShader(fShader);

	ID = glCreateProgram();
	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);
	glLinkProgram(ID);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void VFShader::Activate() {
	glUseProgram(ID);
}

void VFShader::Delete() {
	glDeleteProgram(ID);
}