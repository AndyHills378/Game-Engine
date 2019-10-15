#include "UIManager.h"
#include "event.h"
#include "GameEngine.h"

std::map <int, bool> SubSystemSuper::specialKeys;
std::map <char, bool> SubSystemSuper::keys;

/*void UIManager::setMouseMove(int x, int y)
{
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	float xoffset = x - lastX;
	float yoffset = lastY - y;
	lastX = x;
	lastY = y;

	float sensitivity = 0.3f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	UIManager::yaw += xoffset;
	UIManager::pitch += yoffset;

	if (UIManager::pitch > 89.0f) UIManager::pitch = 89.0f;
	if (UIManager::pitch < -89.0f) UIManager::pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(UIManager::yaw)) * cos(glm::radians(UIManager::pitch));
	front.y = sin(glm::radians(UIManager::pitch));
	front.z = sin(glm::radians(UIManager::yaw)) * cos(glm::radians(UIManager::pitch));
	UIManager::cameraFront = glm::normalize(front);

	//forces mouse to stay in the window
	int win_w = glutGet(GLUT_WINDOW_WIDTH);
	int win_h = glutGet(GLUT_WINDOW_HEIGHT);
	if (x < 100 || x > win_w - 100)
	{
		lastX = win_w / 2;
		lastY = win_h / 2;
		glutWarpPointer(win_w / 2, win_h / 2);
	}
	else if (y < 100 || win_h - 100)
	{
		lastX = win_w / 2;
		lastY = win_h / 2;
		glutWarpPointer(win_w / 2, win_h / 2);
	}
}*/

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
		myEvent.addSubsystem((SubSystemEnum)0); // 0 - GraphicsEngine
		myEvent.addSubsystem((SubSystemEnum)2); // 2 - AudioEngine
		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 's':
	{
		Event myEvent((EventTypeEnum)1); // 1 - Backwards
		myEvent.addSubsystem((SubSystemEnum)0); // 0 - GraphicsEngine
		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 'a':
	{
		Event myEvent((EventTypeEnum)2); // 2 - Turn Left
		myEvent.addSubsystem((SubSystemEnum)0); // 0 - GraphicsEngine
		GameEngine::EventQueue.push_back(myEvent);
		break;
	}
	case 'd':
	{
		Event myEvent((EventTypeEnum)3); // 3 - Turn Right
		myEvent.addSubsystem((SubSystemEnum)0); // 0 - GraphicsEngine
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
