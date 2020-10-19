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


	// (in file) "basic" is the engine's own shader in the case that no shader specified is found. MAKE INTO CODE INSTEAD
	SR.CreateShader("basic", "Shaders/BasicVertex.glsl", "Shaders/BasicFragment.glsl"); // ENGINE NEEDED
	SR.CreateShader("model_loading", "Shaders/model_loadingV.glsl", "Shaders/model_loadingF.glsl");

	// creates a temp entity and adds it to the entity list.
	Entity duck = Entity();
	duck.SetComponent(GS.CreateMeshRenderer("Objects/duck/duck.obj", SR.GetShader("model_loading"), false));
	EntityList.push_back(duck);
	
	Camera c = Camera();

	//sets up procedure for the Graphics System
	GS.Setup();
	PS.Setup();

	//used to exit the loop if needed
	bool quit = false;

	//used for polling the SDL events
	SDL_Event e;

	// the main game loop of the program
	while (!quit)
	{
		// for each event on SDL_queue
		while (SDL_PollEvent(&e) != 0)
		{
			// if the user closes the current window...
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}



		//resets the graphical frame in the windows
		GS.ResetGraphics();

		// updates the keystates using the results of the Window
		IS.Update_Input();



		//GAMEPLAY LOOP (events go here for now)
		//these four if statements are used to test the power of the events and event queues.


		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_W) || IS.GetKeyPressed(KEYLETTERCODE::KEY_A) || IS.GetKeyPressed(KEYLETTERCODE::KEY_S) || IS.GetKeyPressed(KEYLETTERCODE::KEY_D)) {
			MoveObjectEv* ev = new MoveObjectEv();
			MoveObjectAssign((Event*)ev);
			Event_Queue.AddEventToStack((Event*)ev);
		}

		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_R)) {
			ResetEv* re = new ResetEv();
			ResetAssign((Event*)re);
			Event_Queue.AddEventToStack((Event*)re);
		}


		// ENGINE LOOP
		// in the future, the camera will be within a camera system for better control
		c.UpdateCamera(SCREEN_WIDTH, SCREEN_HEIGHT);
		
		// these will set the matrix from the camera into a specific shader. CREATE OPTIONAL WARNINGS IF VALUES DON'T EXIST OR USE A GROUPING SYSTEM THAT DOES NEED IT
		SR.GetShader("model_loading")->SetMat4("Proj", c.GetProj());
		SR.GetShader("model_loading")->SetMat4("View", c.GetView());
		

		//finds out the total events in the queue.
		//std::cout << Event_Queue.GetTotalEvents() << " event in the queue" << std::endl;
		
		// SYSTEM EVENT QUEUE CHECKUP
		// each system must have access to the current event queue and do it's own polling to apply the correct results.
		PS.Update(&Event_Queue);
		GS.Update(&Event_Queue);

		// removes events that are not needed anymore
		Event_Queue.RemoveEmptyEvents();


		// used for the simple showing of the event system
		glm::mat4 model = glm::translate(glm::mat4(1.0), EntityList[0].pos + EntityList[0].PosChange);
		SR.GetShader("model_loading")->SetMat4("model", model);

		// the graphics system now begins drawing the meshes
		GS.Draw();

		//updates the window by double buffering.
		SDL_GL_SwapWindow(gWindow);
	}

	// the program has ended, begin shutting down the engine
	close();

	return 0;
}

void The_TAIM_Engine::MoveObjectAssign(Event* e) {

	MoveObjectEv* moe = (MoveObjectEv*)(e);

	if (moe->GetType() == EventType::MoveObject) {

		glm::vec3 AddPos = glm::vec3(0);
		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_W)) {
			AddPos += glm::vec3(0, 0.1, 0);
		}
		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_A)) {
			AddPos += glm::vec3(-0.1, 0, 0);
		}
		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_S)) {
			AddPos += glm::vec3(0, -0.1, 0);
		}
		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_D)) {
			AddPos += glm::vec3(0.1, 0, 0);
		}
		moe->ListOfEntities.push_back(&EntityList[0]);
		moe->PositionAdd = AddPos;
		moe->SystemList[(int)Systems::Graphics] = true;
	}
	else {
		std::cout << "TYPE MISMATCH" << std::endl;
	}
}

void The_TAIM_Engine::ResetAssign(Event* e) {
	ResetEv* re = (ResetEv*)(e);

	if (re->GetType() == EventType::Reset) {
		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_R)) {
			re->ListOfEntities.push_back(&EntityList[0]);
			re->SystemList[(int)Systems::Graphics] = true;
		}
	}
	else {
		std::cout << "TYPE MISMATCH" << std::endl;
	}
}
