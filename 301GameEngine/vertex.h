#ifndef VERTEX_H
#define VERTEX_H

#include "Header.h"

struct Vertex
{
   glm::vec3 coords;
   glm::vec3 normal;
   glm::vec2 texCoords;
};

struct VertexWithNormal
{
	glm::vec4 coords;
	glm::vec3 normals;
};

#endif
