#include "OpenGLApp.hpp"

OpenGLApp::OpenGLApp(int width, int height) 
    : Window(width, height) {
    const float x0 = 1.0f;
	const float y0 = 1.0f;
	const float z0 = 1.0f;
    const float position[] =
	{
		-x0, -y0, 0.0f,
        x0, -y0, 0.0f,
        0, y0, 0.0f
	};
/*     const float colors[] =
	{
		1.0f,1.0f,0.0f,1.0f,
		1.0f,0.0f,1.0f,1.0f,
		0.0f,1.0f,1.0f,1.0f,
		0.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f
	}; */
    //Vertex Array Object (VAO)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Vertex Buffer Object (VBO)
	glGenBuffers(3, &vbo[0]);
	//GLuint atrybutPo�o�enie = 0;
	//GLuint atrybutKolor = 3;

    GLuint placemnt = 0;
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
	glVertexAttribPointer(placemnt, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

/* 	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);
 */
	


    }
void OpenGLApp::loop() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}