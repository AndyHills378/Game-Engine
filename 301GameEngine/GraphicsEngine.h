#pragma once
#include "Header.h"
#include "shader.h"
#include "GameEngine.h"
#include "Camera.h"
#include "vertex.h"
#include "Mesh.h"
#include "Texture.h"
#include "TextReader.h"
#include "SubSystemSuper.h"
#include "Settings.h"

class GraphicsEngine : public SubSystemSuper
{
private:
	static int oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
	static int newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
public:

	static unsigned int vertexShaderId, fragmentShaderId, programId;
	static int(*EventReaction[4])();
	GraphicsEngine();
	~GraphicsEngine();
	static void setupTextures();
	static void setup(void);
	static void drawScene();
	static void updateGame();
	static void printInteraction(void);
	static void initEngine(int argc, char** argv);
	static void startGame();
	
};

