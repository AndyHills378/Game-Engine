#pragma once
#include "Header.h"
#include "GameEngine.h"

struct ClientData {
	int packetType = 0;
	int clientIndex;
};

struct ClientPacket {
	int clientIndex;
	vec3 position;
	vec3 heading;
};


class NetworkEngine
{
public:
	static int(*EventReaction[4])();
	static int clientCount;
	NetworkEngine();
	~NetworkEngine();
	static void initEngine();
	static int nwAccelerate();
	static int nwDecelerate();
	static int nwTurnLeft();
	static int nwTurnRight();
	static void updateEngine(int deltaTime);
};

