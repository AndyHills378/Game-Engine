#pragma once
#include "Header.h"
#include "GameEngine.h"

struct ClientConnection {
	int packetType;
	int clientIndex;
};

struct ClientData {
	vec3 position[2];
	vec3 heading[2];
};

struct ClientPacket {
	int clientIndex;
	vec3 position[2];
	vec3 heading[2];
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

