#include "Audio_System.h"

Audio_System::Audio_System() {
}
Audio_System::~Audio_System() {

}

void Audio_System::SetComponentSize(int size) {
	// if the list was not reserved, then this will cause a game breaking issue of pointers becoming null.
	ListOfAudioPlayers.reserve(size);
}
void Audio_System::Startup()
{
	FMOD::Studio::System::create(&system);
	if (system) {
		std::cout << "high-level (fmod studio) audio system created." << "\n";
	}

	//FMOD::System* lowLevelSystem = NULL;
	system->getCoreSystem(&lowLevelSystem);

	if (lowLevelSystem) {
		std::cout << "Low-level (fmod) audio System created." << "\n";
	}

	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
	system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);

	for (int i = 0; i < ListOfAudioPlayers.size(); i++) {
		ListOfAudioPlayers[i].AddSystem(lowLevelSystem);
		ListOfAudioPlayers[i].Setup();
	}
}

void Audio_System::Update() {

	typedef void (Audio_System::* method_function)(Event*);
	method_function method_pointer[EVENT_TYPE_COUNT];
	method_pointer[(int)EventType::PlaySound] = &Audio_System::EvPlaySound;
	method_pointer[(int)EventType::GunShot] = &Audio_System::PlayGunShotSound;

	while (Event* e = Event_Queue->PollEvents(SubSystemType::Audio)) {
		method_function func = method_pointer[(int)e->GetType()];
		(this->*func)(e);
	}


	system->update();
}

Component* Audio_System::CreateAudioPlayer(std::string AudioPath) {
	AudioPlayer a = AudioPlayer(AudioPath, channel);
	ListOfAudioPlayers.push_back(a);
	return &ListOfAudioPlayers.back();
}

void Audio_System::EvPlaySound(Event* e) {
	for (int i = 0; i < e->ListOfEntities.size(); i++) {
		AudioPlayer* a = (AudioPlayer*)e->ListOfEntities[i]->GetComponent(ComponentType::AudioPlayer);
		a->PlaySound();
	}
}

void Audio_System::PlayGunShotSound(Event* e) {
	Gunshot* g = (Gunshot*)(e);
	AudioPlayer* a = (AudioPlayer*)g->startEntity->GetComponent(ComponentType::AudioPlayer);
	a->PlaySound();
}