#include "GraphicsEngine.h"

unsigned int GraphicsEngine::programId, GraphicsEngine::fragmentShaderId, GraphicsEngine::vertexShaderId;
Camera* camera;
int(*GraphicsEngine::EventReaction[4])();
static float theta = 0.0; // Angle of the sun with the ground.
//float GameEngine::linetheta = 90.0;
static float alpha = 0.0; // Blending parameter.
float cX = 0, cY = 10.0f, cZ = 15.0f;
int GraphicsEngine::oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
int GraphicsEngine::newTimeSinceStart; ///<The time since the start of the game for delta time calculation.

std::vector<Mesh*> newMesh;
std::vector<Mesh*> cubeMap;
std::vector<Texture*> newTexture;
TextReader model;

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
	
}

void shaderCompileTest(GLuint shader)
{
	GLint result = GL_FALSE;
	int logLength; glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;
}

void GraphicsEngine::setupTextures()
{
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef t = getGlobal(F, "directories");
	std::string textureDir = t["textures"].cast<std::string>();

	t = getGlobal(F, "environment");
	std::string catTexture = t["texture"].cast<std::string>();

	std::string testTextureString = textureDir + catTexture;
	cout << '"' + testTextureString + '"' << endl;


	Texture* testTexture = new Texture(testTextureString, 2);
	newTexture.push_back(testTexture);
	/*if (!testTexture.loadFromFile(textureDir + catTexture))
	{
		std::cout << "Texture did not load!" << "\n";
	}

	texturedShape.setTexture(&testTexture);*/
}

// Initialization routine.
void GraphicsEngine::setup()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Create shader program executable.
	vertexShaderId = setShader((char*)"vertex", (char*)"vertexShader.glsl");
	fragmentShaderId = setShader((char*)"fragment", (char*)"fragmentShader.glsl");
	GraphicsEngine::programId = glCreateProgram();
	glAttachShader(GraphicsEngine::programId, vertexShaderId);
	glAttachShader(GraphicsEngine::programId, fragmentShaderId);
	glLinkProgram(GraphicsEngine::programId);
	glUseProgram(GraphicsEngine::programId);

	std::cout << "::: VERTEX SHADER :::" << std::endl;
	shaderCompileTest(vertexShaderId);
	std::cout << "::: FRAGMENT SHADER :::" << std::endl;
	shaderCompileTest(fragmentShaderId);

	// Obtain light property uniform locations and set values.
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.ambCols"), 1, &light0.ambCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.difCols"), 1, &light0.difCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.specCols"), 1, &light0.specCols[0]);
	light0coordsLoc = glGetUniformLocation(GraphicsEngine::programId, "light0.coords");

	//setup skybox
	Texture* back = new Texture("Textures/back.bmp", 0);
	Texture* bottom = new Texture("Textures/bottom.bmp", 0);
	Texture* front = new Texture("Textures/front.bmp", 0);
	Texture* left = new Texture("Textures/left.bmp", 0);
	Texture* right = new Texture("Textures/right.bmp", 0);
	Texture* top = new Texture("Textures/top.bmp", 0);
	newTexture.push_back(back);
	newTexture.push_back(bottom);
	newTexture.push_back(front);
	newTexture.push_back(left);
	newTexture.push_back(right);
	newTexture.push_back(top);

	Texture* asphalt = new Texture("Textures/asphalt.bmp", 1);
	newTexture.push_back(asphalt);
	/*Texture* sand = new Texture("Textures/sand.bmp", 2);
	newTexture.push_back(sand);*/

	//Texture* cubemap = new Texture(faces);
	cubeMap.push_back(new Mesh(skyVertices, vec3(0.0f, 500.0f, 500.0f), -1.5708f, vec3(1.0f, 0.0f, 0.0f), bottom->texture));
	cubeMap.push_back(new Mesh(skyVertices, vec3(0.0f, 500.0f, -500.0f), 1.5708f, vec3(1.0f, 0.0f, 0.0f), top->texture));
	cubeMap.push_back(new Mesh(skyVertices, vec3(0.0f), 0.0f, vec3(0.0f,1.0f,0.0f), left->texture));
	cubeMap.push_back(new Mesh(skyVertices, vec3(0.0f), 1.5708f, vec3(0.0f, 1.0f, 0.0f), back->texture));
	cubeMap.push_back(new Mesh(skyVertices, vec3(0.0f), -1.5708f, vec3(0.0f, 1.0f, 0.0f), front->texture));
	cubeMap.push_back(new Mesh(skyVertices, vec3(0.0f), 3.14159f, vec3(0.0f, 1.0f, 0.0f), right->texture));

	camera = new Camera();
	camera->setup();

	glm::mat4 modelMat(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(GraphicsEngine::programId, "modelMat"), 1, GL_FALSE, value_ptr(modelMat));
}

void GraphicsEngine::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate and update light (sun) position.
	light0.coords.x = cos((PI / 180.0f) * theta);
	light0.coords.y = sin((PI / 180.0f) * theta);
	glUniform4fv(light0coordsLoc, 1, &light0.coords[0]);

	// Calculate and update blending parameter.
	if (theta <= 90.0f) alpha = theta / 90.0f;
	else alpha = (180.0f - theta) / 90.0f;
	glUniform1f(alphaLoc, alpha);

	for (int i = 0; i < cubeMap.size(); i++)
	{
		glDepthMask(GL_FALSE);
		glUniform1ui(glGetUniformLocation(GraphicsEngine::programId, "tex"), cubeMap[i]->meshID);
		glBindVertexArray(cubeMap[i]->VAO);
		//glBindTexture(GL_TEXTURE_2D, cubeMap[i]->meshID);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		cubeMap[i]->drawMesh();
		glDepthMask(GL_TRUE);
	}
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		GameEngine::gameobjects[i]->drawObject();
	}
	glutSwapBuffers();
}


void GraphicsEngine::updateGame()
{
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTimeSinceStart - oldTimeSinceStart;

	//If the last frame was rendered less than 1 ms ago, the deltaTime will be 0 ms. This causes problems in calculations, so sleep for 1ms to adjust.
	if (deltaTime == 0) {
		Sleep(1);
		newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = newTimeSinceStart - oldTimeSinceStart;
	}
	if (SubSystemSuper::debugMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	theta = theta + 1.0f * deltaTime / 100.0f;
	if (theta >= 180.0) theta -= 180.0f;

	//cout << theta << endl;
	
	//read event queue
	for (int i = 0; i < GameEngine::EventQueue.size();i++)
	{
		for (int j = 0; j < GameEngine::EventQueue[i].mySubSystems.size(); j++)
		{
			if (GameEngine::EventQueue[i].mySubSystems[j] == SubSystemEnum::graphicsEngine)
			{
				EventReaction[(int)GameEngine::EventQueue[i].myType]();
				GameEngine::EventQueue[i].mySubSystems.erase(GameEngine::EventQueue[i].mySubSystems.begin() + j);
			}
		}
	}
	camera->update(deltaTime);
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void GraphicsEngine::printInteraction(void)
{
	std::cout << "----------------------------------" << std::endl;
	std::cout << "---------**  CONTROLS  **---------" << std::endl;
	std::cout << "     **WASD - change camera**     " << std::endl;
	//std::cout << " t - debugmode " << std::endl;
	std::cout << " Arrow keys - Move " << std::endl;
	//std::cout << " c - cameramode " << std::endl;
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
}

void GraphicsEngine::initEngine(int argc, char** argv)
{
	printInteraction();
	//glutInit(&argc, argv);

	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef t = getGlobal(F, "window");
	LuaRef title = t["title"];
	LuaRef w = t["width"];
	LuaRef h = t["height"];

	std::string titleString = title.cast<std::string>();
	int width = w.cast<int>();
	int height = h.cast<int>();

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(500, 100);
	glutCreateWindow(title);
	glutDisplayFunc(drawScene);
	glutIdleFunc([]() {GameEngine::updateGame(); }); //idle function
	glutReshapeFunc(resize);
	glutPassiveMotionFunc(camera->setMouseMove);

	//creates Event Reaction array
	int(*p_grAccelerate)() = camera->grAccelerate;
	int(*p_grDecelerate)() = camera->grDecelerate;
	int(*p_grTurnLeft)() = camera->grTurnLeft;
	int(*p_grTurnRight)() = camera->grTurnRight;
	EventReaction[0] = p_grAccelerate;
	EventReaction[1] = p_grDecelerate;
	EventReaction[2] = p_grTurnLeft;
	EventReaction[3] = p_grTurnRight;

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	std::cout << "GraphicsEngine initiated" << endl;
}

void GraphicsEngine::startGame()
{
	glutMainLoop();
}
