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
	compileErrors(vShader, "VERTEX");

	glShaderSource(fShader, 1, &fragmSource, NULL);
	glCompileShader(fShader);
	compileErrors(fShader, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void VFShader::Activate() const {
	glUseProgram(ID);
}

void VFShader::Delete() const {
	glDeleteProgram(ID);
}

void VFShader::compileErrors(GLuint shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}