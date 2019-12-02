#include "NetworkEngine.h"


ENetAddress address;
ENetEvent enetEvent;
ENetHost* client;
ENetPeer* peer;
ENetPacket* dataPacket;
int NetworkEngine::clientCount = 0;

ClientData* clientData;
ClientPacket* clientPacket;

int* packetType;
int clientIndex = -1;

int(*NetworkEngine::EventReaction[4])();

NetworkEngine::NetworkEngine()
{
}

NetworkEngine::~NetworkEngine()
{
}

void NetworkEngine::initEngine()
{
	if (enet_initialize() != 0)
	{
		cout << "you done goofed..." << endl;
	}

	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		cout << "Client failed to initialise!" << "\n\n";
	}

	enet_address_set_host(&address, "localhost");
	address.port = 1234;

	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) {
		cout << "No available peers for initializing an ENet connection.\n";
	}

	clientData = new ClientData;
	clientPacket = new ClientPacket;
	int* packetType = new int;

	*packetType = -1;

	int(*p_pxAccelerate)() = nwAccelerate;
	int(*p_pxDecelerate)() = nwDecelerate;
	int(*p_pxTurnLeft)() = nwTurnLeft;
	int(*p_pxTurnRight)() = nwTurnRight;
	EventReaction[0] = p_pxAccelerate;
	EventReaction[1] = p_pxDecelerate;
	EventReaction[2] = p_pxTurnLeft;
	EventReaction[3] = p_pxTurnRight;

	cout << "Network Engine initialised" << endl;
}

int NetworkEngine::nwAccelerate()
{
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow)
		{
			clientPacket->position = GameEngine::gameobjects[i]->position;
			clientPacket->heading = GameEngine::gameobjects[i]->heading;
		}
	}
	return 0;
}
int NetworkEngine::nwDecelerate()
{
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow)
		{
			clientPacket->position = GameEngine::gameobjects[i]->position;
			clientPacket->heading = GameEngine::gameobjects[i]->heading;
		}
	}
	return 0;
}
int NetworkEngine::nwTurnLeft()
{
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow)
		{
			clientPacket->position = GameEngine::gameobjects[i]->position;
			clientPacket->heading = GameEngine::gameobjects[i]->heading;
		}
	}
	return 0;
}
int NetworkEngine::nwTurnRight()
{
	for (int i = 0; i < GameEngine::gameobjects.size(); i++)
	{
		if (GameEngine::gameobjects[i]->objectToFollow)
		{
			clientPacket->position = GameEngine::gameobjects[i]->position;
			clientPacket->heading = GameEngine::gameobjects[i]->heading;
		}
	}
	return 0;
}

void NetworkEngine::updateEngine(int deltaTime)
{
	while (enet_host_service(client, &enetEvent, 0) > 0)
	{
		switch (enetEvent.type)
		{
			case ENET_EVENT_TYPE_RECEIVE:
			{
				//cout << "packet received" << endl;
			}
			for (int i = 0; i < GameEngine::EventQueue.size(); i++)
			{
				for (int j = 0; j < GameEngine::EventQueue[i].mySubSystems.size(); j++)
				{
					if (GameEngine::EventQueue[i].mySubSystems[j] == SubSystemEnum::networkEngine)
					{
						EventReaction[(int)GameEngine::EventQueue[i].myType]();
						GameEngine::EventQueue[i].mySubSystems.erase(GameEngine::EventQueue[i].mySubSystems.begin() + j);
						clientPacket->clientIndex = clientIndex;
						dataPacket = enet_packet_create(clientPacket, sizeof(ClientPacket), ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(peer, 0, dataPacket);
					}
				}
			}
		}
	}
}