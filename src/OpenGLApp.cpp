#include <string>
#include "OpenGLApp.hpp"
#include "Utils.hpp"

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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram((GLuint) shader);
	GLint screenWidthParam = glGetUniformLocation((GLuint) shader, "screenWidth");
	GLint screenHeightParam = glGetUniformLocation((GLuint) shader, "screenHeight");
	glUniform1f(screenWidthParam, getWidth());
	glUniform1f(screenHeightParam, getHeight());
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// glDrawArrays(GL_TRIANGLES, 0, 3);
}