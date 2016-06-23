#version 430 core
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

out vec2 texCoord; 
varying vec3 vEye;

uniform mat4 mTransform;

void main()
{
	texCoord = vTexCoord;
	gl_Position = mTransform * vPosition;
}
