#include "Input_System.h"

Input_System::Input_System()
{
}

void Input_System::AssignWindows(SDL_Window* newWindow) {
	Window = newWindow;
}

void Input_System::Reset_Input() {

	for (int i = 0; i < 54; i++) {
		PrevKeyCodeState[i] = KeyCodeState[i];
		KeyCodeState[i] = false;
	}
}

void Input_System::Update() {
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


	CreateEvents();
}

bool Input_System::GetKeyPressed(KeyCode KC) {
	return KeyCodeState[(int)KC];
}

bool Input_System::GetPrevKeyPressed(KeyCode KC) {
	return PrevKeyCodeState[(int)KC];
}

void Input_System::CreateEvents() {
	Event* ev = new Event();
	std::vector<Entity*> playerEntites = ES->GetEntitiesWithTag("Player");
	std::vector<Entity*> ghostEntites = ES->GetEntitiesWithTag("Ghost");
	if (GetKeyPressed(KeyCode::KEY_W)) {
		ev = new MoveForward();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		//ev->ListOfEntities.push_back(&EntityList[0]);
		Event_Queue->AddEventToStack(ev);
	}
	if (GetKeyPressed(KeyCode::KEY_A)) {
		ev = new MoveLeft();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue->AddEventToStack(ev);
	}
	if (GetKeyPressed(KeyCode::KEY_S)) {
		ev = new MoveBackward();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue->AddEventToStack(ev);
	}
	if (GetKeyPressed(KeyCode::KEY_D)) {
		ev = new MoveRight();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue->AddEventToStack(ev);
	}
	if (GetKeyPressed(KeyCode::KEY_SPACE)) {
		ev = new Jump();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue->AddEventToStack(ev);
	}
	if (GetKeyPressed(KeyCode::KEY_N) && !GetPrevKeyPressed(KeyCode::KEY_N)) {
		ev = new PlaySoundEv();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue->AddEventToStack(ev);
	}
	if (GetKeyPressed(KeyCode::KEY_TAB) && !GetPrevKeyPressed(KeyCode::KEY_TAB)) {
		ev = new ResetTransform();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue->AddEventToStack(ev);
	}
	if (GetKeyPressed(KeyCode::KEY_RETURN) && !GetPrevKeyPressed(KeyCode::KEY_RETURN)) {
		std::cout << "INPUT SYSTEM: RECIEVED" <<std::endl;
		ev = new Gunshot();
		Gunshot* g = (Gunshot*)(ev);
		g->SubSystemOrder.push_back(SubSystemType::EntityS);
		g->SubSystemOrder.push_back(SubSystemType::Physics);
		g->startEntity = playerEntites[0];
		g->tagToReact = "Target";

		Event_Queue->AddEventToStack(ev);
	}
	if (GetKeyPressed(KeyCode::KEY_P) && !GetPrevKeyPressed(KeyCode::KEY_P)) {
		ev = new ChangeCamera();
		Event_Queue->AddEventToStack(ev);
	}
	if (GetKeyPressed(KeyCode::KEY_0) && !GetPrevKeyPressed(KeyCode::KEY_0)) {
		if (Comm_Layer->CanChangeLevel) {
			count++;
			if (count > 1) {
				count = 0;
			}
			ev = new ChangeLevel();
			ChangeLevel* l = (ChangeLevel*)(ev);
			l->level = count;
			ev->SubSystemOrder.push_back(SubSystemType::System);
			ev->SubSystemOrder.push_back(SubSystemType::Network);
			Event_Queue->AddEventToStack(ev);
		}
		else {
			std::cout << "Sorry! only the first client can change levels" << std::endl;
		}
	}
}