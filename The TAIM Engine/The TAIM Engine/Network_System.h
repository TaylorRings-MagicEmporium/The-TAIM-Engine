#pragma once

#include <enet/enet.h>
#include <iostream>
#include "SubSystem.h"
#include "Entity_System.h"
#include "Profiling_System.h"

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
	bool FirstClient;
	int CurrentLevel;
};

// a specific packet that is sent to the server that contains the transform and the client index
struct ClientPacket {
	int packetType = 0;
	int clientIndex = -1;
	TransformPacket transform;
};

struct TargetHitPacket
{
	int packetType = 1;
	int clientIndex = -1;
	std::string TargetName;
};

struct TargetHitData
{
	int packetType = 2;
	int clientIndex;
	std::string TargetName;
};

struct LevelChangePacket {
	int packetType = 2;
	int clientIndex;
	int LevelSelect = 0;
};

struct LevelChangeData {
	int packetType = 3;
	int clientIndex;
	int LevelSelect;
};

//The Network system is responsible with sending and recieving packages, and finally put them into
//an event that the rest of the engine can use. The Network system will act similar to the Event system.
class Network_System : public SubSystem
{
private:
	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer;
	ENetEvent enetEvent;

	PhysicsData* serverData = new PhysicsData;

	ClientData* clientData = new ClientData;
	ClientPacket* clientPacket = new ClientPacket;

	TargetHitPacket* targetPacket = new TargetHitPacket;
	TargetHitData* targetData = new TargetHitData;

	LevelChangePacket* LCP = new LevelChangePacket;
	LevelChangeData* LCD = new LevelChangeData;
	void SendTranformPacket();
	void SendTargetPacket(Event* e);
	void SendLevelChangePacket(Event* e);
	bool FirstClient = false;
	int count = 0;
public:


	Entity_System* ES;


	int* packetType = new int;


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

