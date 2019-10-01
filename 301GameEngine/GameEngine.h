#pragma once
#include "Header.h"

class GameEngine
{
public:
	static bool debugMode;
	GameEngine();
	~GameEngine();
	static void initEngine(int argc, char** argv);
	static void startEngine();
};

