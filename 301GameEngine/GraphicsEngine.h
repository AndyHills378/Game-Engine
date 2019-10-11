#pragma once
#include "GameObject.h"
#include "SubSystemSuper.h"
#define PI 3.14159265358979324


class GraphicsEngine : public SubSystemSuper
{
private:
	static int oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
	static int newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
public:
	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static float yaw;
	static float pitch;
	static float cameraSpeed;

	static float linetheta;
	static int sphereToDraw;
	static unsigned int programId;
	static vector<GameObject*> gameobjects;
	static int(*EventReaction[4])();

	static void setup(void);
	static void drawScene();
	static void updateGame();
	GraphicsEngine();
	~GraphicsEngine();
	static void initEngine(int argc, char **argv);
	static void addGameObject(GameObject *gameobject);
	static int grAccelerate();
	static int grDecelerate();
	static int grTurnLeft();
	static int grTurnRight();
};
