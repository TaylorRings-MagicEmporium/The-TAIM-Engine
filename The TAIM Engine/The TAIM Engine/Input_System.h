#pragma once
#include <SDL2\SDL.h>
#include "SubSystem.h"
#include "Entity_System.h"

// KEYLETTERCODE contains all of the letters of the alphabet
enum class KEYLETTERCODE {KEY_A,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F,KEY_G,
KEY_H,KEY_I,KEY_J,KEY_K,KEY_L,KEY_M,KEY_N,KEY_O,KEY_P,
KEY_Q,KEY_R,KEY_S,KEY_T,KEY_U,KEY_V,KEY_W,KEY_X,KEY_Y,KEY_Z};

// KEYNUMBERCODE contains all of the numbers from 0 to 9
enum class KEYNUMBERCODE {KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0};

enum class KEYSPECIALCODE {KEY_RETURN,KEY_ESCAPE,KEY_BACKSPACE,KEY_TAB,KEY_SPACE,KEY_MINUS,KEY_EQUALS,
KEY_LEFTBRACKET,KEY_RIGHTBRACKET,KEY_BACKSLASH,KEY_NONUSHASH,KEY_SEMICOLON,KEY_APOSTROPHE,KEY_GRAVE,
KEY_COMMA,KEY_PERIOD,KEY_SLASH,KEY_CAPSLOCK};

enum class KeyCode {
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
	KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
	KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,

	KEY_RETURN, KEY_ESCAPE, KEY_BACKSPACE, KEY_TAB, KEY_SPACE, KEY_MINUS, KEY_EQUALS,
	KEY_LEFTBRACKET, KEY_RIGHTBRACKET, KEY_BACKSLASH, KEY_NONUSHASH, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_GRAVE,
	KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_CAPSLOCK
};
// the input system is responsible for how the user will interact with the world. it is also considered the first step in event building.
// to keep the abstraction between the window's inputs and gameplay functionality, the input system has it's own keycode for the gameplay to use.
class Input_System : public SubSystem
{

private:
	SDL_Window* Window;

	// an array holds the boolean state of the keypresses (is it pressed?)
	bool KeyCodeState[54];
	bool PrevKeyCodeState[54];

	bool KeyLetterState[26];
	bool KeyNumberState[10];
	bool KeySpecialState[18];

	bool PrevKeyLetterState[26];
	bool PrevKeyNumberState[10];
	bool PrevKeySpecialState[18];

	// the decision to split all keys into three sections is that it's impossible to create a fixed
	//system. for example GLFW's SPACE key is 32, while SDL2's SPACE key is on 44. in the future, EACH key could
	//be manually tested, meaning that just one enum is needed, and simplify some processes (event-key binding)


public:
	Entity_System* ES;

	//used to initialise the Input system
	//used to initalise the input system with a given window state (for now)
	Input_System();

	// updates the boolean states of the input of both letters and numbers
	void Update();

	// resets the input back to false (no input detected)
	void Reset_Input();

	void AssignWindows(SDL_Window* newWindow);
	void CreateEvents();
	// returns the bool of the state at the current frame

	bool GetKeyPressed(KeyCode KC);
	bool GetPrevKeyPressed(KeyCode KC);
};

