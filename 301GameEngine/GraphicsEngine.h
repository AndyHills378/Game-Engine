#pragma once
#include "Header.h"
#include "shader.h"
#include "GameEngine.h"
#include "Camera.h"
#include "vertex.h"
#include "Mesh.h"
#include "Texture.h"

class GraphicsEngine
{
public:

	static unsigned int vertexShaderId, fragmentShaderId, programId;
	static int(*EventReaction[4])();
	GraphicsEngine();
	~GraphicsEngine();
	static int grAccelerate();
	static int grDecelerate();
	static int grTurnLeft();
	static int grTurnRight();
	static void setup(void);
	static void drawScene();
	static void updateGame();
	static void printInteraction(void);
	static void initEngine(int argc, char** argv);
	static void startGame();
	
};

