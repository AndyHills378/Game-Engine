#include "GraphicsEngine.h"

unsigned int GraphicsEngine::programId, GraphicsEngine::fragmentShaderId, GraphicsEngine::vertexShaderId;
Camera* camera;
int(*GraphicsEngine::EventReaction[4])();

std::vector<Mesh*> newMesh;
std::vector<Texture*> newTexture;
TextReader model;

static vector<Vertex> fieldvertices =
{
	{vec3(100.0, 0.0, 100.0), vec3(0.0, 1.0, 0.0), vec2(8.0, 0.0)},
	{vec3(100.0, 0.0, -100.0), vec3(0.0, 1.0, 0.0), vec2(8.0, 8.0)},
	{vec3(-100.0, 0.0, 100.0), vec3(0.0, 1.0, 0.0), vec2(0.0, 0.0)},
	{vec3(-100.0, 0.0, -100.0), vec3(0.0, 1.0, 0.0), vec2(0.0, 8.0)}
};

static vector<Vertex> skyVertices =
{
	{vec3(100.0, 0.0, -100.0), vec3(0.0, 0.0, 1.0), vec2(1.0, 0.0)},
	{vec3(100.0, 120.0, -100.0), vec3(0.0, 0.0, 1.0), vec2(1.0, 1.0)},
	{vec3(-100.0, 0.0, -100.0), vec3(0.0, 0.0, 1.0), vec2(0.0, 0.0)},
	{vec3(-100.0, 120.0, -100.0), vec3(0.0, 0.0, 1.0), vec2(0.0, 1.0)}
};

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

// Initialization routine.
void GraphicsEngine::setup()
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
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

	//setup skybox
	Texture* grass = new Texture("Textures/grass.bmp", 0);
	newTexture.push_back(grass);
	Texture* sky = new Texture("Textures/SkySeamlessTexture.bmp", 1);
	newTexture.push_back(sky);
	newMesh.push_back(new Mesh(fieldvertices, vec3(0.0f), 0.0f, grass->texture));
	//newMesh.push_back(new Mesh(fieldvertices, vec3(0.0f, 120.0f, 0.0f), 0.0f));
	
	newMesh.push_back(new Mesh(skyVertices, vec3(0.0f), 0.0f, sky->texture));
	newMesh.push_back(new Mesh(skyVertices, vec3(0.0f), 1.5708f, sky->texture));
	newMesh.push_back(new Mesh(skyVertices, vec3(0.0f), -1.5708f, sky->texture));
	newMesh.push_back(new Mesh(skyVertices, vec3(0.0f), 3.14159f, sky->texture));
	
	newMesh.push_back(new Mesh((char*)"TrackTri.obj", sky->texture, glm::vec3(0.0f, 0.0f, 0.0f), vec3(50.0f, 1.0f, 50.0f)));

	camera = new Camera();
	camera->setup();

	glm::mat4 modelMat(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(GraphicsEngine::programId, "modelMat"), 1, GL_FALSE, value_ptr(modelMat));
}

void GraphicsEngine::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < newMesh.size(); i++)
	{
		glUniform1ui(glGetUniformLocation(GraphicsEngine::programId, "tex"), newMesh[i]->meshID);
		glBindTexture(GL_TEXTURE_2D, newMesh[i]->meshID);
		//glBindTexture(glGetUniformLocation(GraphicsEngine::programId, "tex"), newTexture[i]->texture);
		newMesh[i]->drawMesh();
	}

	glutSwapBuffers();
}

void GraphicsEngine::updateGame()
{
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
	camera->update();
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

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Graphics Engine");
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
