
#include <iostream>
#include <enet/enet.h>
#include <SDL2/SDL.h>

//struct Vector2 {
//	float x, y;
//};

struct TransformPacket {
	float x, y, z;
	float qx, qy, qz, qw;
};

struct PhysicsData {
	int packetType = 1;
	TransformPacket transforms[2];
};

struct ClientData {
	int packetType = 0;
	int clientIndex;
	bool FirstClient;
	int CurrentLevel = 0;
};


struct TargetHitData {
	int packetType = 2;
	int clientIndex = -1;
	std::string TargetName = "";
};

struct ClientPacket {
	int packetType = 0;
	int clientIndex;
	TransformPacket transform;
};

struct TargetHitPacket
{
	int packetType = 1;
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


int main(int argc, char* args[]) {
	SDL_Window* gWindow = NULL;

	//initialises SDL and creates a window
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else {
		gWindow = SDL_CreateWindow("The TAIM Server", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
	}

	int clientCount = 0;
	int* packetType = new int;
	if (enet_initialize() != 0) {
		std::cout << "Enet failed to initialise!" << "\n\n";
	}

	ENetAddress address;
	ENetHost* server;
	ENetEvent enetEvent;

	ENetPacket* dataPacket;

	address.host = ENET_HOST_ANY;
	address.port = 1234;

	//creates an host that has max of 3s clients and 2 channels
	server = enet_host_create(&address, 32, 2, 0, 0);

	if (server == NULL) {
		std::cout << "server failed to initialise!" << "\n\n";
	}
	else {
		std::cout << "Server is active!" << std::endl;
	}

	int FirstClient = -1;
	// PhysicsData contains each client's position data at start. when a client is connected, they will update their packet,
	// while it recieves the default data of the other client.
	PhysicsData* physicsData = new PhysicsData;

	physicsData->transforms[0].x = 0;
	physicsData->transforms[0].y = 3.0f;
	physicsData->transforms[0].z = 0;
	physicsData->transforms[0].qx = 0;
	physicsData->transforms[0].qy = 0;
	physicsData->transforms[0].qz = 0;
	physicsData->transforms[0].qw = 1.0f;

	physicsData->transforms[1].x = 0;
	physicsData->transforms[1].y = 3.0f;
	physicsData->transforms[1].z = 0;
	physicsData->transforms[1].qx = 0;
	physicsData->transforms[1].qy = 0;
	physicsData->transforms[1].qz = 0;
	physicsData->transforms[1].qw = 1.0f;

	// used to store incoming data
	ClientPacket* clientPacket = new ClientPacket;

	clientPacket->clientIndex = 0;
	//clientPacket->position.x = 0.0f;
	//clientPacket->position.y = 0.0f;

	clientPacket->clientIndex = 0;
	clientPacket->transform.x = 0;
	clientPacket->transform.y = 0;
	clientPacket->transform.z = 0;
	clientPacket->transform.qx = 0;
	clientPacket->transform.qy = 0;
	clientPacket->transform.qz = 0;
	clientPacket->transform.qw = 1.0f;


	ClientData* clientData = new ClientData;
	TargetHitPacket* targetPacket = new TargetHitPacket;
	TargetHitData* targetData = new TargetHitData;
	targetData->clientIndex = 0;

	LevelChangePacket* LCP = new LevelChangePacket;
	LevelChangeData* LCD = new LevelChangeData;
	int currentLevel = 0;

	bool quit = false;
	SDL_Event e;

	while (!quit) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		while (enet_host_service(server, &enetEvent, 0) > 0) {
			switch (enetEvent.type) {
				// when a client connects for the first time
			case ENET_EVENT_TYPE_CONNECT:

				std::cout << "a client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";
				clientData->clientIndex = clientCount;
				if (FirstClient == -1) {
					FirstClient = clientData->clientIndex;
					clientData->FirstClient = true;
				}
				else {
					clientData->FirstClient = false;
				}
				// we send a packet to the client that connected to say that connection is successful.
				dataPacket = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(enetEvent.peer, 0, dataPacket);

				//enetEvent.peer->data = (void*)"This is a client";
				clientCount++;

				break;
				// when a client disconnects for the first time
			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "the client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";
				enetEvent.peer->data = NULL;
				clientCount--;

				if (clientCount == 0) {
					FirstClient = false;
				}

				break;
				// when a client sends a packet and the server recieves it
			case ENET_EVENT_TYPE_RECEIVE:

				memcpy(packetType, enetEvent.packet->data, enetEvent.packet->dataLength);
				if (*packetType == 0) {
					// memcpy copies the actual data (1's and 0's) to a position pointer. as the data is the same length as "transform",
					// we can access it with ease with clientPacket acting as our safe buffer.
					memcpy(clientPacket, enetEvent.packet->data, enetEvent.packet->dataLength);
					int currentClient = clientPacket->clientIndex;
					//physicsData->transforms[clientPacket->clientIndex] = clientPacket->transform;
					physicsData->transforms[clientPacket->clientIndex] = clientPacket->transform;
				}
				else if (*packetType == 1) {
					memcpy(targetPacket, enetEvent.packet->data, enetEvent.packet->dataLength);
					targetData->clientIndex = targetPacket->clientIndex;
					targetData->TargetName = targetPacket->TargetName;
					dataPacket = enet_packet_create(targetData, sizeof(TargetHitData), ENET_PACKET_FLAG_RELIABLE);
					enet_host_broadcast(server, 0, dataPacket);
				}
				else if (*packetType == 2) {
					memcpy(LCP, enetEvent.packet->data, enetEvent.packet->dataLength);
					currentLevel = LCP->LevelSelect;

					LCD->clientIndex = LCP->clientIndex;
					LCD->LevelSelect = currentLevel;

					dataPacket = enet_packet_create(LCD, sizeof(LevelChangeData), ENET_PACKET_FLAG_RELIABLE);
					enet_host_broadcast(server, 0, dataPacket);
				}

			}
			enet_packet_destroy(enetEvent.packet);

		}
		// this creates a packet that calls on all channels and contains ALL of the transforms. the client will then pick the transform that isn't their own.

		if (clientCount > 0) {
			dataPacket = enet_packet_create(physicsData, sizeof(PhysicsData), ENET_PACKET_FLAG_RELIABLE);
			enet_host_broadcast(server, 0, dataPacket);
		}

	}


	// delete it all!

	delete physicsData;
	delete clientData;
	delete clientPacket;

	enet_host_destroy(server);
	atexit(enet_deinitialize);

	std::cout << "server closed successfully!" << std::endl;

	return 0;
}