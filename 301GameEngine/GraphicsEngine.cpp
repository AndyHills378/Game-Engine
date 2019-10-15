#include "GraphicsEngine.h"
#include "GameEngine.h"
#include "sphere.h"

int GraphicsEngine::oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
int GraphicsEngine::newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
vector<GameObject*> GraphicsEngine::gameobjects;
int(*GraphicsEngine::EventReaction[4])();

glm::vec3 GraphicsEngine::cameraPos = glm::vec3(0.0f, 5.0f, 0.0f);
glm::vec3 GraphicsEngine::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float GraphicsEngine::yaw = 90.0f;
float GraphicsEngine::pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
float fov = 45.0f;
float GraphicsEngine::cameraSpeed = 0.5f;

void GraphicsEngine::MouseMove(int x, int y)
{
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	float xoffset = x - lastX;
	float yoffset = lastY - y;
	lastX = x;
	lastY = y;

	float sensitivity = 0.3f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	//forces mouse to stay in the window
	int win_w = glutGet(GLUT_WINDOW_WIDTH);
	int win_h = glutGet(GLUT_WINDOW_HEIGHT);
	if (x < 100 || x > win_w - 100)
	{
		lastX = win_w / 2;
		lastY = win_h / 2;
		glutWarpPointer(win_w / 2, win_h / 2);
	}
	else if (y < 100 || win_h - 100)
	{
		lastX = win_w / 2;
		lastY = win_h / 2;
		glutWarpPointer(win_w / 2, win_h / 2);
	}
}

GraphicsEngine::GraphicsEngine()
{
}


GraphicsEngine::~GraphicsEngine()
{
}
// Globals.
// Light properties.
static Light light0 =
{
	vec4(0.0, 0.0, 0.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 0.0, 0.0, 0.0)
};

// Global ambient.
static const vec4 globAmb = vec4(0.2, 0.2, 0.2, 1.0);

// Front and back material properties.
static const Material matFandB =
{
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(0.0, 0.0, 0.0, 1.0),
	50.0f
};

static Vertex fieldVertices[] =
{
	{vec4(100.0, 0.0, 100.0, 1.0), vec3(0.0, 1.0, 0.0), vec2(8.0, 0.0)},
	{vec4(100.0, 0.0, -100.0, 1.0), vec3(0.0, 1.0, 0.0), vec2(8.0, 8.0)},
	{vec4(-100.0, 0.0, 100.0, 1.0), vec3(0.0, 1.0, 0.0), vec2(0.0, 0.0)},
	{vec4(-100.0, 0.0, -100.0, 1.0), vec3(0.0, 1.0, 0.0), vec2(0.0, 8.0)}
};

static Vertex skyVertices[4] =
{
	{vec4(100.0, 0.0, -70.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(1.0, 0.0)},
	{vec4(100.0, 120.0, -70.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(1.0, 1.0)},
	{vec4(-100.0, 0.0, -70.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(0.0, 0.0)},
	{vec4(-100.0, 120.0, -70.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(0.0, 1.0)}
};

unsigned int GraphicsEngine::programId;


static BitMapFile *image[3];

static float theta = 0.0; // Angle of the sun with the ground.
float GraphicsEngine::linetheta = 90.0; 
static float alpha = 0.0; // Blending parameter.

void shaderCompileTest(GLuint shader)
{
	GLint result = GL_FALSE;
	int logLength; glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;
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

	// Create VAOs and VBOs... 
	glGenVertexArrays(4, vao);
	glGenBuffers(5, buffer);

	// Field vertex shader.
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fieldVertices), fieldVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(fieldVertices[0]), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(fieldVertices[0]), (void*)sizeof(fieldVertices[0].coords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(fieldVertices[0]), (void*)(sizeof(fieldVertices[0].coords) + sizeof(fieldVertices[0].normal)));
	glEnableVertexAttribArray(2);

	// Sky vertex shader
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), skyVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), 0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(skyVertices[0]), (void*)(sizeof(skyVertices[0].coords) + sizeof(skyVertices[0].normal)));
	glEnableVertexAttribArray(4);

	// Obtain projection matrix uniform location and set value.
	projMatLoc = glGetUniformLocation(GraphicsEngine::programId, "projMat");
	//projMat = projection();
	projMat = frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 1000.0);
	//projMat = glm::perspective(0.785398f, 1.0f, 1.0f, 10000.0f);
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMat));

	// Obtain modelview matrix, normal matrix, object and alpha uniform locations.
	modelMatLoc = glGetUniformLocation(GraphicsEngine::programId, "modelMat");
	viewMatLoc = glGetUniformLocation(GraphicsEngine::programId, "viewMat");
	normalMatLoc = glGetUniformLocation(GraphicsEngine::programId, "normalMat");
	objectLoc = glGetUniformLocation(GraphicsEngine::programId, "object");
	alphaLoc = glGetUniformLocation(GraphicsEngine::programId, "alpha");

	// Obtain light property uniform locations and set values.
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.ambCols"), 1, &light0.ambCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.difCols"), 1, &light0.difCols[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "light0.specCols"), 1, &light0.specCols[0]);
	light0coordsLoc = glGetUniformLocation(GraphicsEngine::programId, "light0.coords");

	// Obtain global ambient uniform location and set value.
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "globAmb"), 1, &globAmb[0]);

	// Obtain front material property uniform locations and set values.
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "matFandB.ambRefl"), 1, &matFandB.ambRefl[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "matFandB.difRefl"), 1, &matFandB.difRefl[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "matFandB.specRefl"), 1, &matFandB.specRefl[0]);
	glUniform4fv(glGetUniformLocation(GraphicsEngine::programId, "matFandB.emitCols"), 1, &matFandB.emitCols[0]);
	glUniform1f(glGetUniformLocation(GraphicsEngine::programId, "matFandB.shininess"), matFandB.shininess);

	// Load the images.
	image[0] = getbmp("Textures/grass.bmp");
	image[1] = getbmp("Textures/sky.bmp");
	image[2] = getbmp("Textures/nightSky.bmp");
	
	// Create texture ids.
	glGenTextures(3, texture);

	// Bind grass image.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	grassTexLoc = glGetUniformLocation(GraphicsEngine::programId, "grassTex");
	glUniform1i(grassTexLoc, 0);

	// Bind sky image.
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->sizeX, image[1]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	skyTexLoc = glGetUniformLocation(GraphicsEngine::programId, "skyTex");
	glUniform1i(skyTexLoc, 1);

	// Bind night sky image.
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->sizeX, image[2]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	nightSkyTexLoc = glGetUniformLocation(GraphicsEngine::programId, "nightSkyTex");
	glUniform1i(nightSkyTexLoc, 2);
}

// Drawing routine.
void GraphicsEngine::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Calculate and update light (sun) position.
	light0.coords.x = cos((PI / 180.0f)*theta);
	light0.coords.y = sin((PI / 180.0f)*theta);
	glUniform4fv(light0coordsLoc, 1, &light0.coords[0]);

	// Calculate and update blending parameter.
	if (theta <= 90.0f) alpha = theta / 90.0f;
	else alpha = (180.0f - theta) / 90.0f;
	glUniform1f(alphaLoc, alpha);

	// Calculate and update modelview matrix.
	viewMat = mat4(1.0);

	//read event queue
	for (int i = 0; i < GameEngine::EventQueue.size();i++)
	{
		for (int j = 0; j < GameEngine::EventQueue[i].mySubSystems.size(); j++)
		{
			if (GameEngine::EventQueue[i].mySubSystems[j] == SubSystemEnum::graphicsEngine)
			{
				EventReaction[(int)GameEngine::EventQueue[i].myType]();
				GameEngine::EventQueue[i].mySubSystems.erase(GameEngine::EventQueue[i].mySubSystems.begin()+j);
			}
		}
	}

	viewMat = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, value_ptr(viewMat));

	// Calculate and update normal matrix.
	normalMat = transpose(inverse(mat3(viewMat)));
	glUniformMatrix3fv(normalMatLoc, 1, GL_FALSE, value_ptr(normalMat));

	modelMat = mat4(1.0);
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));

	// Draw field.
	glUniform1ui(objectLoc, 0);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Draw sky.
	glUniform1ui(objectLoc, 1);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//right
	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(150, 0, 0));
	modelMat = glm::rotate(modelMat, 1.5708f, vec3(0, 1, 0));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, 1);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//left
	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(-150, 0, 0));
	modelMat = glm::rotate(modelMat, -1.5708f, vec3(0, 1, 0));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, 1);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//back
	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(0.0, 0.0, 150));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, 1);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++)
	{
		gameobjects[i]->drawScene();
	}

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
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
	//if (theta = 180.0f) theta = 0.0f;
	//if (specialKeys[GLUT_KEY_PAGE_UP])
	for (vector < GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		gameobjects[i]->update(deltaTime);
	}

	//Test collisions in a naive way for every pair of gameobjects (note calculations will explode when you increase the amount of gameobjects. Can you think of a better way?
	/*for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		for (std::vector<GameObject*>::size_type j = i + 1; j != gameobjects.size(); j++) {
			if (gameobjects[i]->collider != NULL) {
				if (gameobjects[i]->collider->collidesWith(gameobjects[j]->collider)) {
					gameobjects[i]->collides(gameobjects[j]->collider);
					gameobjects[j]->collides(gameobjects[i]->collider);
				}
			}
		}
	}*/
	glutPostRedisplay();
	//GameEngine::updateGame();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "----------------------------------" << endl;
	cout << "---------**  CONTROLS  **---------" << endl;
	cout << "     **WASD - change camera**     " << endl;
}

int GraphicsEngine::grAccelerate()
{
	cameraPos += cameraSpeed * cameraFront;
	return 0;
}

int GraphicsEngine::grDecelerate()
{
	cameraPos -= cameraSpeed * cameraFront;
	return 0;
}

int GraphicsEngine::grTurnLeft()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	return 0;
}

int GraphicsEngine::grTurnRight()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	return 0;
}

void GraphicsEngine::initEngine(int argc, char ** argv)
{
	printInteraction();
	

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("301CR Game Engine");
	glutDisplayFunc(drawScene);
	
	glutReshapeFunc(resize);
	glutPassiveMotionFunc(MouseMove);
	glewExperimental = GL_TRUE;
	glewInit();
	//glutTimerFunc(0, []() {GraphicsEngine::frameCounter(); }, 0);

	//creates Event Reaction array
	int(*p_grAccelerate)() = grAccelerate;
	int(*p_grDecelerate)() = grDecelerate;
	int(*p_grTurnLeft)() = grTurnLeft;
	int(*p_grTurnRight)() = grTurnRight;
	EventReaction[0] = p_grAccelerate;
	EventReaction[1] = p_grDecelerate;
	EventReaction[2] = p_grTurnLeft;
	EventReaction[3] = p_grTurnRight;

	setup();

	cout << "Graphics Engine loaded" << endl;
}

void GraphicsEngine::addGameObject(GameObject *gameobject) {
	gameobjects.push_back(gameobject);
	gameobject->modelMatLoc = modelMatLoc;
	gameobject->setupDrawing();
}



