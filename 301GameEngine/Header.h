#pragma once
#include <cstdlib>
#include <map>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include  "stb_image.h"

//Nvidia PhysX includes (physics)
#include <PxPhysicsAPI.h>
#include <vehicle/PxVehicleSDK.h>
#include <memory>
#include <PxPhysics.h>
#include "foundation/Px.h"
#include <foundation/PxFoundationVersion.h>
#include "common/PxPhysXCommonConfig.h"

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

#include "light.h"

using namespace std;
using namespace glm;
using namespace luabridge;

static unsigned int
vertexShaderId,
fragmentShaderId,
viewMatLoc,
modelMatLoc,
projMatLoc,
normalMatLoc,

light0coordsLoc,
alphaLoc;

#define PI 3.14159265358979324

static mat4 modelMat = mat4(1.0);
static mat4 viewMat = mat4(1.0);
static mat4 projMat = mat4(1.0);
static mat3 normalMat = mat3(1.0);


