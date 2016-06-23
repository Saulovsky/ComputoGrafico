//recibe pos. luz, normales y posvecs, calcula color
#version 430 core
uniform vec3 vEye;
uniform vec3 myLightPosition;
out vec4 color;
in vec3 lightv;
in vec3 newNormal;
in vec4 vNewVec; 

vec3 getAmbient(in vec3 light, in vec3 mat)
{
	return light * mat;
}
vec3 getDifusse(in vec3 light, in vec3 mat, in vec3 lightv, in vec3 Normal)
{
	return max(0.0, dot(lightv, Normal)) * mat * light;
}
vec3 getSpecular( in vec3 light, in vec3 mat, in vec3 lightv, in vec3 Normal, in float shininess, in vec3 myPos)
{
	vec3 viewv = normalize( vEye - myPos);
	vec3 refl = normalize(reflect(vEye - lightv, Normal ));
	//specular light computation
	vec3 specular = vec3( 0.0, 0.0, 0.0 );
	if( dot(lightv, viewv) > 0.0)
	{
		specular = pow(max(0.0, dot(viewv, refl)), shininess) * lightv * mat;
	}
	return specular;
}

void main()
{
    const vec3 lA = vec3( 0.1, 0.1, 0.1 );
	const vec3 lD = vec3( 0.3, 0.3, 0.3 );
	const vec3 lS = vec3( 1.0, 1.0, 1.0); 

		//const vec3 lS = vec3( 0.0, 0.0, 0.0 );

	const vec3 mA = vec3( 0.4, 0.0, 0.8);
	const vec3 mD = vec3( 1.0, 0.0, 0.0 );
	const vec3 mS = vec3( 0.6, 0.0, 0.9 );

	const float fShininess = 10.0;
color = clamp(
			  vec4(getAmbient(lA, mA), 1.0) 
			+ vec4(getDifusse(lD, mD, lightv, newNormal), 1.0)
			+ vec4(getSpecular(lS, mS, lightv, newNormal, fShininess, vNewVec.xyz), 1.0)
			,0.0, 1.0);
}