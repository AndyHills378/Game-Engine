#pragma once
class Mustang
{
public:
	Mustang();
	~Mustang();
	void setupDrawing();
	void drawScene(); ///<Function to perform this object's part of the redraw work. Can override in inherited classes.

							  /* Every GameObject must implement the following pure virtual function or otherwise cause a compile error.*/
	//virtual void start()= 0 ; ///<Pure virtual start function, run once when the engine starts.  Must override in inherited classes.
	void update(int deltaTime); ///<Pure virtual update function, run periodicly to update the game state.  Must override in inherited classes.

	//void collides(Collider* other); ///<Virtual function to notify this game object that a collision has happened can be overridden (optional).
};

