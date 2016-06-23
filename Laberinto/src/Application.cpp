#include "Application.h"
#include <iostream>
#include <vector>
#include <time.h>
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ShaderFuncs.h"


GLfloat vertexPositions[] = {
	//A t1
	0.75f, 0.75f, -0.75f, 0.75f,
	0.75f, -0.75f, -0.75f, 0.75f,
	-0.75f, -0.75f, -0.75f, 0.75f,
	//A t2
	0.75f, 0.75f, -0.75f, 0.75f,
	-0.75f, -0.75f, -0.75f, 0.75f,
	-0.75f, 0.75f, -0.75f, 0.75f,
	//Bt1
	0.75f, 0.75f, 0.75f, 0.75f,
	-0.75f, -0.75f, 0.75f, 0.75f,
	0.75f, -0.75f, 0.75f, 0.75f,
    //Bt2
	0.75f, 0.75f, 0.75f, 0.75f,
	-0.75f, 0.75f, 0.75f, 0.75f,
	-0.75f, -0.75f, 0.75f, 0.75f,
	//Ct1
	0.75f, 0.75f, 0.75f, 0.75f,
	0.75f, -0.75f, 0.75f, 0.75f,
	0.75f, -0.75f, -0.75f, 0.75f,
	//Ct2
	0.75f, -0.75f, -0.75f, 0.75f,
	0.75f, 0.75f, -0.75f, 0.75f,
	0.75f, 0.75f, 0.75f, 0.75f,
	//Dt1
	-0.75f, 0.75f, -0.75f, 0.75f,
	-0.75f, -0.75f, -0.75f, 0.75f,
	-0.75f, -0.75f, 0.75f, 0.75f,
	//Dt2
	-0.75f, 0.75f, -0.75f, 0.75f,
	-0.75f, -0.75f, 0.75f, 0.75f,
	-0.75f, 0.75f, 0.75f, 0.75f,
	//Et1
	-0.75f, 0.75f, -0.75f, 0.75f,
	-0.75f, 0.75f, 0.75f, 0.75f,
	0.75f, 0.75f, 0.75f, 0.75f,
	//Et2
	-0.75f, 0.75f, -0.75f, 0.75f,
	0.75f, 0.75f, 0.75f, 0.75f,
	0.75f, 0.75f, -0.75f, 0.75f,
	//Ft1
	-0.75f, -0.75f, 0.75f, 0.75f,
	-0.75f, -0.75f, -0.75f, 0.75f,
	0.75f, -0.75f, -0.75f, 0.75f,
	//Ft2
	-0.75f, -0.75f, 0.75f, 0.75f,
	0.75f, -0.75f, -0.75f, 0.75f,
	0.75f, -0.75f, 0.75f, 0.75f
};
GLfloat vertexColors[] = {
	//R
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	//Morado
	0.3, 0.0, 0.8, 1.0,
	0.3, 0.0, 0.8, 1.0,
	0.3, 0.0, 0.8, 1.0,
	0.3, 0.0, 0.8, 1.0,
	0.3, 0.0, 0.8, 1.0,
	0.3, 0.0, 0.8, 1.0,
	//G
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	//B
	0.0, 0.2, 1.0, 1.0,
	0.0, 0.2, 1.0, 1.0,
	0.0, 0.2, 1.0, 1.0,
	0.0, 0.2, 1.0, 1.0,
	0.0, 0.2, 1.0, 1.0,
	0.0, 0.2, 1.0, 1.0,
	//Naranja
	1.0f, 0.5f, 0.0f, 0.7f,
	1.0f, 0.5f, 0.0f, 0.7f,
	1.0f, 0.5f, 0.0f, 0.7f,
	1.0f, 0.5f, 0.0f, 0.7f,
	1.0f, 0.5f, 0.0f, 0.7f,
	1.0f, 0.5f, 0.0f, 0.7f,
	//Blanco
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

};
char Dungeon[15][15] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,
	1,0,1,1,1,1,1,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
std::string strFragmentShader, strVertexShader;
Application::Application() : fAngle(0.0), //eye(5.0f, 50.0f, 25.0f), target(5.0f, 0.0f, 5.0f)//top view
                                          eye(-10.0f, 5.0f, -15.0f), target(0.0f, 0.0f, 0.0f)//fpv
{}
Application::~Application() 
{}
void Application::loadShaders()
{
	strVertexShader = loadTextFile("shaders/vertexshader1.vs");
	strFragmentShader = loadTextFile("shaders/fragmentshader1.fs");
}
void Application::setup()
{
	
	loadShaders();
	InitializeProgram(cube.shader, strVertexShader, strFragmentShader);
	cube.numVertex = 36;
	glGenVertexArrays(1, &cube.vao);
	glBindVertexArray(cube.vao);
	glGenBuffers(1, &cube.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions)+sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), vertexPositions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexColors), vertexColors);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertexPositions));
	uTransform = glGetUniformLocation(cube.shader, "transform");
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}
void Application::display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glUseProgram(cube.shader);	
	glBindVertexArray(cube.vao);
	for (int i = 0; i < 15; i++)
	{
		glm::mat4 filas = glm::translate(glm::mat4(1.0f), (glm::vec3(2.0f, 2.0f, 2.0f*i)));//2 espaciado perfecto
		for (int j = 0; j < 15; j++)
		{
			glm::mat4 columnas = glm::translate(glm::mat4(1.0f), (glm::vec3(2.0f*j, 2.0f, 1.0f)));
			columnas = glm::translate(columnas, glm::vec3(-0.95f, -0.95f, 0.9f));
			glm::mat4 transform = camera * columnas * filas;
			transform = glm::perspective(45.0f, 680.0f / 480.0f, 0.1f, 300.0f) * transform; //far MUY lejos 300+
			if (Dungeon[i][j] == 1)
			{
				glUniformMatrix4fv(uTransform, 1, GL_FALSE, glm::value_ptr(transform));
				glDrawArrays(GL_TRIANGLES, 0, cube.numVertex);
			}
		}
	}
}
void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}
void Application::update()
{
	clock_t time;
	time = clock();

	fAngle = ((float)time)/CLOCKS_PER_SEC;
	camera = glm::lookAt(eye, target, glm::vec3(0.0f, 1.0f, 0.0f));	//poner la f para que sea el double
}
void Application::keyboard(int key, int scanCode, int action, int mods)
{
switch (key)
{
//case GLFW_KEY_ESCAPE: exit(0);
}
}