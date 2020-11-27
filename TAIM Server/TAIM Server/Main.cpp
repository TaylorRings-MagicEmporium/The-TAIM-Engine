
#include <iostream>
#include <enet/enet.h>
#include <SDL2/SDL.h>

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
	

	//setups enet properties for the server
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

	// the placeholder creation of PhysicsData
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

	ClientPacket* clientPacket = new ClientPacket;

	clientPacket->clientIndex = 0;
	clientPacket->transform.x = 0;
	clientPacket->transform.y = 0;
	clientPacket->transform.z = 0;
	clientPacket->transform.qx = 0;
	clientPacket->transform.qy = 0;
	clientPacket->transform.qz = 0;
	clientPacket->transform.qw = 1.0f;

	// creates placeholders for data and packets
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

		while (SDL_PollEvent(&e) != 0) {			// unlikely, but this will cause an error with an unpredicted pattern. however, this happens at the end of the server's program
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}

		while (enet_host_service(server, &enetEvent, 0) > 0) {
			switch (enetEvent.type) {

				
			case ENET_EVENT_TYPE_CONNECT:						// when a client connects for the first time

				std::cout << "a client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";
				clientData->clientIndex = clientCount;
				if (FirstClient == -1) {								// determines if the client is the first client to connect to the server.
					FirstClient = clientData->clientIndex;				// stores the data of the first client connected.
					clientData->FirstClient = true;
				}
				else {
					clientData->FirstClient = false;
				}
				
				dataPacket = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);		// we send a packet to the client that connected to say that connection is successful.
				enet_peer_send(enetEvent.peer, 0, dataPacket);

				clientCount++;

				break;

			case ENET_EVENT_TYPE_DISCONNECT:					// when a client disconnects for the first time
				std::cout << "the client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";
				enetEvent.peer->data = NULL;
				clientCount--;									// decrements the client count

				if (clientCount == 0) {
					FirstClient = false;						// if all clients have been disconnected, then it can be considered that the clients has resetted.
																// in that case, firstclient is reset to false;
				}

				break;
				
			case ENET_EVENT_TYPE_RECEIVE:						// when a client sends a packet and the server recieves it

				memcpy(packetType, enetEvent.packet->data, enetEvent.packet->dataLength);								//determines which packet has been recieved for this event.
				if (*packetType == 0) {			//transforms
					memcpy(clientPacket, enetEvent.packet->data, enetEvent.packet->dataLength);
					int currentClient = clientPacket->clientIndex;
					physicsData->transforms[clientPacket->clientIndex] = clientPacket->transform;
				}
				else if (*packetType == 1) {	//target hit data
					memcpy(targetPacket, enetEvent.packet->data, enetEvent.packet->dataLength);
					targetData->clientIndex = targetPacket->clientIndex;
					targetData->TargetName = targetPacket->TargetName;
					dataPacket = enet_packet_create(targetData, sizeof(TargetHitData), ENET_PACKET_FLAG_RELIABLE);
					enet_host_broadcast(server, 0, dataPacket);
				}
				else if (*packetType == 2) {	//level change data
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

		if (clientCount > 0) {
			dataPacket = enet_packet_create(physicsData, sizeof(PhysicsData), ENET_PACKET_FLAG_RELIABLE);
			enet_host_broadcast(server, 0, dataPacket);
		}

	}
	// closes the server and SDL2 window.
	delete physicsData;
	delete clientData;
	delete clientPacket;

	enet_host_destroy(server);
	atexit(enet_deinitialize);

	std::cout << "server closed successfully!" << std::endl;

	return 0;
}