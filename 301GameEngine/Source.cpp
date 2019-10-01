#include "GraphicsEngine.h"

int main(int argc, char ** argv)
{
	GameObject::debugMode = true;
	GraphicsEngine::initEngine(argc, argv);

	GraphicsEngine::startEngine();
}