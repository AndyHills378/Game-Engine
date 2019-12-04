#pragma once
#include "Header.h"
#include "SubSystemSuper.h"
#include "GameEngine.h"

using namespace physx;

#define TURNING_SPEED 3.0
#define MOVE_SPEED 100.0

class UserErrorCallback : public PxErrorCallback
{
public:
	virtual void reportError(PxErrorCode::Enum code, const char* message, const char* file,
		int line)
	{
		// error processing implementation
		std::cout << "Bad stuff happen\n";
	}
};

class PhysicsEngine : public SubSystemSuper
{
private:
public:
	static float Acceleration;
	static glm::vec3 NewVelocity;
	static glm::vec3 Velocity;
	static int oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
	static int newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
	static int(*EventReaction[4])();
	static int pxAccelerate();
	static int pxDecelerate();
	static int pxTurnLeft();
	static int pxTurnRight();
	PhysicsEngine();
	~PhysicsEngine();
	static void customizeSceneDesc(PxSceneDesc& sceneDesc);
	static void initEngine();
	static void updateEngine(int deltaTime);
};

