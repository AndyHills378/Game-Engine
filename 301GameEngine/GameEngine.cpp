#include "GameEngine.h"
#include "Track.h"

#include "GameObject.h"

std::vector<Event> GameEngine::EventQueue;
std::vector<int> GameEngine::subsystems;
std::vector<GameObject*> GameEngine::gameobjects;

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{
}

void GameEngine::initEngine(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutIdleFunc([]() {GameEngine::updateGame(); }); //idle function
	//Initialise Graphics Engine
	GraphicsEngine::initEngine(argc, argv);

	//Initialise UIManager
	UIManager::initEngine(argc, argv);

	//Initialise Audio Engine
	AudioEngine::initEngine();

	//Initialise Physics Engine
	PhysicsEngine::initEngine();

	gameobjects.push_back(new GameObject((char*)"environment.obj", (char*)"environment", 0));
	gameobjects.push_back(new GameObject((char*)"mustang.obj", (char*)"mustang", 1));

	//start the engine
	startEngine();
}

void GameEngine::startEngine()
{
	cout << "press ESC to close" << endl;
	//GraphicsEngine::addGameObject(new Track(glm::vec3(0, 1, 0)));
	glutMainLoop();
}

void GameEngine::updateGame()
{
	GraphicsEngine::updateGame();

	AudioEngine::updateEngine();

	PhysicsEngine::updateEngine();

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
