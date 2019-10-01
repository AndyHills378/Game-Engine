#include "Sphere.h"
#include "SphereCollider.h"

static const Material sphereFandB =
{
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(0.663, 0.663, 0.663, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(0.0, 0.0, 0.0, 1.0),
	50.0f
};

static const Material sphereRed =
{
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(1.0, 0.0, 0.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0),
	50.0f
};

static const Material sphereBlue =
{
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0),
	50.0f
};

static const Material Jack =
{
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(1.0, 0.0, 1.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0),
	50.0f
};

void ballColour(Material color) {
	//codes for OpenGL lighting SPHERE MATS
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "sphereFandB.ambRefl"), 1, &color.ambRefl[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "sphereFandB.difRefl"), 1, &color.difRefl[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "sphereFandB.specRefl"), 1, &color.specRefl[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "sphereFandB.emitCols"), 1, &color.emitCols[0]);
	glUniform1f(glGetUniformLocation(GameEngine::programId, "sphereFandB.shininess"), color.shininess);
}

Sphere::Sphere(vec3 position, float radii, unsigned int *sphereIndices, VertexWithNormal *sphereVerticesNor, int id) : GameObject(position)
{
	this->position = position;
	stacks = 10;
	slices = 10;
	radius = radii;
	Sphere::collider = new SphereCollider(&this->position, radius);
	//Velocity = MOVE_SPEED;
	mass = radius + 1;
	sphereId = id;

	this->sphereVerticesNor = (VertexWithNormal *)malloc(sizeof(VertexWithNormal) * 121);
	this->sphereIndices = (unsigned int *)malloc(sizeof(unsigned int) * 660);
	CreateSpherewithNormal();
}

Sphere::~Sphere()
{
	delete Sphere::collider;
	Sphere::collider = NULL;
	free(sphereVerticesNor);
	free(sphereIndices);
}

void Sphere::setupDrawing()
{
	glGenVertexArrays(2, vao);
	glGenBuffers(3, buffer);

	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexWithNormal) * 121, this->sphereVerticesNor, GL_STATIC_DRAW);  ///please note the change
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 660, sphereIndices, GL_STATIC_DRAW); ///please note the change
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), 0);  //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), (GLvoid*)sizeof(sphereVerticesNor[0].coords));
	glEnableVertexAttribArray(7);
}

void Sphere::drawScene()
{
	if (sphereId % 2 != 0) ballColour(sphereBlue);
	if (sphereId % 2 == 0) ballColour(sphereRed);
	if (sphereId == 0) ballColour(Jack);
	mat4 modelMat = mat4(1.0);
	modelMat = translate(modelMat, this->position);
	modelMat = rotate(modelMat, -glm::radians(Acceleration / 2), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));  //send to the shader
	glUniform1ui(glGetUniformLocation(GameEngine::programId, "object"), 3);
	glBindVertexArray(vao[0]);
	glDrawElements(GL_TRIANGLE_STRIP, 660, GL_UNSIGNED_INT, 0);  ///use index array to control triangle drawing
}

void Sphere::update(int deltaTime)
{
	heading.y = 0;
	if (sphereId == GameEngine::sphereToDraw)
	{
		NewVelocity = Velocity + (Acceleration * heading) * (deltaTime / 1000.0f);
		position = position + NewVelocity * (deltaTime / 1000.0f);

		cout << StoredAcceleration << endl;

		if (specialKeys[GLUT_KEY_UP])
		{
			StoredAcceleration += MOVE_SPEED;
		}
		else if (specialKeys[GLUT_KEY_DOWN]) {
			hasMoved = true;
			heading = GameEngine::cameraFront;
			Acceleration = StoredAcceleration;
		}
		else
		{
			if (Acceleration > 0) {
				Acceleration = Acceleration - MOVE_SPEED;
			}
			if (Acceleration < 0) {
				Acceleration = Acceleration + MOVE_SPEED;
			}
			if (Acceleration > -10.0f && Acceleration < 10.0f)
			{
				Acceleration = 0.0f;
				if (hasMoved) GameEngine::sphereToDraw++;
			}
		}
	}
}

void Sphere::CreateSpherewithNormal(void)
{
	int count;
	count = 0;
	for (int i = 0; i <= stacks; ++i) {

		GLfloat V = i / (float)stacks;
		GLfloat phi = V * glm::pi <float>();

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			GLfloat U = j / (float)slices;
			GLfloat theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			GLfloat x = cosf(theta) * sinf(phi);
			GLfloat y = cosf(phi);
			GLfloat z = sinf(theta) * sinf(phi);

			sphereVerticesNor[count].coords = vec4(x * radius, y * radius, z * radius, 1.0);
			sphereVerticesNor[count].normals = vec3(x, y, z); ///Sphere normals

			count++;
		}
	}

	count = 0;
	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		sphereIndices[count] = i;
		count++;
		sphereIndices[count] = i + slices + 1;
		count++;
		sphereIndices[count] = i + slices;
		count++;

		sphereIndices[count] = i + slices + 1;
		count++;
		sphereIndices[count] = i;
		count++;
		sphereIndices[count] = i + 1;
		count++;
	}

	count = 0;
}

VertexWithNormal * Sphere::GetVerData(int &verNum)
{
	verNum = 121;
	return sphereVerticesNor;
}

unsigned int * Sphere::GetTriData(int &triNum)
{
	triNum = 660;
	return sphereIndices;
}

void Sphere::collides(Collider* other) 
{
	if (debugMode) 
	{
		std::cout << "Sphere collides!" << std::endl;
	}
}