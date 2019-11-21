#include "UIManager.h"
#include "event.h"
#include "GameEngine.h"

std::map <int, bool> SubSystemSuper::specialKeys;
std::map <char, bool> SubSystemSuper::keys;

void UIManager::setKeyInput(unsigned char key, int x, int y)
{
	int id = 0;
	float cameraSpeed = 0.5f;
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 't':
		if (SubSystemSuper::debugMode) SubSystemSuper::debugMode = false;
		else SubSystemSuper::debugMode = true;
		break;
	case 'w':
	{
		Event myEvent((EventTypeEnum)0); // 0 - Accelerate
		//myEvent.addSubsystem((SubSystemEnum)0); // 0 - GraphicsEngine
		myEvent.addSubsystem((SubSystemEnum)2); // 2 - AudioEngine
		myEvent.addSubsystem((SubSystemEnum)3); // 0 - PhysicsEngine
		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 's':
	{
		Event myEvent((EventTypeEnum)1); // 1 - Backwards
		//myEvent.addSubsystem((SubSystemEnum)0); // 0 - GraphicsEngine
		myEvent.addSubsystem((SubSystemEnum)3); // 0 - PhysicsEngine
		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 'a':
	{
		Event myEvent((EventTypeEnum)2); // 2 - Turn Left
		//myEvent.addSubsystem((SubSystemEnum)0); // 0 - GraphicsEngine
		myEvent.addSubsystem((SubSystemEnum)3); // 0 - PhysicsEngine
		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 'd':
	{
		Event myEvent((EventTypeEnum)3); // 3 - Turn Right
		//myEvent.addSubsystem((SubSystemEnum)0); // 0 - GraphicsEngine
		myEvent.addSubsystem((SubSystemEnum)3); // 0 - PhysicsEngine
		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 'g':
		id++;
	}
}

void UIManager::setSpecialKeyInput(int key, int x, int y)
{
	glutPostRedisplay();
}

void UIManager::setSpecialKeyUp(int key, int x, int y)
{
	SubSystemSuper::specialKeys[key] = false;
}

void UIManager::joyStick(unsigned int buttonmask, int x, int y, int z)
{
}

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::initEngine(int argc, char** argv)
{
	//glutPassiveMotionFunc(setMouseMove);
	glutKeyboardFunc(setKeyInput);
	glutSpecialFunc(setSpecialKeyInput);
	glutSpecialUpFunc(setSpecialKeyUp);
	glutJoystickFunc(joyStick, 20);
	cout << "UI Manager loaded" << endl;
}

/*glm::vec3 UIManager::getCameraPos()
{
	return cameraPos;
}

glm::vec3 UIManager::getCameraFront()
{
	return cameraFront;
}

glm::vec3 UIManager::getCameraUp()
{
	return cameraUp;
}*/
