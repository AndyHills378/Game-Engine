#pragma once
#include <cstdlib>
#include <map>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

//reactphysics includes (physics)
#include <reactphysics3d.h>

//freeglut includes (Graphics)
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/vec3.hpp>

//FMOD includes (Audio)
#include <fmod_studio.hpp>
#include <fmod.hpp>

using namespace std;
using namespace glm;

static enum object { FIELD, SKY }; /// VAO ids.
static enum buffer { FIELD_VERTICES, SKY_VERTICES }; // VBO ids.

static mat4 modelMat = mat4(1.0);
static mat4 viewMat = mat4(1.0);
static mat4 projMat = mat4(1.0);
static mat3 normalMat = mat3(1.0);



