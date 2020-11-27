#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(std::string AudioPath,FMOD::Channel* chan) {
	type = ComponentType::AudioPlayer;
	this->AudioPath = AudioPath;
	this->channel = chan;
	//this->system = system;
}

void AudioPlayer::Setup() {
	system->createSound(AudioPath.c_str(), FMOD_LOOP_OFF, NULL, &sound);
	if (sound) {
		std::cout << "Sound loaded." << std::endl;
		sound->getDefaults(&DefaultFreq, nullptr);
	}
	else {
		std::cout << "SOUND NOT LOADED" << std::endl;
	}
}
void AudioPlayer::SetSpeed(float percentage) {
	sound->setDefaults(DefaultFreq * percentage,0);
}
void AudioPlayer::PlaySound() {
	system->playSound(sound, NULL, false, &channel);
}

void AudioPlayer::AddSystem(FMOD::System* system) {
	this->system = system;
}

//AUDIO CREDIT
//"Gun Shot.wav" by Bird_man on freesound.org