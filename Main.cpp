#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VFShader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture2D.h"

GLfloat vertices[] =
{ // COORDINATES           /     COLORS           //
	-0.5f,  0.5f, 0.0f,     1.0f, 0.0f,  0.0f,    0.0f, 0.0f,// Canto superior esquerdo
	 0.5f,  0.5f, 0.0f,    0.0f, 0.0f,  1.0f,    0.0f, 1.0f,// Canto superior direito
	-0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f,// Canto inferior esquerdo
	 0.5f, -0.5f, 0.0f,    0.0f, 1.0f,  0.0f,   1.0f, 0.0f// Canto inferior direito
};

GLuint indices[] =
{
	2, 3, 1, // Triângulo inferior
	0, 2, 1, // Triângulo superior
};

double swapUniform() {
	return sin(glfwGetTime());
}

int main() {
	//Inicializando a janela do OpenGL
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Aprendendo", NULL, NULL);

	if (window == NULL) {
		std::cout << "Erro ao abrir a janela do glfw." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Carregando o objeto do viewport
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	
	float r, g, b;
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;

	VFShader shaderProgram = VFShader("default.vert", "default.frag");
	GLuint uniID1 = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); //Positions
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float))); //Colors
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float))); //Colors
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	//Textures
	Texture2D texture("texture1.jpeg", 0);
	texture.SetActive(0);
	texture.Bind();

	texture.Parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	texture.Parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	texture.Parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	texture.Parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Texture parameters
	texture.SpecifyTex(0, 0, GL_RGB, GL_RGB);
	texture.Unbind();

	//Loop de atualização da janela
	while (!glfwWindowShouldClose(window)) {
		glClearColor(r, g, b, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID1, swapUniform());
		texture.Bind();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	texture.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}