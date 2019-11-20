#pragma once
#include "Header.h"
#include "UIManager.h"
#include "GraphicsEngine.h"
#include "AudioEngine.h"
#include "PhysicsEngine.h"

class GameObject;

class GameEngine
{
private:
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
	

