#include "Animator.h"

void Animator::UpdateAnimation(float deltaTime)
{
	if (start) {
		AnimationStarted = true;
		AnimationPlaying = true;
		start = false;
	}

	if (AnimationPlaying && !AnimationEnd) {
		if (KeyFrameCounter == AnimationStructure.size() - 1) {
			if (loop) {
				KeyFrameCounter = 0; // animation loops back to the start
			}
			else {
				AnimationEnd = true;
				AnimationPlaying = false;
				return; // animation stops
			}
			overallTime = 0;
		}


		overallTime += deltaTime;
		KeyFrame start = AnimationStructure[KeyFrameCounter];
		KeyFrame end = AnimationStructure[KeyFrameCounter + 1];

		CurrentValues.scale = Vec3Lerp(start.scale, end.scale, keyTransitionTime / end.duration);
		//std::cout << CurrentValues.scale.x << ", " << CurrentValues.scale.y << ", " << CurrentValues.scale.z << std::endl;
		keyTransitionTime += deltaTime;

		GO->transform.scale = CurrentValues.scale;

		if (keyTransitionTime > end.duration) {
			KeyFrameCounter += 1;
			keyTransitionTime = 0;
		}
	}

}

glm::vec3  Animator::Vec3Lerp(glm::vec3 start, glm::vec3 end, float percent) {
	return start + (end - start) * percent;
	//return start + (end * percent);
}

//float EaseinoutQuad(float currTime, glm::vec3 start, glm::vec3 end, float duration) {
//	return 0;
//}

