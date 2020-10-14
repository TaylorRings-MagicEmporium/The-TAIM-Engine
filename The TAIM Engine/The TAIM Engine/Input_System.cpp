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
	for (int i = SDL_SCANCODE_A; i < SDL_SCANCODE_Z; i++) {
		KeyLetterState[i - SDL_SCANCODE_A] = state[i];
	}
	for (int i = SDL_SCANCODE_1; i < SDL_SCANCODE_0; i++) {
		KeyNumberState[i - SDL_SCANCODE_1] = state[i];
	}
}

bool Input_System::GetKeyPressed(KEYLETTERCODE KLC) {
	return KeyLetterState[(int)KLC];
}

bool Input_System::GetKeyPressed(KEYNUMBERCODE KNC) {
	return KeyNumberState[(int)KNC];
}

