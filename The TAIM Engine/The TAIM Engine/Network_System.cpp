#include "Network_System.h"



Network_System::Network_System() {

}
Network_System::~Network_System() {

}

void Network_System::Update() {

	bool PacketPass[4] = { false,false, false, false };				// PacketPass ensures that only one packet can be recieved for each packet.
																	// if this didn't exist, then hundreds of events would be added per frame, even when they do the same thing.
	while (enet_host_service(client, &enetEvent, 0) > 0) {
		switch (enetEvent.type) {

		case ENET_EVENT_TYPE_RECEIVE:

			memcpy(packetType, enetEvent.packet->data, sizeof(int)); // all packets have int as their first value, this means the "type" of packet can be figured out before copying the rest.
			if (*packetType == 0 && !PacketPass[0]) {
				Comm_Layer->CanChangeLevel = false;
				memcpy(clientData, enetEvent.packet->data, sizeof(ClientData)); // memcpy copies actual data into memory, but it is a risky move to do.
				std::cout << "connection Packet Recieved!" << std::endl;
				clientIndex = clientData->clientIndex;
				serverConnect = true;
				FirstClient = clientData->FirstClient;
				Comm_Layer->CanChangeLevel = FirstClient;
				if (FirstClient) {
					std::cout << "YAY! I'm the first client!" << std::endl;
				}
				if (clientData->CurrentLevel != Comm_Layer->CurrentLevel) {
					ChangeLevel* ev = new ChangeLevel();
					ev->level = clientData->CurrentLevel;
					Event_Queue->AddEventToStack(ev);
				}
				PacketPass[0] = true;
			}
			else if (*packetType == 1 && !PacketPass[1]) {

				memcpy(serverData, enetEvent.packet->data, sizeof(PhysicsData));

				std::vector<Entity*> ghostEntities = ES->GetEntitiesWithTag("Ghost");
				
				for (int i = 0; i < 2; i++) {
					if (i != clientIndex) {
						// the data from the packet is put into a "update transform" event with the ghost object target.
						Event* ev = new UpdateTransform();
						ev->ListOfEntities.insert(ev->ListOfEntities.end(), ghostEntities.begin(), ghostEntities.end());
						static_cast<UpdateTransform*>(ev)->pos = glm::vec3(serverData->transforms[i].x, serverData->transforms[i].y, serverData->transforms[i].z);
						static_cast<UpdateTransform*>(ev)->rot = glm::quat(serverData->transforms[i].qw, serverData->transforms[i].qx, serverData->transforms[i].qy, serverData->transforms[i].qz);
						Event_Queue->AddEventToStack(ev);
					}
				}
				PacketPass[1] = true;
			}
			else if (*packetType == 2 && !PacketPass[2]) {
				// the data from the packet is to find out which target got deleted. it goes by name, as the file loader loads the entities in an unspecificed order.
				//completing the Target process requires three seperate events
				memcpy(targetData, enetEvent.packet->data, sizeof(TargetHitData));
				if (targetData->clientIndex != clientIndex) {
					count++;
					std::cout << count << std::endl;
					std::cout << "target name:" << targetData->TargetName << std::endl;
					Entity* hit = ES->GetEntityWithName(targetData->TargetName);
					AnimationBegin* ev1 = new AnimationBegin(); // 1. plays the animation
					ev1->ListOfEntities.push_back(hit);
					ev1->SubSystemOrder.push_back(SubSystemType::Animation);
					Event_Queue->AddEventToStack(ev1);

					Profiling_System::GetInstance()->IncrementPlayer2Hit();

					HideComponent* ev2 = new HideComponent(); // hides the rigidbody component from physics
					ev2->ListOfEntities.push_back(hit);
					ev2->SubSystemOrder.push_back(SubSystemType::Physics);
					Event_Queue->AddEventToStack(ev2);

					PlaySoundEv* ev3 = new PlaySoundEv(); // plays the shooting sound from the player tag
					ev3->ListOfEntities.push_back(ES->GetEntitiesWithTag("Player")[0]);
					Event_Queue->AddEventToStack(ev3);
						
				}
			}
			else if (*packetType == 3 && !PacketPass[3]) {
				// the data from the packet is used to change or restart the level, even if it's the same level. 
				memcpy(LCD, enetEvent.packet->data, sizeof(LevelChangeData));
				if (LCD->clientIndex != clientIndex) {
					ChangeLevel* ev = new ChangeLevel();
					ev->SubSystemOrder.push_back(SubSystemType::System);
					ev->level = LCD->LevelSelect;
					Event_Queue->AddEventToStack(ev);
				}
			}

			break;

		}
		enet_packet_destroy(enetEvent.packet);

	}
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

		SendTranformPacket();

		typedef void (Network_System::* method_function)(Event*);
		method_function method_pointer[EVENT_TYPE_COUNT];
		method_pointer[(int)EventType::GunShot] = &Network_System::SendTargetPacket;
		method_pointer[(int)EventType::ChangeLevel] = &Network_System::SendLevelChangePacket;
		while (Event* e = Event_Queue->PollEvents(SubSystemType::Network)) {
			method_function func = method_pointer[(int)e->GetType()];
			(this->*func)(e);
		}
	}
	else {
		while (Event* e = Event_Queue->PollEvents(SubSystemType::Network));
	}
}

void Network_System::SendTranformPacket()
{
	clientPacket->clientIndex = clientIndex;
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

void Network_System::SendTargetPacket(Event* e)
{
	Gunshot* g = (Gunshot*)(e);
	targetPacket->TargetName = g->ListOfEntities[0]->GetName();
	targetPacket->clientIndex = clientIndex;
	dataPacket = enet_packet_create(targetPacket, sizeof(TargetHitPacket), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, dataPacket);
}

void Network_System::SendLevelChangePacket(Event* e)
{
	ChangeLevel* l = (ChangeLevel*)(e);
	LCP->clientIndex = clientIndex;
	LCP->LevelSelect = l->level;
	dataPacket = enet_packet_create(LCP, sizeof(LevelChangePacket), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, dataPacket);
}
