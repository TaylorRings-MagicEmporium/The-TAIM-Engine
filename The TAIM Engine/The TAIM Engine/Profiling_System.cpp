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
		//ImGui::Checkbox("Another Window", &show_another_window);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		//ImGui::ColorEdit3("clear color", (float*)&clear_color);

		//if (ImGui::Button("Button")) {
		//	counter++;
		//}
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		ImGui::Text("Level name: %s", levelName.c_str());

		ImGui::Text("Player 1 Hits: %d", Player1Hit);
		ImGui::Text("Player 2 Hits: %d", Player2Hit);
		ImGui::Text("");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}

	//if (show_another_window) {
	//	ImGui::Begin("Another Window", &show_another_window);
	//	ImGui::Text("Hello from another window!");
	//	if (ImGui::Button("Close Me")) {
	//		show_another_window = false;
	//	}
	//	ImGui::End();
	//}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
