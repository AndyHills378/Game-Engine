#pragma once
#include "Header.h"
#include "GraphicsEngine.h"

class Camera
{
public:
	static glm::vec3 cameraPos, cameraFront;
	static float yaw, pitch, cameraSpeed;
	Camera();
	~Camera();
	void setup();
	void update(int deltaTime);
	static void setMouseMove(int x, int y);
	static int grAccelerate();
	static int grDecelerate();
	static int grTurnLeft();
	static int grTurnRight();
	static int cameraSwitch();
};

