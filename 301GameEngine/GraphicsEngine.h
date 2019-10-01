#pragma once
#include "GameObject.h"
#include "GameEngine.h"
#define PI 3.14159265358979324


class GraphicsEngine : public GameEngine
{
private:
	static int oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
	static int newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
public:
	static float linetheta;
	static int sphereToDraw;
	static unsigned int programId;
	static vector<GameObject*> gameobjects;
	static float yaw;
	static float pitch;
	static void setup(void);
	static void drawScene();
	static void updateGame();
	GraphicsEngine();
	~GraphicsEngine();
	static void initEngine(int argc, char **argv);
	static void addGameObject(GameObject *gameobject);
};
