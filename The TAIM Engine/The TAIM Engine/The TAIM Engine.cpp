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

	//Quit SDL subsystems
	SDL_Quit();
	ES.CloseEntitySystem();
}

int The_TAIM_Engine::SetupEngine() {
	//Start up SDL and create window
	bool Success = true;

	SubSystemsList = std::vector<SubSystem*>{ &NS,&IS,&PS,&CS,&GS,&AS};


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

	GS.SR = &SR;
	NS.ES = &ES;

	FLS.GS = &GS;
	FLS.PS = &PS;
	FLS.SR = &SR;
	FLS.ES = &ES;
	FLS.AS = &AS;
	FLS.CS = &CS;


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

	if (!success)
	{
		printf("Failed to initialize!\n");
	}

	return 0;
}

int The_TAIM_Engine::StartEngine() {

	//sets up procedure for the Graphics System

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

		for (int i = 0; i < SubSystemsList.size(); i++) {
			SubSystemsList[i]->Update();
		}

		//GAME LOOP

		GameLoop();

		// ENGINE LOOP
		// in the future, the camera will be within a camera system for better control

		// these will set the matrix from the camera into a specific shader. CREATE OPTIONAL WARNINGS IF VALUES DON'T EXIST OR USE A GROUPING SYSTEM THAT DOES NEED IT

		
		//finds out the total events in the queue.
		//std::cout << Event_Queue.GetTotalEvents() << " event in the queue" << std::endl;
		
		// SYSTEM EVENT QUEUE CHECKUP
		// each system must have access to the current event queue and do it's own polling to apply the correct results.
		
		//float t1, t2, t3, t4;
		//t1 = SDL_GetTicks();
		//PS.Update(&Event_Queue);
		//t2 = SDL_GetTicks();
		//GS.Update(&Event_Queue);
		//t3 = SDL_GetTicks();
		//AS.Update(&Event_Queue);

		//std::cout << "PHYSICS: " << (t2 - t1) / 1000.0f << "Seconds. " << "GRAPHICS: " << (t3 - t2) / 1000.0f << "Seconds" << std::endl;
		
		// removes events that are not needed anymore
		Event_Queue.RemoveEmptyEvents();

		// the graphics system now begins drawing the meshes
		//GS.Draw();
		//GS.DebugDraw();
		//updates the window by double buffering.
		SDL_GL_SwapWindow(gWindow);
		//SDL_GL_

		for (int i = 0; i < SubSystemsList.size(); i++) {
			SubSystemsList[i]->LateUpdate();
		}
		
	}

	// the program has ended, begin shutting down the engine

	close();
	//delete ev;
	return 0;
}

void The_TAIM_Engine::GameLoop() {
	Event* ev = new Event();
	std::vector<Entity*> playerEntites = ES.GetEntitiesWithTag("Player");
	std::vector<Entity*> ghostEntites = ES.GetEntitiesWithTag("Ghost");
	if (IS.GetKeyPressed(KeyCode::KEY_W)) {
		ev = new MoveForward();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		//ev->ListOfEntities.push_back(&EntityList[0]);
		Event_Queue.AddEventToStack(ev);
	}
	if (IS.GetKeyPressed(KeyCode::KEY_A)) {
		ev = new MoveLeft();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue.AddEventToStack(ev);
	}
	if (IS.GetKeyPressed(KeyCode::KEY_S)) {
		ev = new MoveBackward();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue.AddEventToStack(ev);
	}
	if (IS.GetKeyPressed(KeyCode::KEY_D)) {
		ev = new MoveRight();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue.AddEventToStack(ev);
	}
	if (IS.GetKeyPressed(KeyCode::KEY_SPACE)) {
		ev = new Jump();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue.AddEventToStack(ev);
	}
	if (IS.GetKeyPressed(KeyCode::KEY_N) && !IS.GetPrevKeyPressed(KeyCode::KEY_N)) {
		ev = new PlaySoundEv();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue.AddEventToStack(ev);
	}
	if (IS.GetKeyPressed(KeyCode::KEY_TAB) && !IS.GetPrevKeyPressed(KeyCode::KEY_TAB)) {
		ev = new ResetTransform();
		ev->ListOfEntities.insert(ev->ListOfEntities.end(), playerEntites.begin(), playerEntites.end());
		Event_Queue.AddEventToStack(ev);
	}
	//if (IS.GetKeyPressed(KeyCode::KEY_Q) && !IS.GetPrevKeyPressed(KeyCode::KEY_Q)) {
	//	ev = new UpdateTransform();
	//	ev->ListOfEntities.insert(ev->ListOfEntities.end(), ghostEntites.begin(), ghostEntites.end());
	//	static_cast<UpdateTransform*>(ev)->pos = ev->ListOfEntities[0]->pos + glm::vec3(1, 0, 0);
	//	static_cast<UpdateTransform*>(ev)->rot = ev->ListOfEntities[0]->rot;
	//	Event_Queue.AddEventToStack(ev);
	//}
}

//void The_TAIM_Engine::MoveObjectAssign(Event* e) {
//
//	MoveObjectEv* moe = (MoveObjectEv*)(e);
//
//	if (moe->GetType() == EventType::MoveObject) {
//
//		glm::vec3 AddPos = glm::vec3(0);
//		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_W)) {
//			AddPos += glm::vec3(0, 0.1, 0);
//		}
//		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_A)) {
//			AddPos += glm::vec3(-0.1, 0, 0);
//		}
//		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_S)) {
//			AddPos += glm::vec3(0, -0.1, 0);
//		}
//		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_D)) {
//			AddPos += glm::vec3(0.1, 0, 0);
//		}
//		moe->ListOfEntities.push_back(&EntityList[0]);
//		moe->PositionAdd = AddPos;
//		moe->SystemList[(int)Systems::Graphics] = true;
//	}
//	else {
//		std::cout << "TYPE MISMATCH" << std::endl;
//	}
//}
//
//void The_TAIM_Engine::ResetAssign(Event* e) {
//	ResetEv* re = (ResetEv*)(e);
//
//	if (re->GetType() == EventType::Reset) {
//		if (IS.GetKeyPressed(KEYLETTERCODE::KEY_R)) {
//			re->ListOfEntities.push_back(&EntityList[0]);
//			re->SystemList[(int)Systems::Graphics] = true;
//		}
//	}
//	else {
//		std::cout << "TYPE MISMATCH" << std::endl;
//	}
//}
