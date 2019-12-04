#include "GameEngine.h"
#include "Track.h"

#include "GameObject.h"

std::vector<Event> GameEngine::EventQueue;
std::vector<int> GameEngine::subsystems;
std::vector<GameObject*> GameEngine::gameobjects;
int GameEngine::oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
int GameEngine::newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
int deltaTime;
int GameEngine::levelId;
bool valid;

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::initEngine(int argc, char** argv)
{
	glutInit(&argc, argv);
	while (!valid) {
		cout << "Choose the level that you want to load (1 or 2): \n";
		cin >> levelId;
		if (levelId == 1 || levelId == 2)
		{
			valid = true;
		}
	}

	glutIdleFunc([]() {GameEngine::updateGame(); }); //idle function
	//Initialise Graphics Engine
	GraphicsEngine::initEngine(argc, argv);

	//Initialise UIManager
	UIManager::initEngine(argc, argv);

	//Initialise Audio Engine
	AudioEngine::initEngine();

	//Initialise Physics Engine
	PhysicsEngine::initEngine();

	if (levelId == 1) {
		//gameobjects.push_back(new GameObject((char*)"level.lua", (char*)"environmentTest.obj", (char*)"environment", 0));
		gameobjects.push_back(new GameObject((char*)"level.lua", (char*)"mustang.obj", (char*)"mustang", 1));
	}
	if (levelId == 2) {
		//gameobjects.push_back(new GameObject((char*)"level2.lua", (char*)"environmentTest.obj", (char*)"environment", 0));
		gameobjects.push_back(new GameObject((char*)"level2.lua", (char*)"mustang.obj", (char*)"mustang", 1));
	}

	//Initialise Network Engine
	NetworkEngine::initEngine();

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
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = newTimeSinceStart - oldTimeSinceStart;
	
	//If the last frame was rendered less than 1 ms ago, the deltaTime will be 0 ms. This causes problems in calculations, so sleep for 1ms to adjust.
	if (deltaTime == 0) {
		Sleep(1);
		newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = newTimeSinceStart - oldTimeSinceStart;
	}

	UIManager::updateGame(deltaTime);
	GraphicsEngine::updateGame(deltaTime);
	AudioEngine::updateEngine(deltaTime);
	PhysicsEngine::updateEngine(deltaTime);
	NetworkEngine::updateEngine(deltaTime);

	if (EventQueue.size() > 0)
	{
		for (int i = 0; i < EventQueue.size();i++)
		{
			if (EventQueue[i].mySubSystems.size() == 0)
			{
				EventQueue.erase(EventQueue.begin() + i);
				cout << "Event erased\n";
			}
		}
	}
}
