#pragma once
#include "Header.h"

static mat4 modelMat = mat4(1.0);
static mat4 viewMat = mat4(1.0);
static mat4 projMat = mat4(1.0);
static mat3 normalMat = mat3(1.0);

class GameEngine
{
public:
	static std::map <int, bool> specialKeys;
	static std::map <char, bool> keys;
	static bool debugMode;
	GameEngine();
	~GameEngine();
	static void initEngine(int argc, char** argv);
	static void startEngine();
};

