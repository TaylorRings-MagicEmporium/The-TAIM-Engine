#include "Audio_System.h"

Audio_System::Audio_System(int ComponentSize) {
	ListOfAudioPlayers.reserve(ComponentSize);
}
Audio_System::~Audio_System() {

}
void Audio_System::Setup() {
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
void Audio_System::Update(EventQueue* EQ) {

	typedef void (Audio_System::* method_function)(Event*);
	method_function method_pointer[EVENT_TYPE_COUNT];
	method_pointer[(int)EventType::PlaySound] = &Audio_System::EvPlaySound;

	while (Event* e = EQ->PollEvents()) {
		if (e->SystemList[(int)Systems::Audio]) {
			method_function func = method_pointer[(int)e->GetType()];
			(this->*func)(e);
			e->SystemList[(int)Systems::Audio] = false;
		}
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