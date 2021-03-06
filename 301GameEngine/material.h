#ifndef MATERIAL_H
#define MATERIAL_H

#include "Header.h"

struct Material
{
   glm::vec4 ambRefl;
   glm::vec4 difRefl;
   glm::vec4 specRefl;
   glm::vec4 emitCols;
   float shininess;
};

#endif
