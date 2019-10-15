#pragma once
#include "SubSystemSuper.h"
#include "GameObject.h"
#include "Header.h"

class UIManager : public SubSystemSuper
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
	//std::vector<Event>* eQ; //Might want to pass in pointer to the event queue in the constructor, when GameEngine makes UISubsystem
};

