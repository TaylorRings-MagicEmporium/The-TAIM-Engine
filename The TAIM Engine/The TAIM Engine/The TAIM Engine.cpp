#include "The_TAIM_Engine.h"

The_TAIM_Engine::The_TAIM_Engine() {

}


The_TAIM_Engine::~The_TAIM_Engine() {

}

void The_TAIM_Engine::close()
{
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	for (int i = 0; i < SubSystemsList.size(); i++) {
		SubSystemsList[i]->ShutDown();
	}
	Profiling_System::GetInstance()->ShutDown();
	//Quit SDL subsystems
	SDL_Quit();
	ES.CloseEntitySystem();
}

int The_TAIM_Engine::SetupEngine() {
	//Start up SDL and create window
	bool Success = true;

	SubSystemsList = std::vector<SubSystem*>{ &NS,&IS,&PS,&AnS,&ES,&CS,&GS,&AS};


	//Initialization flag
	bool success = true;

	std::cout << "LOADING CONFIG FILE" << std::endl;
	ConfigData CD = FLS.LoadConfig();

	if (CD.FileLoaded) {
		SCREEN_WIDTH = CD.ScreenSize.x;
		SCREEN_HEIGHT = CD.ScreenSize.y;
		ProgramName = CD.WindowName;
	}

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
		gWindow = SDL_CreateWindow(ProgramName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
					success = false;
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

			}
		}
	}


	CS.SetWindowSize(CD.ScreenSize);
	Profiling_System::GetInstance()->ApplySDLContext(gWindow, gContext);
	GS.SR = &SR;

	NS.ES = &ES;
	IS.ES = &ES;

	FLS.GS = &GS;
	FLS.PS = &PS;
	FLS.SR = &SR;
	FLS.ES = &ES;
	FLS.AS = &AS;
	FLS.CS = &CS;
	FLS.AnS = &AnS;


	for (int i = 0; i < SubSystemsList.size(); i++) {
		SubSystemsList[i]->SetComponentSize(100);
	}

	// (in file) "basic" is the engine's own shader in the case that no shader specified is found. MAKE INTO CODE INSTEAD
	SR.CreateShader("basic", "Shaders/BasicVertex.glsl", "Shaders/BasicFragment.glsl"); // ENGINE NEEDED
	SR.CreateShader("model_loading", "Shaders/model_loadingV.glsl", "Shaders/model_loadingF.glsl");
	SR.CreateShader("DebugLine", "Shaders/DebugLineVertex.glsl", "Shaders/DebugLineFragment.glsl");

	FLS.LoadEntities();

	for (int i = 0; i < SubSystemsList.size(); i++) {
		SubSystemsList[i]->AssignLayers(&Event_Queue, &CL);
		SubSystemsList[i]->Startup();
	}
	Profiling_System::GetInstance()->Startup();

	if (!success)
	{
		printf("Failed to initialize!\n");
	}

	return 0;
}

int The_TAIM_Engine::StartEngine() {



	//used to exit the loop if needed
	bool quit = false;

	//used for polling the SDL events
	SDL_Event e;

	// the main game loop of the program
	int count = 0;
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

		CL.ResetBuffers();

		SR.GetShader("model_loading")->Use();
		SR.GetShader("model_loading")->SetMat4("Proj", CL.proj);
		SR.GetShader("model_loading")->SetMat4("View", CL.view);
		SR.GetShader("basic")->Use();
		SR.GetShader("basic")->SetMat4("Proj", CL.proj);
		SR.GetShader("basic")->SetMat4("View", CL.view);
		SR.GetShader("DebugLine")->Use();
		SR.GetShader("DebugLine")->SetMat4("Proj", CL.proj);
		SR.GetShader("DebugLine")->SetMat4("View", CL.view);

		// ENGINE LOOP
		// in the future, the camera will be within a camera system for better control

		std::vector<float> timeList;

		for (int i = 0; i < SubSystemsList.size(); i++) {
			timeList.push_back(SDL_GetTicks());
			SubSystemsList[i]->Update();
		}
		Profiling_System::GetInstance()->Update();

		//std::cout << "PHYSICS: " << (t2 - t1) / 1000.0f << "Seconds. " << "GRAPHICS: " << (t3 - t2) / 1000.0f << "Seconds" << std::endl;


		//finds out the total events in the queue.
		//std::cout << Event_Queue.GetTotalEvents() << " event in the queue" << std::endl;
			
		typedef void (The_TAIM_Engine::* method_function)(Event*);
		method_function method_pointer[EVENT_TYPE_COUNT];
		method_pointer[(int)EventType::ResetAllSystems] = &The_TAIM_Engine::ResetSystems;

		while (Event* e = Event_Queue.PollEvents(SubSystemType::System)) {
			method_function func = method_pointer[(int)e->GetType()];
			(this->*func)(e);
		}

		// removes events that are not needed anymore
		Event_Queue.RemoveEmptyEvents();

		//updates the window by double buffering.

		//SDL_GL_

		for (int i = 0; i < SubSystemsList.size(); i++) {
			SubSystemsList[i]->LateUpdate();
		}


		

		SDL_GL_SwapWindow(gWindow);
	}




	close();
	//delete ev;
	return 0;
}


void The_TAIM_Engine::ResetSystems(Event* e)
{
	for (int i = 0; i < SubSystemsList.size(); i++) {
		SubSystemsList[i]->ResetSystem();
	}
	FLS.SwapFile();
	FLS.LoadEntities();

	for (int i = 0; i < SubSystemsList.size(); i++) {
		SubSystemsList[i]->SyncComponentsToSystem();
	}
}

