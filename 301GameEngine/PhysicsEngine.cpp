#include "PhysicsEngine.h"

int(*PhysicsEngine::EventReaction[4])();
int PhysicsEngine::oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
int PhysicsEngine::newTimeSinceStart; ///<The time since the start of the game for delta time calculation.

rp3d::DynamicsWorld* world;
rp3d::RigidBody* body;

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
	// Destroy the rigid body
	world->destroyRigidBody(body);
}

void PhysicsEngine::initEngine()
{
	// Gravity vector
	rp3d::Vector3 gravity(0.0f, -9.81f, 0.0f);
	// Create the dynamics world
	rp3d::DynamicsWorld world(gravity);

	///only edit if needed, increasing numbers slows down compute time
	// Change the number of iterations of the velocity solver
	world.setNbIterationsVelocitySolver(15);
	// Change the number of iterations of the position solver
	world.setNbIterationsPositionSolver(8);

	// Initial position and orientation of the rigid body
	rp3d::Vector3 initPosition(0.0, 3.0, 0.0);
	rp3d::Quaternion initOrientation = rp3d::Quaternion ::
		identity();
	rp3d::Transform transform(initPosition, initOrientation);

	// Create a rigid body in the world
	body = world.createRigidBody(transform);	body->enableGravity(false);
	// Half extents of the box in the x, y and z directions
	const rp3d::Vector3 halfExtents(2.0, 3.0, 5.0);
	// Create the box shape
	const rp3d::BoxShape boxShape(halfExtents);	// Create the sphere shape with a radius of 2m
	const rp3d::SphereShape sphereShape(2.0);

	cout << "Physics Engine loaded" << endl;
	/*int(*p_grAccelerate)() = camera->grAccelerate;
	int(*p_grDecelerate)() = camera->grDecelerate;
	int(*p_grTurnLeft)() = camera->grTurnLeft;
	int(*p_grTurnRight)() = camera->grTurnRight;
	EventReaction[0] = p_grAccelerate;
	EventReaction[1] = p_grDecelerate;
	EventReaction[2] = p_grTurnLeft;
	EventReaction[3] = p_grTurnRight;*/
}

void PhysicsEngine::updateEngine()
{
	//read event queue
	for (int i = 0; i < GameEngine::EventQueue.size(); i++)
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
}
