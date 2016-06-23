
#include "Application.h"
#include <iostream>
#include <vector>
#include "GLFW/glfw3.h"
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glm/matrix.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderFuncs.h"
#include "Plane.h"


# define WIDTH 640.0f
# define HEIGHT 480.0f 

Application::Application() : PlanoPlox(),
	                         Input(0),

							 eye(0.0f, 80.0f, 70.0f),
							 target(0.0f,0.0f,0.0f),
							 up(0.0f,1.0f,0.0f),
	                         luz(-20.0f,0.0f,0.0f)
{}

Application::~Application() 
{}

void Application::setup()
{
	PlanoPlox.createPlane(100);
    //Phong
	//std::string sVertex = loadTextFile("Shaders/passThru.v");
	//std::string sFragment = loadTextFile("Shaders/passThru.f");
	//gouraud
	std::string sVertex = loadTextFile("Shaders/gouraud.v");
	std::string sFragment = loadTextFile("Shaders/gouraud.f");
	InitializeProgram(PlanoPlox.shader[0], sVertex, sFragment);
	
	PlanoPlox.uTransform[0] = glGetUniformLocation(PlanoPlox.shader[0], "mTransform");
	PlanoPlox.uTime[0] = glGetUniformLocation(PlanoPlox.shader[0], "fTime");
	PlanoPlox.Light[0] = glGetUniformLocation(PlanoPlox.shader[0], "myLightPosition");
	PlanoPlox.Ojo[0] = glGetUniformLocation(PlanoPlox.shader[0], "vEye");
	glGenVertexArrays(1, &PlanoPlox.vao);
	glBindVertexArray(PlanoPlox.vao);
	glGenBuffers(1, &PlanoPlox.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, PlanoPlox.vbo);
	glBufferData(GL_ARRAY_BUFFER, PlanoPlox.getVertexSizeInBytes() + PlanoPlox.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, PlanoPlox.getVertexSizeInBytes(), PlanoPlox.plane);
	glBufferSubData(GL_ARRAY_BUFFER, PlanoPlox.getVertexSizeInBytes(), PlanoPlox.getTextureCoordsSizeInBytes(), PlanoPlox.textureCoords);   //rascauachamente multiplico por 2 el tama;o de textura para skeletor
	PlanoPlox.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(PlanoPlox.getVertexSizeInBytes()));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

}


void Application::display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mTra = glm::mat4(1.0);
	mTra = glm::rotate(mTra, PlanoPlox.aRotations.x, glm::vec3(1.0, 0.0, 0.0));
	mTra = glm::rotate(mTra, PlanoPlox.aRotations.y, glm::vec3(0.0, 1.0, 0.0));
	mTra = glm::rotate(mTra, PlanoPlox.aRotations.z, glm::vec3(0.0, 0.0, 1.0));
	//Shaders a usar
	glUseProgram(PlanoPlox.shader[0]);
	glm::mat4 mProjection = glm::perspective(45.0f, WIDTH / HEIGHT, 0.1f, 200.0f);//Perspectiva
	glm::mat4 mCamera = glm::lookAt(eye, target, up);

	//acumulación de matrices
	glm::mat4 finalMatrix = glm::mat4(1.0);
	finalMatrix = mProjection * mCamera * mTra;

	glUniformMatrix4fv(PlanoPlox.uTransform[0],1,GL_FALSE, glm::value_ptr(finalMatrix));
	glUniform1f(PlanoPlox.uTime[0], fTime);
	glUniform3fv(PlanoPlox.Light[0], 1, glm::value_ptr(luz));
	glUniform3fv(PlanoPlox.Ojo[0], 1, glm::value_ptr(eye));
	glDrawArrays(GL_TRIANGLES, 0, PlanoPlox.getNumVertex());
}

void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Application::update()
{
	//Input += 1;
	fTime = glfwGetTime();
	PlanoPlox.rotation = glm::rotate(glm::mat4(1.0f), fTime, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Application::keyboard(int key, int scanCode, int action, int mods)
{

}

void Application::cursor_position(double Xpos, double Ypos)
{
	PlanoPlox.aRotations.y = -((Xpos - WIDTH) / 100.0f);
	PlanoPlox.aRotations.x = ((Ypos + HEIGHT) / 100.0f);
}




