#include "GameEngine.h"

#include "UIManager.h"
#include "GraphicsEngine.h"

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::initEngine(int argc, char** argv)
{
	//Initialise Graphics Engine
	GraphicsEngine::initEngine(argc, argv);

	//Initialise UIManager
	UIManager::initEngine(argc, argv);

	//Initialise Physics Engine

	//start the engine
	startEngine();
}

void GameEngine::startEngine()
{
	cout << "press ESC to close" << endl;
	glutMainLoop();
}
