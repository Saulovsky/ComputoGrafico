#version 430 core

out vec4 fColor;
in vec2 texCoord;

uniform sampler2D theTexture;
uniform sampler2D theTexture1;


void main()
{
    fColor = texture(theTexture, texCoord) * texture(theTexture1, texCoord);
}
