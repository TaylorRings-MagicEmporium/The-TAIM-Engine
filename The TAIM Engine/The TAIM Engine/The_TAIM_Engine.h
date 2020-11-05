
// The TAIM Engine : the main engine core that keeps track of the event queue, systems and objects.
// there should only be one engine operating in the program.
// the engine should be able to control everything it needs to do itself.

#pragma once
// WINDOWS INCLUDES
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>

// GLAD (OpenGL Wrapper) INCLUDES
#include <glad/glad.h>

// GLM INCLUDES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GENERIC INCLUDES
#include <stdio.h>
#include <string>
#include <iostream>

// CUSTOM INCLUDE
#include "Shader.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Entity_System.h"
#include "Event.h"
#include "ShaderRegistry.h"
#include "Graphics_System.h"
#include "Physics_System.h"
#include "Input_System.h"
#include "Communication_Layer.h"
#include "FileLoader_System.h"

#include <fmod_studio.hpp>
#include <fmod.hpp>


class The_TAIM_Engine {

	//used for window setup
	SDL_Window* gWindow = NULL;
	SDL_GLContext gContext;

	// general values for the size of the screen
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;
	int ComponentSize = 100;
	std::string ProgramName = "SDL tutorial";

	//CHANGE
	
	ShaderRegistry SR = ShaderRegistry();
	Graphics_System GS = Graphics_System(100);
	Physics_System PS = Physics_System(100);
	EventQueue Event_Queue = EventQueue();
	Input_System IS;
	Communication_Layer CL = Communication_Layer();
	FileLoader_System FLS = FileLoader_System();
	Entity_System ES = Entity_System();

	FMOD::Studio::System* system = NULL;
	FMOD::System* lowLevelSystem = NULL;

public:
	// used for engine initialisation. 
	The_TAIM_Engine();

	//used for engine destruction
	~The_TAIM_Engine();

	// close() is used for the close procedure of the engine and the last function to be called by the engine.
	// it also tells the systems to close and delete anything that needs deleting.
	// finally, it can be used for the final file editing of the program.
	void close();

	// the init function makes sure that each of the system's initialisation processes are running correctly and smoothly.
	// this will also be the first call for action if any of the systems are not set up correctly.
	bool init();


	// the SetupEngine is a function that only the Main.cpp can call
	int SetupEngine();

	// the main function of the engine, the start engine will control the overall lifetime of the program
	int StartEngine();

	//void MoveObjectAssign(Event* e);
	//void ResetAssign(Event* e);

};