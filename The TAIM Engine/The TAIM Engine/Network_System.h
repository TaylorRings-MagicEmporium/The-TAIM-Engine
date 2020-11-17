#pragma once
#include <enet/enet.h>
#include <iostream>
#include "SubSystem.h"

// a defined packet structure that holds the position and rotation value of an object
struct TransformPacket {
	float x, y, z;
	float qx, qy, qz, qw;
};

// a specific packet that (when recieved) contains all of the clients transforms
struct PhysicsData {
	int packetType = 1;
	TransformPacket transforms[2];
};

// a specific packet that (when recieved) tells the NS that it is connected to a server.
struct ClientData {
	int packetType = 0;
	int clientIndex;
};

// a specific packet that is sent to the server that contains the transform and the client index
struct ClientPacket {
	int clientIndex;
	TransformPacket transform;
};

//The Network system is responsible with sending and recieving packages, and finally put them into
//an event that the rest of the engine can use. The Network system will act similar to the Event system.
class Network_System : public SubSystem
{
public:
	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer;
	ENetEvent enetEvent;

	Entity_System* ES;

	PhysicsData* serverData = new PhysicsData;
	ClientData* clientData = new ClientData;
	int* packetType = new int;

	ClientPacket* clientPacket = new ClientPacket;
	ENetPacket* dataPacket;

	int clientIndex = -1;

	//serverConnect is needed for safety. packets are only sent if there is a server connected.
	// without this, errors including corruption  of data and backlog of events can occur
	bool serverConnect = false;

	Network_System();
	~Network_System();

	void Startup();
	void Update();
	void LateUpdate();
	void ShutDown();


};

