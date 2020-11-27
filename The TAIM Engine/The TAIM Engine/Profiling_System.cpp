#include "Profiling_System.h"

Profiling_System* Profiling_System::SingleInstance = 0;

Profiling_System::Profiling_System()
{
}

void Profiling_System::Startup()
{
	//DEARIMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(gWindow, gContext);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void Profiling_System::ShutDown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void Profiling_System::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(gWindow);
	ImGui::NewFrame();

	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}

	{


		ImGui::Begin("The TAIM Profiler");
		ImGui::Text("useful level of the program:");
		//ImGui::Checkbox("Demo Window", &show_demo_window);
		ImGui::Checkbox("Instructions", &show_another_window);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		//ImGui::ColorEdit3("clear color", (float*)&clear_color);

		if (Comm_layer->CanChangeLevel) {
			if (ImGui::Button("Level 1")) {
				std::cout << "level 1 selected" << std::endl;
				Event* ev = new ChangeLevel();
				ChangeLevel* l = (ChangeLevel*)(ev);
				l->level = 0;
				ev->SubSystemOrder.push_back(SubSystemType::System);
				ev->SubSystemOrder.push_back(SubSystemType::Network);
				Event_Queue->AddEventToStack(ev);
			}
			ImGui::SameLine();
			if (ImGui::Button("Level 2")) {
				std::cout << "level 2 selected" << std::endl;
				Event* ev = new ChangeLevel();
				ChangeLevel* l = (ChangeLevel*)(ev);
				l->level = 1;
				ev->SubSystemOrder.push_back(SubSystemType::System);
				ev->SubSystemOrder.push_back(SubSystemType::Network);
				Event_Queue->AddEventToStack(ev);
			}
		}



		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		ImGui::Text("Level name: %s", levelName.c_str());

		ImGui::Text("Player 1 Hits: %d", Player1Hit);
		ImGui::Text("Player 2 Hits: %d", Player2Hit);
		ImGui::Text("");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}

	if (show_another_window) {
		ImGui::Begin("Instructions", &show_another_window);
		ImGui::Text("HELLO! instructions for the game for both singleplayer and multiplayer");
		ImGui::Text("W, A, S, D : moving the duck on the x and z axis.");
		ImGui::Text("Space: make the duck jump!");
		ImGui::Text("Enter: to shoot. WARNING: loud noise... sorry.");
		ImGui::Text("buttons will be displayed to switch levels, but only in single player, or you are the first client to connect.");
		ImGui::Text("to reset a level, just press the Level Button.");
		if (ImGui::Button("Close Me")) {
			show_another_window = false;
		}
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
