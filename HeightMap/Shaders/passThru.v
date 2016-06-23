#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 mTransform;
uniform sampler2D theTexture;

out vec2 texCoord;

vec4 mathFunc(vec4 r, float Luminosity)
{
r.y = (8*Luminosity);
//r.y = (30*Luminosity * sin(input)); //desmadrito
return r;
}

void main()
{
    vec4 Color = texture(theTexture, vTexCoord);
	float Luminosity = (0.299 * Color.r + 0.587 * Color.g + 0.114 * Color.b);
	texCoord = vTexCoord;
	gl_Position = mTransform * mathFunc(vPosition, Luminosity);

}
//tarea normal= color -> out vec3 normal = texture(tex, texcoord).xyz -> normalize(normal), phong en fragment