#pragma once
#include <cstdlib>
#include <map>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

//reactphysics includes (physics)
#include <reactphysics3d.h>

//freeglut includes (Graphics)
#include "freeGlut-library/GL/glew.h"
#include "freeGlut-library/GL/freeglut.h"
#include "freeGlut-library/GL/glext.h"
#include "freeGlut-library/glm/glm.hpp"
#include <freeGlut-library/glm/gtc/matrix_transform.hpp>
#include <freeGlut-library/glm/gtc/type_ptr.hpp>
#include <freeGlut-library/glm/gtc/matrix_inverse.hpp>
#include <freeGlut-library/glm/gtx/rotate_vector.hpp>
#include <freeGlut-library/glm/vec3.hpp>

using namespace std;
using namespace glm;

static enum object { FIELD, SKY }; /// VAO ids.
static enum buffer { FIELD_VERTICES, SKY_VERTICES }; // VBO ids.


