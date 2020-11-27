#pragma once

#include <iostream>
#include <fmod_studio.hpp>
#include <fmod.hpp>
#include "Component.h"

// Audio player is a component that holds the audiopath and plays audio.
class AudioPlayer : public Component
{
	FMOD::Sound* sound = NULL;
	FMOD::Channel* channel = NULL;
	FMOD::System* system = NULL;
	std::string AudioPath;
	float DefaultFreq = 1.0f; // the default frequency (time speed) of the sound.
public:
	AudioPlayer(std::string AudioPath, FMOD::Channel* chan);
	void Setup();
	// adds the system to the player
	void AddSystem(FMOD::System* system);

	//sets the speed of the audio playing
	void SetSpeed(float percentage);

	// plays the sound
	void PlaySound();
};

