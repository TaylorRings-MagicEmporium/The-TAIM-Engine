#pragma once

#include <iostream>
#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <vector>

#include "AudioPlayer.h"
#include "SubSystem.h"
class Audio_System : public SubSystem
{
private:
	FMOD::Studio::System* system = NULL;
	FMOD::System* lowLevelSystem = NULL;
	FMOD::Channel* channel = NULL;
	std::vector<AudioPlayer> ListOfAudioPlayers;
public:
	Audio_System();
	~Audio_System();
	void Update();
	void Startup();
	void SetComponentSize(int size);
	Component* CreateAudioPlayer(std::string AudioPath);
	void ResetSystem();

	void EvPlaySound(Event* e);
	void PlayGunShotSound(Event* e);
};

