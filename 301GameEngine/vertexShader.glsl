#version 430 core

layout(location=0) in vec3 Coords;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 TexCoords;


uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat3 normalMat;

out vec4 normalsExport;
out vec2 texCoordsExport;

struct Light
{
   vec4 ambCols;
   vec4 difCols;
   vec4 specCols;
   vec4 coords;
};
uniform Light light0;

uniform vec4 globAmb;
  
struct Material
{
   vec4 ambRefl;
   vec4 difRefl;
   vec4 specRefl;
   vec4 emitCols;
   float shininess;
};

uniform Material matFandB;

vec3 normal, lightDirection, eyeDirection, halfway;
vec4 fAndBEmit, fAndBGlobAmb, fAndBAmb, fAndBDif, fAndBSpec;
vec4 coords;

uniform uint object;
uniform vec3 cameraPos;

void main(void)
{   
	//normalsExport = vec4(Normal,1.0);
	texCoordsExport = TexCoords;
	/*if(object == 1)
	{
		gl_Position = projMat * viewMat * modelMat * vec4(Coords+cameraPos, 1.0);
	}
	else{*/
		gl_Position = projMat * viewMat * modelMat * vec4(Coords, 1.0);
	//}
}




