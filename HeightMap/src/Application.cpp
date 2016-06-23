
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
#include "SOIL.h"
#include "ShaderFuncs.h"
#include "Plane.h"


# define WIDTH 640.0f
# define HEIGHT 480.0f 


std::string strVertexShader, strFragmentShader;

Application::Application() : PlanoPlox(),
	                         Input(0),
							 eye(0.0f, 90.0f, 80.0f),
							 target(0.0f,0.0f,0.0f),
							 up(0.0f,1.0f,0.0f)
{}

Application::~Application() 
{}
void Application::initTexture()
{
	bool text = 0;
	int img_width, img_height;
	int channels;
	//OJO: SOIL	entrega la imagen de cabeza
	unsigned char* img = SOIL_load_image("altura.jpg", &img_width, &img_height, &channels, 0);
	glGenTextures(1, &PlanoPlox.texture_id);
	glBindTexture(GL_TEXTURE_2D, PlanoPlox.texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img_width, img_height, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img);
	// Mipmap generation is now included in OpenGL 3 and above
	glGenerateMipmap(GL_TEXTURE_2D);
	// Trilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
}
void Application::initTexture2()
{
	bool text = 0;
	int img_width, img_height;
	int channels;
	//OJO: SOIL	entrega la imagen de cabeza

	unsigned char* img = SOIL_load_image("altura.jpg", &img_width, &img_height, &channels, 0);  //cambia a skeletorcitos
	glGenTextures(1, &PlanoPlox.texture_id2);
	glBindTexture(GL_TEXTURE_2D, PlanoPlox.texture_id2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexStorage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img_width, img_height, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img);
	// Mipmap generation is now included in OpenGL 3 and above
	glGenerateMipmap(GL_TEXTURE_2D);
	// TriliNear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 1);
}


void Application::setup()
{
	initTexture();
	initTexture2();
	PlanoPlox.createPlane(70);
	std::string sVertex = loadTextFile("Shaders/passThru.v");
	std::string sFragment = loadTextFile("Shaders/passThru.f");
	InitializeProgram(PlanoPlox.shader[0], sVertex, sFragment);
	InitializeProgram(PlanoPlox.shader[1], sVertex, sFragment);

	PlanoPlox.uTransform[0] = glGetUniformLocation(PlanoPlox.shader[0], "mTransform");
	PlanoPlox.uTime[0] = glGetUniformLocation(PlanoPlox.shader[0], "fTime");
	PlanoPlox.uTexture[0] = glGetUniformLocation(PlanoPlox.shader[0], "theTexture");
	
	PlanoPlox.uTransform[1] = glGetUniformLocation(PlanoPlox.shader[0], "mTransform");
	PlanoPlox.uTime[1] = glGetUniformLocation(PlanoPlox.shader[1], "fTime");
	PlanoPlox.uTexture2[1] = glGetUniformLocation(PlanoPlox.shader[1], "theTexture1");
	
	glGenVertexArrays(1, &PlanoPlox.vao);
	glBindVertexArray(PlanoPlox.vao);
	glGenBuffers(1, &PlanoPlox.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, PlanoPlox.vbo);
	glBufferData(GL_ARRAY_BUFFER, PlanoPlox.getVertexSizeInBytes() + PlanoPlox.getTextureCoordsSizeInBytes(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, PlanoPlox.getVertexSizeInBytes(), PlanoPlox.plane);
	glBufferSubData(GL_ARRAY_BUFFER, PlanoPlox.getVertexSizeInBytes(), PlanoPlox.getTextureCoordsSizeInBytes(), PlanoPlox.textureCoords);   //rascauachamente multiplico por 2 el tama;o de textura para skeletor
	PlanoPlox.cleanMemory();

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(PlanoPlox.getVertexSizeInBytes()));

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
	//Seleccionamos los shaders a usar, color
	glUseProgram(PlanoPlox.shader[0]);
	//altura
	glUseProgram(PlanoPlox.shader[1]);
	glm::mat4 mProjection = glm::perspective(45.0f, WIDTH / HEIGHT, 0.1f, 200.0f);//Perspectiva
	glm::mat4 mCamera = glm::lookAt(eye, target, up);

	//acumulación de matrices
	glm::mat4 finalMatrix = glm::mat4(1.0);
	finalMatrix = mProjection * mCamera * mTra;

	glUniformMatrix4fv(PlanoPlox.uTransform[0],1,GL_FALSE, glm::value_ptr(finalMatrix));
	glUniform1f(PlanoPlox.uTime[0], fTime);
	glUniform3fv(PlanoPlox.uLight[0], 1, glm::value_ptr(PlanoPlox.Light));
	glUniform3fv(PlanoPlox.uEye[0], 1, glm::value_ptr(PlanoPlox.Ojo));
	//glUniform1f(PlanoPlox.Input, Input);
	//myLightPosition  y vEye

	//pasamos parametros de texturas
	//textura 0
	glUniform1i(PlanoPlox.uTexture[1], 0);
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, PlanoPlox.texture_id);

	//texrua 1
	glUniform1i(PlanoPlox.uTexture2[1], 1);
	glActiveTexture(GL_TEXTURE1); //gl textura 1                                    //descomenta y cambio textura
	glBindTexture(GL_TEXTURE_2D, PlanoPlox.texture_id2); //segunda id



	//activamos el vertex array object y dibujamos
	glDrawArrays(GL_TRIANGLES, 0, PlanoPlox.getNumVertex());
}

void Application::reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Application::update()
{
	Input += 1;
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




