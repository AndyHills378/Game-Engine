#include "GameEngine.h"
#include "Track.h"

#include "GameObject.h"

std::vector<Event> GameEngine::EventQueue;
std::vector<int> GameEngine::subsystems;
std::vector<GameObject*> GameEngine::gameobjects;
int GameEngine::oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
int GameEngine::newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
int deltaTime;

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

	//gameobjects.push_back(new GameObject((char*)"environment.obj", (char*)"environment", 0, false));
	gameobjects.push_back(new GameObject((char*)"mustang.obj", (char*)"mustang", 1, true));

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
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = newTimeSinceStart - oldTimeSinceStart;
	
	//If the last frame was rendered less than 1 ms ago, the deltaTime will be 0 ms. This causes problems in calculations, so sleep for 1ms to adjust.
	if (deltaTime == 0) {
		Sleep(1);
		newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = newTimeSinceStart - oldTimeSinceStart;
	}

	GraphicsEngine::updateGame(deltaTime);

	AudioEngine::updateEngine(deltaTime);

	PhysicsEngine::updateEngine(deltaTime);

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
