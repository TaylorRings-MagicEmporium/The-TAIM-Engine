#include "Animation_System.h"

Animation_System::Animation_System() {
	for (int i = 0; i < 4; i++) {
		Bubble_shrink_Animation.push_back(KeyFrame());
	}
	Bubble_shrink_Animation[1].scale = glm::vec3(0.5);
	Bubble_shrink_Animation[2].scale = glm::vec3(1.2);
	Bubble_shrink_Animation[3].scale = glm::vec3(0);

	Bubble_shrink_Animation[0].duration = 0;
	Bubble_shrink_Animation[1].duration = 1;
	Bubble_shrink_Animation[2].duration = 1;
	Bubble_shrink_Animation[3].duration = 1;
}

void Animation_System::Startup()
{
}

void Animation_System::Shutdown()
{
	ListOfAnimators.clear();
}

void Animation_System::Update()
{
	typedef void (Animation_System::* method_function)(Event*);
	method_function method_pointer[EVENT_TYPE_COUNT];
	method_pointer[(int)EventType::GunShot] = &Animation_System::BeginAnimation;
	method_pointer[(int)EventType::AnimationBegin] = &Animation_System::BeginAnimation;
	while (Event* e = Event_Queue->PollEvents(SubSystemType::Animation)) {
		method_function func = method_pointer[(int)e->GetType()];
		(this->*func)(e);
	}

	for (int i = 0; i < ListOfAnimators.size(); i++) {
		ListOfAnimators[i].UpdateAnimation(deltaTime);

		if (ListOfAnimators[i].AnimationEnd && ListOfAnimators[i].announced) {
			ListOfAnimators[i].announced = false;
			Event* ev = new AnimationEnd();
			ev->SubSystemOrder.push_back(SubSystemType::Graphics);
			ev->ListOfEntities.push_back(ListOfAnimators[i].GO);
			Event_Queue->AddEventToStack(ev);
		}
	}
}

void Animation_System::SetComponentSize(int size)
{
	ListOfAnimators.reserve(100);
}

Animator* Animation_System::CreateAnimator(std::string type, bool IsLooping, bool StartOnLoad)
{
	Animator a = Animator();
	a.SetLooping(IsLooping);
	if (StartOnLoad) {
		a.StartAnimation();
	}
	if (type == "Bubble_shrink") {
		a.AnimationStructure = Bubble_shrink_Animation;
	}

	ListOfAnimators.push_back(a);
	return &ListOfAnimators.back();
	
}

void Animation_System::BeginAnimation(Event* e) {
	for (int i = 0; i < e->ListOfEntities.size(); i++)
	{
		Animator* a = static_cast<Animator*>(e->ListOfEntities[i]->GetComponent(ComponentType::Animator));
		a->StartAnimation();
	}
}

void Animation_System::ResetSystem() {
	ListOfAnimators.clear();
}
