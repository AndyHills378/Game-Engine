#include "UIManager.h"
#include "event.h"
#include "GameEngine.h"

std::map <int, bool> SubSystemSuper::specialKeys;
std::map <char, bool> SubSystemSuper::keys;
int UIManager::cameraMode = 1;
int(*UIManager::EventReaction[5])();

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

		if(cameraMode==1){ myEvent.addSubsystem((SubSystemEnum)3); }// 3 - PhysicsEngine
		else { myEvent.addSubsystem((SubSystemEnum)0); } // 0 - GraphicsEngine

		myEvent.addSubsystem((SubSystemEnum)2); // 2 - AudioEngine
		myEvent.addSubsystem((SubSystemEnum)4); // 4 - NetworkEngine
		
		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 's':
	{
		Event myEvent((EventTypeEnum)1); // 1 - Backwards

		if (cameraMode == 1) { myEvent.addSubsystem((SubSystemEnum)3); }// 3 - PhysicsEngine
		else { myEvent.addSubsystem((SubSystemEnum)0); } // 0 - GraphicsEngine

		myEvent.addSubsystem((SubSystemEnum)4); // 4 - NetworkEngine

		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 'a':
	{
		Event myEvent((EventTypeEnum)2); // 2 - Turn Left

		if (cameraMode == 1) { myEvent.addSubsystem((SubSystemEnum)3); }// 3 - PhysicsEngine
		else { myEvent.addSubsystem((SubSystemEnum)0); } // 0 - GraphicsEngine

		myEvent.addSubsystem((SubSystemEnum)4); // 4 - NetworkEngine

		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 'd':
	{
		Event myEvent((EventTypeEnum)3); // 3 - Turn Right

		if (cameraMode == 1) { myEvent.addSubsystem((SubSystemEnum)3); }// 3 - PhysicsEngine
		else { myEvent.addSubsystem((SubSystemEnum)0); } // 0 - GraphicsEngine

		myEvent.addSubsystem((SubSystemEnum)4); // 4 - NetworkEngine

		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 'c':
		Event myEvent((EventTypeEnum)4);
		myEvent.addSubsystem((SubSystemEnum)0); // 0 - GraphicsEngine
		myEvent.addSubsystem((SubSystemEnum)1); // 1 - UIManager

		GameEngine::EventQueue.push_back(myEvent);

	}
}

int UIManager::cameraSwitch()
{
	if (cameraMode == 1) { cameraMode = 2; }
	else { cameraMode = 1; }
	return 0;
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
	int(*p_grCamera)() = cameraSwitch;
	EventReaction[4] = p_grCamera;
}

void UIManager::updateGame(int deltaTime)
{
	//read event queue
	for (int i = 0; i < GameEngine::EventQueue.size();i++)
	{
		for (int j = 0; j < GameEngine::EventQueue[i].mySubSystems.size(); j++)
		{
			if (GameEngine::EventQueue[i].mySubSystems[j] == SubSystemEnum::uiManager)
			{
				EventReaction[(int)GameEngine::EventQueue[i].myType]();
				GameEngine::EventQueue[i].mySubSystems.erase(GameEngine::EventQueue[i].mySubSystems.begin() + j);
			}
		}
	}
	glutPostRedisplay();
}
