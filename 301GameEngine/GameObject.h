#pragma once

#include "shader.h"
#include "light.h"
#include "material.h"
#include "getbmp.h"
#include "vertex.h"
#include "Collider.h"
#include "Header.h"

struct Colour {
	float r, g, b;
};

class GameObject {
protected:
	unsigned int base;  ///<Base index for display lists.
public:
	

	unsigned int modelMatLoc;

	static bool DrawColliders;
	Collider* collider = NULL;  ///<Pointer to a collider for the game object. Initially NULL to indicate that we do not want to calculate collisions.
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);  ///<Position of the gameobject.
	glm::vec3 heading = glm::vec3(0.0, 0.0, -1.0);  ///<Heading (direction) the gameobject is facing.

	GameObject(glm::vec3 pos);
	~GameObject(); ///<Standard destructor.

	virtual void setupDrawing();
	virtual void drawScene(); ///<Function to perform this object's part of the redraw work. Can override in inherited classes.

							  /* Every GameObject must implement the following pure virtual function or otherwise cause a compile error.*/
	//virtual void start()= 0 ; ///<Pure virtual start function, run once when the engine starts.  Must override in inherited classes.
	virtual void update(int deltaTime) = 0; ///<Pure virtual update function, run periodicly to update the game state.  Must override in inherited classes.

	virtual void collides(Collider* other); ///<Virtual function to notify this game object that a collision has happened can be overridden (optional).
};