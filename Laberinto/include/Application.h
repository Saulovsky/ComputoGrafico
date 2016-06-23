#pragma once

#include <iostream>
#include "Object3D.h"

class Application {
public:
	Application();
	~Application();

	GLint uAngle;
	float fAngle;
	GLint uTransform;
	void setup();
	void display();
	void reshape(int w, int h);
	void loadShaders();
	void update();
	void keyboard(int key, int scanCode, int action, int mods);

private:	
	Object3D cube;

	glm::mat4 camera;
	glm::vec3 eye, target;
};

