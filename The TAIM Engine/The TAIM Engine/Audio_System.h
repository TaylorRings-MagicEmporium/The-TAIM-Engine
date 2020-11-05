#pragma once

#include <iostream>
#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <vector>

#include "AudioPlayer.h"
#include "EventQueue.h"

class Audio_System
{
private:
	FMOD::Studio::System* system = NULL;
	FMOD::System* lowLevelSystem = NULL;
	FMOD::Channel* channel = NULL;
	std::vector<AudioPlayer> ListOfAudioPlayers;
public:
	Audio_System(int ComponentSize);
	~Audio_System();
	void Setup();
	void Update(EventQueue* EQ);
	Component* CreateAudioPlayer(std::string AudioPath);

	void EvPlaySound(Event* e);
};

