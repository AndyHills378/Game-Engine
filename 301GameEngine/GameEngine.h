#pragma once
#include "Header.h"
#include "UIManager.h"
#include "GraphicsEngine.h"
#include "AudioEngine.h"
#include "PhysicsEngine.h"
#include "NetworkEngine.h"

class GameObject;

class GameEngine
{
private:
	static int oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
	static int newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
	vector<int>::iterator Iter;
public:
	static std::vector<Event> EventQueue;
	static std::vector<int> subsystems;
	static std::vector<GameObject*> gameobjects;

	GameEngine();
	~GameEngine();
	static void initEngine(int argc, char** argv);
	static void startEngine();
	static void updateGame();
};
	

