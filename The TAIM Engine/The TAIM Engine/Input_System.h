#pragma once
#include <SDL2\SDL.h>

// KEYLETTERCODE contains all of the letters of the alphabet
enum class KEYLETTERCODE {KEY_A,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F,KEY_G,
KEY_H,KEY_I,KEY_J,KEY_K,KEY_L,KEY_M,KEY_N,KEY_O,KEY_P,
KEY_Q,KEY_R,KEY_S,KEY_T,KEY_U,KEY_V,KEY_W,KEY_X,KEY_Y,KEY_Z};

// KEYNUMBERCODE contains all of the numbers from 0 to 9
enum class KEYNUMBERCODE {KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0};

// the input system is responsible for how the user will interact with the world. it is also considered the first step in event building.
// to keep the abstraction between the window's inputs and gameplay functionality, the input system has it's own keycode for the gameplay to use.
class Input_System
{

private:
	SDL_Window* Window;

	// an array holds the boolean state of the keypresses (is it pressed?)
	bool KeyLetterState[26];
	bool KeyNumberState[10];
public:
	//used to initialise the Input system
	Input_System();
	//used to initalise the input system with a given window state (for now)
	Input_System(SDL_Window* newWindow);

	// updates the boolean states of the input of both letters and numbers
	void Update_Input();

	// resets the input back to false (no input detected)
	void Reset_Input();

	// returns the bool of the boolean at the index of KLC
	bool GetKeyPressed(KEYLETTERCODE KLC);

	//returns the bool of the boolean at the index of KNC
	bool GetKeyPressed(KEYNUMBERCODE KNC);
};

