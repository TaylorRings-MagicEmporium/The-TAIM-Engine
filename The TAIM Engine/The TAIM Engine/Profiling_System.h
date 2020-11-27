#pragma once


#include <glad/glad.h>
#include <SDL2\SDL.h>
#include <stdio.h>

#include <DearIMGUI/imgui.h>
#include <DearIMGUI/backends/imgui_impl_sdl.h>
#include <DearIMGUI/backends/imgui_impl_opengl3.h>
#include <string>
#include <iostream>

#include "EventQueue.h"
#include "Communication_Layer.h"

class Profiling_System
{
private:
	const char* glsl_version = "#version 130";
	SDL_Window* gWindow = NULL;
	SDL_GLContext gContext;

	bool show_demo_window = false;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	int counter = 0;

	int Player1Hit = 0;
	int Player2Hit = 0;

	std::string levelName = "ERROR";

	static Profiling_System* SingleInstance;

	EventQueue* Event_Queue;
	Communication_Layer* Comm_layer;
public:
	Profiling_System();
	void ApplySDLContext(SDL_Window* gw, SDL_GLContext gc) { gWindow = gw; gContext = gc; };
	void ApplyLayers(EventQueue* eq, Communication_Layer* cl) { Event_Queue = eq; Comm_layer = cl; };
	void Startup();
	void ShutDown();
	void Update();

	void IncrementPlayer1Hit() {Player1Hit++;};
	void IncrementPlayer2Hit() { Player2Hit++; };
	void SetLevelName(std::string name) { levelName = name; };
	static Profiling_System* GetInstance() {
		if (!SingleInstance) {
			SingleInstance = new Profiling_System;
		}
		return SingleInstance;
	}
};



