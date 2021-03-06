#pragma once
#include "SubSystem.h"
#include "Animator.h"



enum class AnimationType {Null, Bubble_shrink};

// the animation system is responsible for playing animations. for now, the animations are hard-coded
// but in the future, this can be read from a file.
class Animation_System : public SubSystem
{
protected:
	std::vector<Animator> ListOfAnimators;

	std::vector<KeyFrame> Bubble_shrink_Animation;
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

