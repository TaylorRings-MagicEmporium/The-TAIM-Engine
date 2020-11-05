#pragma once

#include <iostream>
#include <fmod_studio.hpp>
#include <fmod.hpp>
#include "Component.h"

class AudioPlayer : public Component
{
	FMOD::Sound* sound = NULL;
	FMOD::Channel* channel = NULL;
	FMOD::System* system = NULL;
	std::string AudioPath;
	float DefaultFreq = 1.0f;
public:
	AudioPlayer(std::string AudioPath, FMOD::Channel* chan);
	void Setup();
	void AddSystem(FMOD::System* system);
	void SetSpeed(float percentage);
	void PlaySound();
};

