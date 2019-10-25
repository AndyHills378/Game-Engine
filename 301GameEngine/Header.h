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

//LUA includes (custom compiler)
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
#include <LuaBridge/LuaBridge.h>

//E-Net includes (Networking)
#include <enet/enet.h>

using namespace std;
using namespace glm;

static unsigned int
vertexShaderId,
fragmentShaderId,
viewMatLoc,
modelMatLoc,
projMatLoc,
normalMatLoc,

light0coordsLoc,
alphaLoc,
buffer[5],
vao[4],
texture[4];



static enum object { FIELD, SKY, TRACK }; /// VAO ids.
static enum buffer { FIELD_VERTICES, SKY_VERTICES, TRACK_VERTICES, TRACK_NORMALS }; // VBO ids.

static mat4 modelMat = mat4(1.0);
static mat4 viewMat = mat4(1.0);
static mat4 projMat = mat4(1.0);
static mat3 normalMat = mat3(1.0);


