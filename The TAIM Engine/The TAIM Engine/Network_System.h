#pragma once
#include <enet/enet.h>
#include <iostream>

#include "EventQueue.h"
#include "Entity_System.h"

struct TransformPacket {
	float x, y, z;
	float qx, qy, qz, qw;
};

//struct Vector2 {
//	float x;
//	float y;
//};

struct PhysicsData {
	int packetType = 1;
	TransformPacket transforms[2];
};

struct ClientData {
	int packetType = 0;
	int clientIndex;
};

struct ClientPacket {
	int clientIndex;
	TransformPacket transform;
};

class Network_System
{
public:
	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer;
	ENetEvent enetEvent;
	EventQueue* Event_Queue;
	Entity_System* ES;

	PhysicsData* serverData = new PhysicsData;
	ClientData* clientData = new ClientData;
	int* packetType = new int;

	ClientPacket* clientPacket = new ClientPacket;
	ENetPacket* dataPacket;

	int clientIndex = -1;
	bool serverConnect = false;

	Network_System();
	void Setup();
	void Update();
	void PostUpdate();
	void ShutDown();


};

