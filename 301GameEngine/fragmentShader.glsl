#version 430 core

in vec4 normalsExport;
in vec2 texCoordsExport;

uniform sampler2D tex;

uniform float alpha;

out vec4 colorsOut;

vec4 texColor;

void main(void)
{  
   texColor = texture(tex, texCoordsExport);
   colorsOut = texColor;
  // colorsOut = vec4(1,0,1,1);
}