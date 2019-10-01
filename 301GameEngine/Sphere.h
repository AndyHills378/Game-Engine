#ifndef SPHERE
#define SPHERE

#include <fstream>

#include "vertex.h"
#include "GameObject.h"
#include "SphereCollider.h"
#include "GraphicsEngine.h"

#define MOVE_SPEED 2.0

class Sphere : public GameObject
{
private:
	int sizeX;
	int sizeY;
	VertexWithNormal *sphereVerticesNor;  //121
	unsigned int *sphereIndices; //660

	int stacks; //10
	int slices; //10
	float radius;	
	glm::vec3 NewVelocity;
	float StoredAcceleration = 0;
	glm::vec3 Velocity;
	float Acceleration;
	float Deceleration;
	int mass;
	int sphereId;
	bool hasMoved;
	void CreateSpherewithNormal();
public:
	glm::vec3 heading;
	unsigned int vao[2];
	unsigned int buffer[3];
	static enum object { SPHERE1, LINE}; /// VAO ids.
	static enum buffer { SPHERE_VERTICES, SPHERE_NORMALS, LINE_VERTICES}; // VBO ids.
	Sphere(vec3 position, float radii, unsigned int * sphereIndices, VertexWithNormal * sphereVerticesNor, int id);
	~Sphere();
	void setupDrawing();
	void drawScene();
	void update(int deltaTime);
	VertexWithNormal * GetVerData(int &);
	unsigned int * GetTriData(int &);
	void collides(Collider * other);
};

#endif