#include "event.h"
#include "GameEngine.h"
#include "Header.h"
#include "SubSystemSuper.h"
#include "Track.h"

bool SubSystemSuper::debugMode = false;

int main(int argc, char** argv)
{
	GameEngine::initEngine(argc, argv);

	GraphicsEngine::addGameObject(new Track(glm::vec3(0, 1, 0)));

	//GameEngine::startEngine();
}
	