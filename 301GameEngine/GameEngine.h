#pragma once
#include "Header.h"
#include "UIManager.h"
#include "GraphicsEngine.h"
#include "AudioEngine.h"

class GameEngine
{
public:
	static std::vector<Event> EventQueue;
	static std::vector<int> subsystems;
	GameEngine();
	~GameEngine();
	void get_element();
	static void initEngine(int argc, char** argv);
	static void startEngine();
	static void updateGame();


private:
	vector<int>::iterator Iter;
};
	

