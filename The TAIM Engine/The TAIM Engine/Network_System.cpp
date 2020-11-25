#include "Network_System.h"

Network_System::Network_System() {

}
Network_System::~Network_System() {

}

void Network_System::Update() {
	int count = 0;
	bool PacketPass[2] = { false,false }; // PacketPass ensures that only one packet can be recieved for each packet.
	// if this didn't exist, then hundreds of events would be added, even when they do the same thing.
	while (enet_host_service(client, &enetEvent, 0) > 0) {
		switch (enetEvent.type) {

		case ENET_EVENT_TYPE_RECEIVE:

			memcpy(packetType, enetEvent.packet->data, sizeof(int)); // all pachets have int as their first value, this means the "type" of packet can be figured out before copying the rest.
			if (*packetType == 0 && !PacketPass[0]) {
				memcpy(clientData, enetEvent.packet->data, sizeof(ClientData)); // memcpy copies actual data into memory, but it is a risky move to do.
				std::cout << "connection Packet Recieved!" << std::endl;
				clientIndex = clientData->clientIndex;
				serverConnect = true;

				PacketPass[0] = true;
			}
			else if (*packetType == 1 && !PacketPass[1]) {
				//std::cout << "update Packet Recieved!" << std::endl;
				count++;
				memcpy(serverData, enetEvent.packet->data, sizeof(PhysicsData));

				std::vector<Entity*> ghostEntities = ES->GetEntitiesWithTag("Ghost");
				for (int i = 0; i < 2; i++) {
					if (i != clientIndex) {

						// the data from the packet it put into a "update transform" event with the ghost object target.
						Event* ev = new UpdateTransform();
						ev->ListOfEntities.insert(ev->ListOfEntities.end(), ghostEntities.begin(), ghostEntities.end());
						static_cast<UpdateTransform*>(ev)->pos = glm::vec3(serverData->transforms[i].x, serverData->transforms[i].y, serverData->transforms[i].z);
						static_cast<UpdateTransform*>(ev)->rot = glm::quat(serverData->transforms[i].qw, serverData->transforms[i].qx, serverData->transforms[i].qy, serverData->transforms[i].qz);
						Event_Queue->AddEventToStack(ev);
					}
				}
				PacketPass[1] = true;
			}

			break;

		}
		enet_packet_destroy(enetEvent.packet);

	}
	//std::cout << count << std::endl;
}

void Network_System::ShutDown() {

	enet_peer_disconnect_now(peer, 0);

	enet_host_destroy(client);
	atexit(enet_deinitialize);

}

void Network_System::Startup() {
	if (enet_initialize() != 0) { // initialises the Enet middleware
		std::cout << "Enet failed to initialise" << std::endl;
	}

	client = enet_host_create(NULL, 1, 2, 0, 0); // creates a host

	if (client == NULL) {
		std::cout << "Client failed to initialise!" << std::endl;
	}

	enet_address_set_host(&address, "localhost");
	address.port = 1234; // sets the network to look at (this is local)

	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) {
		std::cout << "No available peers for initializing an Enet connection." << std::endl;
	}


	*packetType = -1;
}

void Network_System::LateUpdate() {
	// due to the nature of networking, a post update is needed to send a packet AFTER the client's transform is updated.
	if (serverConnect) {
		clientPacket->clientIndex = clientIndex;
		//clientPacket->position.x = 100.0f;
		//clientPacket->position.y = 300.0f;
		std::vector<Entity*> playerEntities = ES->GetEntitiesWithTag("Player");
		clientPacket->transform.x = playerEntities[0]->transform.position.x;
		clientPacket->transform.y = playerEntities[0]->transform.position.y;
		clientPacket->transform.z = playerEntities[0]->transform.position.z;
		clientPacket->transform.qw = playerEntities[0]->transform.Rotation.w;
		clientPacket->transform.qx = playerEntities[0]->transform.Rotation.x;
		clientPacket->transform.qy = playerEntities[0]->transform.Rotation.y;
		clientPacket->transform.qz = playerEntities[0]->transform.Rotation.z;

		dataPacket = enet_packet_create(clientPacket, sizeof(ClientPacket), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, dataPacket); // finally the packet is sent
	}
}