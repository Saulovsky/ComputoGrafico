#version 430 core
layout (location = 0) in vec4 vPosition;

//luz->normales->posvertices

uniform mat4 mTransform;
uniform float fTime;
uniform vec3 vEye;
uniform vec3 myLightPosition;
out vec3 newNormal;
out vec4 vNewVec; 
out vec4 color;
out vec3 lightv;


//Derivada parcial de "a"
float Dp(float a, float b) 
{
	return	-4.0 * a * 0.04 * sin(0.0002 * (a*a + b*b) + fTime);
}
float F(float x, float z) 
{
	return 2.0 * cos  (0.02 * (x*x + z*z) + fTime); 
}
//calculamos la normal antes de aplicar transformaciones
vec3 calculateNormal (vec4 v)
{
	vec3 vt1 = vec3(1.0, Dp(v.x, v.z), 0.0);
	vec3 vt2 = vec3(0.0, Dp(v.z, v.x), 1.0);

	return cross (vt1, vt2);
}
void main()
{
vec4 vNewVec = vPosition;
	//calculamos la altura de este vertice
	vNewVec.y = F(vNewVec.x, vNewVec.z);

	//CALCULO DE NORMALES
	vec3 normal = normalize(calculateNormal (vNewVec));
	mat4 matForNormals = transpose(inverse(mTransform));
	newNormal = normalize(matForNormals * vec4(normal, 1.0)).xyz;

	//calculo de posicion de luz
	lightv = normalize( myLightPosition - vNewVec.xyz);
gl_Position = mTransform * vNewVec;
}

//tarea normal= color -> out vec3 normal = texture(tex, texcoord).xyz -> normalize(normal), phong en fragment