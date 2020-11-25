#pragma once
#include "SubSystem.h"
#include "Animator.h"

enum class AnimationType {Null, Bubble_shrink};


class Animation_System : public SubSystem
{
protected:
	std::vector<Animator> ListOfAnimators;


	std::vector<KeyFrame> Bubble_shrink_Animation;
	//void TogglePlayAnimation(Event* e);
	//void ResetAnimation(Event* e);
	float deltaTime = 1.0f / 60.0f;

	void BeginAnimation(Event* e);
public:
	Animation_System();
	~Animation_System() {};
	void Startup();
	void Shutdown();
	void Update();
	void SetComponentSize(int size);
	void ResetSystem();
	Animator* CreateAnimator(std::string type, bool IsLooping, bool StartOnLoad);

};

