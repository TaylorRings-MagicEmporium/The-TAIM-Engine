#pragma once
#include <SDL2\SDL.h>

enum class KEYLETTERCODE {KEY_A,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F,KEY_G,
KEY_H,KEY_I,KEY_J,KEY_K,KEY_L,KEY_M,KEY_N,KEY_O,KEY_P,
KEY_Q,KEY_R,KEY_S,KEY_T,KEY_U,KEY_V,KEY_W,KEY_X,KEY_Y,KEY_Z};

enum class KEYNUMBERCODE {KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0};

class Input_System
{

private:
	SDL_Window* Window;

	bool KeyLetterState[26];
	bool KeyNumberState[10];
public:
	Input_System();
	Input_System(SDL_Window* newWindow);

	void Update_Input();
	void Reset_Input();

	bool GetKeyPressed(KEYLETTERCODE KLC);
	bool GetKeyPressed(KEYNUMBERCODE KNC);
};

