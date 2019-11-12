#pragma once
#include "Header.h"
#include "SubSystemSuper.h"
#include "GameEngine.h"

class PhysicsEngine : public SubSystemSuper
{
private:
	static int oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
	static int newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
public:
	static int(*EventReaction[4])();
	PhysicsEngine();
	~PhysicsEngine();
	static void initEngine();
	static void updateEngine();
};

