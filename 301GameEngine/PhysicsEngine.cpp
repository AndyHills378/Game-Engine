#include "PhysicsEngine.h"

int(*PhysicsEngine::EventReaction[4])();
int PhysicsEngine::oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta time calculation.
int PhysicsEngine::newTimeSinceStart; ///<The time since the start of the game for delta time calculation.
float turningSpeed;
float rotSpeed = 90;
float PhysicsEngine::Acceleration;
glm::vec3 PhysicsEngine::NewVelocity;
glm::vec3 PhysicsEngine::Velocity = vec3(0,0,0);

int PhysicsEngine::pxAccelerate()
{
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow) { Acceleration += MOVE_SPEED; }
	}
	return 0;
}

int PhysicsEngine::pxDecelerate()
{
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow) { Acceleration -= MOVE_SPEED; }
	}
	return 0;
}

int PhysicsEngine::pxTurnLeft()
{
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow) { GameEngine::gameobjects[i]->rotate += turningSpeed; }
	} 
	return 0;
}

int PhysicsEngine::pxTurnRight()
{
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow) { GameEngine::gameobjects[i]->rotate -= turningSpeed; }
	}
	return 0;
}

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::customizeSceneDesc(PxSceneDesc& sceneDesc)
{
	sceneDesc.gravity = PxVec3(0, -9.81, 0);
	//sceneDesc.filterShader = filter;
	//sceneDesc.simulationEventCallback = this;
	sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
	sceneDesc.flags |= PxSceneFlag::eREQUIRE_RW_LOCK;
}

void PhysicsEngine::initEngine()
{
	/*static UserErrorCallback gUserErrorCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;
	//static PxDefaultSimulationFilterShader gDefaultFilterShader;

	PxFoundation* mFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gDefaultAllocatorCallback,
		gUserErrorCallback);
	if (!mFoundation) {
		cout << "PxCreateFoundation failed!" << endl;
	}

	bool recordMemoryAllocations = false;
	
	PxPvd* mPvd = PxCreatePvd(*mFoundation);
	if (!mPvd) { cout << "PxPvd failed" << endl; } //profile zone manager

	PxPhysics* mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(), recordMemoryAllocations, mPvd); //top-level physics
	if (!mPhysics){ cout << "PxCreatePhysics failed!" << endl;}

	//PxCooking* mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, PxCookingParams(0, 1, 0));
	//if (!mCooking) { cout << "PxCreateCooking failed!" << endl; }

	PxScene* mScene;
	PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	customizeSceneDesc(sceneDesc);
	mScene = mPhysics->createScene(sceneDesc);
	if (!mScene) { cout << "createScene failed" << endl; }

	PxMaterial* mMaterial = mPhysics->createMaterial((PxReal)0.5f, (PxReal)0.5f, (PxReal)0.5f); //static friction, dynamic friction, restitution
	if (!mMaterial) { cout << "createMaterial failed" << endl; }

	PxRigidActor* aSphereActor = mPhysics->createRigidDynamic(PxTransform(0.f, 1.f, 0.f));
	PxShape* aSphereShape = aSphereActor->createShape(PxSphereGeometry(1.0f), *mMaterial);
	/*PxReal density;
	density = 10.0f;
	PxVec3 position(0, 50, 0);*/



	//if (!aSphereActor) { cout << "Unable to create sphere actor" << endl; }
	//PxRigidBodyExt::updateMassAndInertia(*aSphereActor, density);
	//mScene->addActor(*aSphereActor);

	//PxRigidStatic* plane = PxCreatePlane(*mPhysics, PxPlane(PxVec3(0.0f, 1.0f, 0.0f), 0), *mMaterial);
	//mScene->addActor(*plane);

	cout << "Physics Engine loaded" << endl;
	int(*p_pxAccelerate)() = pxAccelerate;
	int(*p_pxDecelerate)() = pxDecelerate;
	int(*p_pxTurnLeft)() = pxTurnLeft;
	int(*p_pxTurnRight)() = pxTurnRight;
	EventReaction[0] = p_pxAccelerate;
	EventReaction[1] = p_pxDecelerate;
	EventReaction[2] = p_pxTurnLeft;
	EventReaction[3] = p_pxTurnRight;
}

void PhysicsEngine::updateEngine(int deltaTime)
{
	turningSpeed = TURNING_SPEED * (deltaTime / 1000.0); //turning speed (degrees/sec) * deltaTime in sec = turning speed over delta time
	//read event queue
	for (int i = 0; i < GameEngine::EventQueue.size(); i++)
	{
		for (int j = 0; j < GameEngine::EventQueue[i].mySubSystems.size(); j++)
		{
			if (GameEngine::EventQueue[i].mySubSystems[j] == SubSystemEnum::physicsEngine)
			{
				EventReaction[(int)GameEngine::EventQueue[i].myType]();
				GameEngine::EventQueue[i].mySubSystems.erase(GameEngine::EventQueue[i].mySubSystems.begin() + j);
			}
		}
	}

	/*if (Acceleration > -50.0f && Acceleration < 50.0f)
	{
		Acceleration = 0.0f;
	}*/
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow) {
			GameEngine::gameobjects[i]->heading.y = 0;
			NewVelocity = Velocity + (Acceleration * GameEngine::gameobjects[i]->heading) * (deltaTime / 1000.0f);
			GameEngine::gameobjects[i]->position = GameEngine::gameobjects[i]->position + NewVelocity * (deltaTime / 1000.0f);
			GameEngine::gameobjects[i]->heading = glm::rotate(GameEngine::gameobjects[i]->startHeading, GameEngine::gameobjects[i]->rotate, GameEngine::gameobjects[i]->rotateVec);
		}
	}
}
