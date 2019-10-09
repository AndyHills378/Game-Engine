#include "UIManager.h"
//#include "event.h"

std::map <int, bool> GameEngine::specialKeys;
std::map <char, bool> GameEngine::keys;
/*glm::vec3 UIManager::cameraPos = glm::vec3(0.0f, 5.0f, 0.0f);
glm::vec3 UIManager::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float UIManager::yaw = 90.0f;
float UIManager::pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
float fov = 45.0f;*/
//bool GameEngine::debugMode = false;

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
		if (GameEngine::debugMode) GameEngine::debugMode = false;
		else GameEngine::debugMode = true;
		break;
	case 'w':
	{
		/*Event myEvent(accelerate);
		myEvent.addSubsystem(graphicsEngine);
		EventQueue.push_back(myEvent);*/
		//UIManager::cameraPos += cameraSpeed * UIManager::cameraFront;
		break;
	}
	case 'a':
		//UIManager::cameraPos -= glm::normalize(glm::cross(UIManager::cameraFront, cameraUp)) * cameraSpeed;
		break;
	case 's':
		//UIManager::cameraPos -= cameraSpeed * UIManager::cameraFront;
		break;
	case 'd':
		//UIManager::cameraPos += glm::normalize(glm::cross(UIManager::cameraFront, cameraUp)) * cameraSpeed;
		break;
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
	GameEngine::specialKeys[key] = false;
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
