// The TAIM Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "The_TAIM_Engine.h"


The_TAIM_Engine::The_TAIM_Engine() {

}

The_TAIM_Engine::~The_TAIM_Engine() {

}

bool The_TAIM_Engine::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Create OpenGL context
				gContext = SDL_GL_CreateContext(gWindow);
				if (gContext == NULL)
				{
					printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}

				//initialise GLAD
				if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
					std::cout << "Failed to initialize GLAD" << std::endl;
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}
			}
		}
	}

	return success;
}


void The_TAIM_Engine::handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		gRenderQuad = !gRenderQuad;
	}
}

void The_TAIM_Engine::update()
{
	//No per frame update needed
}

void The_TAIM_Engine::close()
{
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int The_TAIM_Engine::SetupEngine() {
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}



	return 0;
}

int The_TAIM_Engine::StartEngine() {
	glEnable(GL_DEPTH_TEST);

	SR.CreateShader("basic", "Shaders/BasicVertex.glsl", "Shaders/BasicFragment.glsl"); // ENGINE NEEDED
	SR.CreateShader("model_loading", "Shaders/model_loadingV.glsl", "Shaders/model_loadingF.glsl");

	Entity duck = Entity();
	duck.SetComponent(GS.CreateMeshRenderer("Objects/duck/duck.obj", SR.GetShader("model_loading"), false));

	
	Camera c = Camera();

	GS.Setup();

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Enable text input
	SDL_StartTextInput();

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				Event ev = Event();
				switch (e.key.keysym.sym) {
				case SDLK_a:
					std::cout << "EVENT MADE" << std::endl;
					ev.type = EventType::MoveLeft;
					ev.SystemList[(int)Systems::Graphics] = true;
					ev.ListOfEntities.push_back(&duck);
					Event_Queue.AddEventToStack(ev);
					break;
				
				case SDLK_d:
					std::cout << "EVENT MADE" << std::endl;
					ev.type = EventType::MoveRight;
					ev.SystemList[(int)Systems::Graphics] = true;
					ev.ListOfEntities.push_back(&duck);
					Event_Queue.AddEventToStack(ev);
					break;
				}
			}
		}

		GS.ResetGraphics();

		//SYSTEM LOOP
		

		//Render quad
		c.UpdateCamera(SCREEN_WIDTH, SCREEN_HEIGHT);
		
		SR.GetShader("model_loading")->SetMat4("Proj", c.GetProj());
		SR.GetShader("model_loading")->SetMat4("View", c.GetView());
		
		GS.Update(Event_Queue);

		glm::mat4 model = glm::translate(glm::mat4(1.0), duck.pos);
		SR.GetShader("model_loading")->SetMat4("model", model);
		GS.Draw();

		//Update screen
		SDL_GL_SwapWindow(gWindow);
	}
		//Disable text input
		SDL_StopTextInput();
	

	//Free resources and close SDL
	close();

	return 0;
}
