#pragma once
#include "Header.h"

class CubeMap
{
public:
	glm::vec3 coords1, coords2, coords3, coords4;

	CubeMap(char* filename);
	~CubeMap();
};

