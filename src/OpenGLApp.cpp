#include <string>
#include "OpenGLApp.hpp"
#include "Utils.hpp"
#include <ctime>
#include <math.h>

OpenGLApp::OpenGLApp(int width, int height) 
    : Window(width, height) { }
	
bool OpenGLApp::PrepareBuffers() {
	float vertices[] = {
		//postions          // colors
    	-1.0f, -1.0f, 0.0f,	 1.0f, 0.0f, 0.0f,
     	 1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 
    	 1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 
		-1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f, 
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	// creating buffers 
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);	
	glGenBuffers(1, &ebo);
	// binding buffers
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
		6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
		(void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	return true;
}
void OpenGLApp::LoadShaderFiles(const std::string &vertexShaderPath, 
                                const std::string &fragmentShaderPath) {
	std::string vertexContent = readFile(vertexShaderPath);
	std::string fragmentContent = readFile(fragmentShaderPath);
	if(vertexContent == "" || fragmentContent == "")
		throw std::runtime_error("[Error] Vertex shader or fragment shader is empty");
	shader = Shader(vertexContent, fragmentContent);
}
void OpenGLApp::loop() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram((GLuint) shader);
	GLint screenWidthParam = glGetUniformLocation((GLuint) shader, "screenWidth");
	GLint screenHeightParam = glGetUniformLocation((GLuint) shader, "screenHeight");
	glUniform1f(screenWidthParam, getWidth());
	glUniform1f(screenHeightParam, getHeight());

	// MVP matrix
	GLint matrixWorldParam = glGetUniformLocation((GLuint) shader, "matrixWorld"); 
	float matrixWorld[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};
	glUniformMatrix4fv(matrixWorldParam, 1, true, matrixWorld);
	GLint matrixViewParam = glGetUniformLocation((GLuint) shader, "matrixView");
	float matrixView[16] ={
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, -3.0f,
		0.0f, 0.0f, 0.0f, 1.0f};
	glUniformMatrix4fv(matrixViewParam, 1, true, matrixView);
	GLint matrixProjectionParam = glGetUniformLocation((GLuint) shader, "matrixProjection");
	float matrixProjection[16] ={
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.41f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.22f, -2.22f,
		0.0f, 0.0f, -1.0f, 0.0f};
	glUniformMatrix4fv(matrixProjectionParam, 1, true, matrixProjection);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, 3);
}