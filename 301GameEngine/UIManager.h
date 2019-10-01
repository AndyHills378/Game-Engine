#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Header.h"

class UIManager : public GameEngine
{
private:
	static void setMouseMove(int x, int y);
	static void setKeyInput(unsigned char key, int x, int y);
	static void setSpecialKeyInput(int key, int x, int y);
	static void setSpecialKeyUp(int key, int x, int y);
	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static float yaw;
	static float pitch;
public:
	UIManager();
	~UIManager();	
	static void initEngine(int argc, char** argv);
	static glm::vec3 getCameraPos();
	static glm::vec3 getCameraFront();
	static glm::vec3 getCameraUp();
};

