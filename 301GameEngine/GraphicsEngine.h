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
#include "CubeMap.h"

class GraphicsEngine : public SubSystemSuper
{
public:
	static int cameraMode;
	static unsigned int vertexShaderId, fragmentShaderId, programId;
	static int(*EventReaction[5])();
	GraphicsEngine();
	~GraphicsEngine();
	static void setupTextures();
	static void setup(void);
	static void drawScene();
	static void updateGame(int deltaTime);
	static void printInteraction(void);
	static void initEngine(int argc, char** argv);
	static void startGame();
	
};

