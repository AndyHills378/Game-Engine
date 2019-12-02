#version 430 core

in vec4 normalsExport;
in vec2 texCoordsExport;

uniform sampler2D tex;

uniform float alpha;

out vec4 colorsOut;

void main(void)
{  
	vec4 texColor;
	texColor = texture(tex, texCoordsExport);
	colorsOut = texColor;
  // colorsOut = vec4(1,0,1,1);
}