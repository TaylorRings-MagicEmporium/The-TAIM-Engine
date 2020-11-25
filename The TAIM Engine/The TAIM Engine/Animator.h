#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Component.h"
#include <iostream>

struct KeyFrame {
	KeyFrame() {};
	glm::vec3 position = glm::vec3(0);
	glm::quat rotation = glm::quat(1, 0, 0, 0);
	glm::vec3 scale = glm::vec3(1);

	float duration = 1;
};

class Animator : public Component
{
private:

	KeyFrame CurrentValues;
	bool start = false;

	bool loop = true;
	int KeyFrameCounter = 0;
	float overallTime = 0;
	float keyTransitionTime = 0;
	float timeScale = 1;

public:

	bool AnimationStarted = false;
	bool AnimationPlaying = false;
	bool AnimationEnd = false;

	bool announced = true;

	bool DeleteAfterCompletion = false;


	std::vector<KeyFrame> AnimationStructure;

	Animator() { type = ComponentType::Animator; };
	void UpdateAnimation(float deltaTime);
	void StartAnimation() { start = true; };
	void PauseAnimation() { AnimationPlaying = false; };
	void SetTimeScale(float sca) {timeScale = sca;};
	void SetLooping(bool state) { loop = state; };
	bool IsPlaying() { return AnimationPlaying; };

	glm::vec3 Vec3Lerp(glm::vec3 start, glm::vec3 end, float percent);

	//float EaseinoutQuad(float currTime, glm::vec3 start, glm::vec3 end, float duration);
};

