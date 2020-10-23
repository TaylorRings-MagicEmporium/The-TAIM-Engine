#include "Input_System.h"

Input_System::Input_System()
{
}

Input_System::Input_System(SDL_Window* newWindow) {
	Window = newWindow;
	Reset_Input();
}

void Input_System::Reset_Input() {
	for (int i = 0; i < 26; i++) {
		KeyLetterState[i] = false;
	}
	for (int i = 0; i < 10; i++) {
		KeyNumberState[i] = false;
	}
}

void Input_System::Update_Input() {
	Reset_Input();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	int begin = SDL_SCANCODE_A;
	int end = SDL_SCANCODE_Z;
	for (int i = begin; i < end; i++) {
		KeyLetterState[i - begin] = state[i];
	}

	begin = SDL_SCANCODE_1;
	end = SDL_SCANCODE_0;
	for (int i = begin; i < end; i++) {
		KeyNumberState[i - begin] = state[i];
	}

	begin = SDL_SCANCODE_RETURN;
	end = SDL_SCANCODE_CAPSLOCK;
	for (int i = begin; i < end; i++) {
		KeySpecialState[i - begin] = state[i];
	}
}

bool Input_System::GetKeyPressed(KEYLETTERCODE KLC) {
	return KeyLetterState[(int)KLC];
}

bool Input_System::GetKeyPressed(KEYNUMBERCODE KNC) {
	return KeyNumberState[(int)KNC];
}

bool Input_System::GetKeyPressed(KEYSPECIALCODE KSC) {
	return KeySpecialState[(int)KSC]; 
}

