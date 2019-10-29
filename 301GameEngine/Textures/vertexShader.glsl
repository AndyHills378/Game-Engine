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

void main(void)
{   
	//normalsExport = vec4(Normal,1.0);
	texCoordsExport = TexCoords;
    gl_Position = projMat * viewMat * modelMat * vec4(Coords, 1.0);
}
