#include "OpenGLApp.hpp"
#include "Utils.hpp"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
    	"FragColor = vec4(1.0f, 0.5f, 1.0f, 1.0f);\n"
	"}\0";

OpenGLApp::OpenGLApp(int width, int height) 
    : Window(width, height) { }
	
bool OpenGLApp::PrepareBuffers() {
	// init vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// create vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	if(!checkShader(vertexShader))
		return false;
	// init fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	if(!checkShader(fragmentShader))
		return false;
	// link all in shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	if(!checkShaderProgram(shaderProgram))
		return false;
	// free resources
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//init buffers
	float vertices[] = { // aka pozycje
    	-1.0f, -1.0f, 0.0f,
     	1.0f, -1.0f, 0.0f,
    	1.0f,  1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};
	uint indices[] = {
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
		3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// some unexplained binding bellow
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return true;
}
void OpenGLApp::loop() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}