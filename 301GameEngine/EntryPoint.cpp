#include "event.h"
#include "GameEngine.h"
#include "Header.h"
#include "SubSystemSuper.h"

bool SubSystemSuper::debugMode = false;

int main(int argc, char ** argv)
{
	GameEngine::initEngine(argc, argv);
}