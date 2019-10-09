#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "Header.h"

class UIManager : public GameEngine
{
private:
	//static void setMouseMove(int x, int y);
	static void setKeyInput(unsigned char key, int x, int y);
	static void setSpecialKeyInput(int key, int x, int y);
	static void setSpecialKeyUp(int key, int x, int y);
	static void joyStick(unsigned int buttonmask, int x, int y, int z);
public:
	UIManager();
	~UIManager();	
	static void initEngine(int argc, char** argv);
};

