#pragma once


#include <SDL2\SDL.h>
#include <glad/glad.h>
#include <SDL2\SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Shader.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Entity.h"

#include "Event.h"
#include "EventQueue.h"

#include "ShaderRegistry.h"
#include "Graphics_System.h"
#include "Input_System.h"

class The_TAIM_Engine {
	SDL_Window* gWindow = NULL;
	SDL_GLContext gContext;
	bool gRenderQuad = true;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	ShaderRegistry SR = ShaderRegistry();
	Graphics_System GS = Graphics_System(100);
	EventQueue Event_Queue = EventQueue();
	Input_System IS;

public:
	The_TAIM_Engine();
	~The_TAIM_Engine();
	bool init();
	void handleKeys(unsigned char keys, int x, int y);
	void update();
	void close();

	int SetupEngine();
	int StartEngine();

};