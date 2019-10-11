#include "GameEngine.h"

std::vector<Event> GameEngine::EventQueue;
std::vector<int> GameEngine::subsystems;

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::get_element()
{
	for (int x = 0; x < subsystems.size(); x++)
	{
		cout << subsystems[x] << " \n";
	};
	cout << " \n";
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

void GameEngine::updateGame()
{
	if (EventQueue.size() > 0)
	{
		for (int i = 0; i < EventQueue.size();i++)
		{
			if (EventQueue[i].mySubSystems.size() == 0)
			{
				EventQueue.erase(EventQueue.begin() + i);
				cout << "Event erased\n";
				/*EventReaction[(int)GameEngine::EventQueue[i].myType]();
				GameEngine::EventQueue[i].mySubSystems.erase(GameEngine::EventQueue[i].mySubSystems.begin() + j);*/
			}
		}
	}
}
