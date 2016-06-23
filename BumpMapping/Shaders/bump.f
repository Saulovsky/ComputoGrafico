#version 430 core
out vec4 fColor;

in vec2 texCoord;
in vec3 vEye;
uniform mat4 mTransform;

uniform sampler2D theTexture;
uniform sampler2D normal;

const vec3 lA = vec3( 0.2, 0.2, 0.2 );
const vec3 lD = vec3( 0.5, 0.5, 0.5 );
const vec3 lS = vec3( 1.0, 1.0, 1.0 );

const vec3 mA = vec3( 0.7, 0.9, 0.0 );
const vec3 mD = vec3( 0.3, 0.3, 0.0 );
const vec3 mS = vec3( 0.7, 0.7, 0.7 );
const float fShininess = 50.0;
vec4 lightPos;


vec3 getAmbient()
{
	return lA * mA;
}

vec3 getDiffuse (in vec3 lightv, in vec3 norm)
{
	return max(0.0, dot(lightv, norm)) * mD * lD;
}

vec3 getSpecular(in vec3 lightv, in vec3 norm)
{
	vec3 refl = reflect( vec3(0.,0.,0.) - lightv, norm );
	vec3 viewv = normalize( vec3(0.,0.,0.) - vEye );

	vec3 specular = vec3( 0.0, 0.0, 0.0 );
	if( dot(lightv, viewv) > 0.0)
	{
		specular = pow(max(0.0, dot(viewv,refl)), fShininess) * mS * lS;
	}
	return specular;	
}


vec3 ADSLightModel( in vec3 myNormal, in vec3 myPosition )
{
	vec3 norm = normalize( myNormal );
	vec3 lightv = normalize( lightPos.xyz - myPosition);

	vec3 ambient = getAmbient();
	vec3 diffuse = getDiffuse(lightv, norm); 
	vec3 specular = getSpecular (lightv, norm);
	
	return clamp( ambient + diffuse /*+ specular*/, 0.0, 1.0);
}



void main()
{
	lightPos = vec4(1.0 , 1.0, 1.0, 1.0);
	lightPos = mTransform * lightPos;
	mat4 Normals = transpose(inverse(mTransform));
	vec3 normal = texture(normal, texCoord).rgb;
	vec3 newNormal = (Normals * vec4(normal, 1.0)).xyz;

	fColor = vec4(ADSLightModel(newNormal, vEye), 1.0) * texture(theTexture, texCoord);
}
