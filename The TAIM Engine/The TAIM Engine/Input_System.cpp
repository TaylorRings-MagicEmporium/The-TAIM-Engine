#include "Input_System.h"

Input_System::Input_System()
{
}

Input_System::Input_System(SDL_Window* newWindow) {
	Window = newWindow;
	Reset_Input();
}

void Input_System::Reset_Input() {

	for (int i = 0; i < 54; i++) {
		PrevKeyCodeState[i] = KeyCodeState[i];
		KeyCodeState[i] = false;
	}
}

void Input_System::Update_Input() {
	Reset_Input();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	int begin = SDL_SCANCODE_A;
	int end = SDL_SCANCODE_Z;
	for (int i = begin; i < end; i++) {
		KeyCodeState[i - begin] = state[i];
	}
	KeyCodeState[(int)KeyCode::KEY_0] = state[SDL_SCANCODE_0];
	KeyCodeState[(int)KeyCode::KEY_1] = state[SDL_SCANCODE_1];
	KeyCodeState[(int)KeyCode::KEY_2] = state[SDL_SCANCODE_2];
	KeyCodeState[(int)KeyCode::KEY_3] = state[SDL_SCANCODE_3];
	KeyCodeState[(int)KeyCode::KEY_4] = state[SDL_SCANCODE_4];
	KeyCodeState[(int)KeyCode::KEY_5] = state[SDL_SCANCODE_5];
	KeyCodeState[(int)KeyCode::KEY_6] = state[SDL_SCANCODE_6];
	KeyCodeState[(int)KeyCode::KEY_7] = state[SDL_SCANCODE_7];
	KeyCodeState[(int)KeyCode::KEY_8] = state[SDL_SCANCODE_8];
	KeyCodeState[(int)KeyCode::KEY_9] = state[SDL_SCANCODE_9];

	KeyCodeState[(int)KeyCode::KEY_RETURN] = state[SDL_SCANCODE_RETURN];
	KeyCodeState[(int)KeyCode::KEY_ESCAPE] = state[SDL_SCANCODE_ESCAPE];
	KeyCodeState[(int)KeyCode::KEY_BACKSPACE] = state[SDL_SCANCODE_BACKSPACE];
	KeyCodeState[(int)KeyCode::KEY_TAB] = state[SDL_SCANCODE_TAB];
	KeyCodeState[(int)KeyCode::KEY_SPACE] = state[SDL_SCANCODE_SPACE];
	KeyCodeState[(int)KeyCode::KEY_MINUS] = state[SDL_SCANCODE_MINUS];
	KeyCodeState[(int)KeyCode::KEY_EQUALS] = state[SDL_SCANCODE_EQUALS];
	KeyCodeState[(int)KeyCode::KEY_LEFTBRACKET] = state[SDL_SCANCODE_LEFTBRACKET];
	KeyCodeState[(int)KeyCode::KEY_RIGHTBRACKET] = state[SDL_SCANCODE_RIGHTBRACKET];
	KeyCodeState[(int)KeyCode::KEY_BACKSLASH] = state[SDL_SCANCODE_BACKSLASH];
	KeyCodeState[(int)KeyCode::KEY_NONUSHASH] = state[SDL_SCANCODE_NONUSHASH];
	KeyCodeState[(int)KeyCode::KEY_SEMICOLON] = state[SDL_SCANCODE_SEMICOLON];
	KeyCodeState[(int)KeyCode::KEY_APOSTROPHE] = state[SDL_SCANCODE_APOSTROPHE];
	KeyCodeState[(int)KeyCode::KEY_GRAVE] = state[SDL_SCANCODE_GRAVE];
	KeyCodeState[(int)KeyCode::KEY_COMMA] = state[SDL_SCANCODE_COMMA];
	KeyCodeState[(int)KeyCode::KEY_PERIOD] = state[SDL_SCANCODE_PERIOD];
	KeyCodeState[(int)KeyCode::KEY_SLASH] = state[SDL_SCANCODE_SLASH];
	KeyCodeState[(int)KeyCode::KEY_CAPSLOCK] = state[SDL_SCANCODE_CAPSLOCK];


	//int begin = SDL_SCANCODE_A;
	//int end = SDL_SCANCODE_Z;
	//for (int i = begin; i < end; i++) {
	//	KeyLetterState[i - begin] = state[i];
	//}

	//begin = SDL_SCANCODE_1;
	//end = SDL_SCANCODE_0;
	//for (int i = begin; i < end; i++) {
	//	KeyNumberState[i - begin] = state[i];
	//}

	//begin = SDL_SCANCODE_RETURN;
	//end = SDL_SCANCODE_CAPSLOCK;
	//for (int i = begin; i < end; i++) {
	//	KeySpecialState[i - begin] = state[i];
	//}
}

//bool Input_System::GetKeyPressed(KEYLETTERCODE KLC) {
//	return KeyLetterState[(int)KLC];
//}
//
//bool Input_System::GetKeyPressed(KEYNUMBERCODE KNC) {
//	return KeyNumberState[(int)KNC];
//}
//
//bool Input_System::GetKeyPressed(KEYSPECIALCODE KSC) {
//	return KeySpecialState[(int)KSC]; 
//}
//
//bool Input_System::GetPrevKeyPressed(KEYLETTERCODE KLC) {
//	return PrevKeyLetterState[(int)KLC];
//}
//
//bool Input_System::GetPrevKeyPressed(KEYNUMBERCODE KNC) {
//	return PrevKeyNumberState[(int)KNC];
//}
//
//bool Input_System::GetPrevKeyPressed(KEYSPECIALCODE KSC) {
//	return PrevKeySpecialState[(int)KSC];
//}

bool Input_System::GetKeyPressed(KeyCode KC) {
	return KeyCodeState[(int)KC];
}

bool Input_System::GetPrevKeyPressed(KeyCode KC) {
	return PrevKeyCodeState[(int)KC];
}
