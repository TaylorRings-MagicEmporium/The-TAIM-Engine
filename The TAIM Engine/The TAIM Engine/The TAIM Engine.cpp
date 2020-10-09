// The TAIM Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

///*This source code copyrighted by Lazy Foo' Productions (2004-2020)
//and may not be redistributed without written permission.*/
//
////Using SDL, SDL OpenGL, GLEW, standard IO, and strings
//#include <SDL2\SDL.h>
//#include <glad/glad.h>
//#include <SDL2/SDL_opengl.h>
//#include <stdio.h>
//#include <string>
//#include <iostream>
//
////Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
////The window we'll be rendering to
//SDL_Window* gWindow = NULL;
//
////OpenGL context
//SDL_GLContext gContext;
//
//GLuint programID = 0;
//
//unsigned int VAO;
//unsigned int VBO;
//
//float vertices[] = {
//	-0.5,-0.5,0.0f,
//	0.5,-0.5f,0.0f,
//	0.0f,0.5,0.0f
//};
//
//
//
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(0.7f, 0.5f,0.2f, 1.0f);\n"
//"}\0";
//
//
//bool init()
//{
//	//Initialization flag
//	bool success = true;
//
//	//Initialize SDL
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
//		success = false;
//	}
//	else
//	{
//		//Use OpenGL 3.1 core
//		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
//		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//		//Create window
//		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
//		if (gWindow == NULL)
//		{
//			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
//			success = false;
//		}
//		else
//		{
//			//Create context
//			gContext = SDL_GL_CreateContext(gWindow);
//			if (gContext == NULL)
//			{
//				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
//				success = false;
//			}
//			else
//			{
//				//Initialize GLEW
//				if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
//					printf("Error initializing GLAD %s\n", glad_glGetError());
//				}
//			}
//		}
//	}
//
//	return success;
//}
//
//void close()
//{
//	//Deallocate program
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(programID);
//
//	//Destroy window	
//	SDL_DestroyWindow(gWindow);
//	gWindow = NULL;
//
//	//Quit SDL subsystems
//	SDL_Quit();
//}
//
//void SetupModel() {
//	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPLICATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER:FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	int programID = glCreateProgram();
//	glAttachShader(programID, vertexShader);
//	glAttachShader(programID, fragmentShader);
//	glLinkProgram(programID);
//
//	glGetProgramiv(programID, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(programID, 512, NULL, infoLog);
//		std::cout << "EEOR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//
//
//}
//
//int main(int argc, char* args[])
//{
//	//Start up SDL and create window
//	if (!init())
//	{
//		printf("Failed to initialize!\n");
//	}
//	else
//	{
//		//create a sample triangle, focusing on seperating it from SDL
//		SetupModel();
//
//		//Main loop flag
//		bool quit = false;
//
//		//Event handler
//		SDL_Event e;
//
//		//While application is running
//		while (!quit)
//		{
//			//Handle events on queue
//			while (SDL_PollEvent(&e) != 0)
//			{
//				//User requests quit
//				if (e.type == SDL_QUIT)
//				{
//					quit = true;
//				}
//			}
//
//			//glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
//			//glClear(GL_COLOR_BUFFER_BIT);
//
//			glUseProgram(programID);
//			glBindVertexArray(VAO);
//			glDrawArrays(GL_TRIANGLES, 0, 3);
//
//			//Update screen
//			SDL_GL_SwapWindow(gWindow);
//		}
//	}
//
//	//Free resources and close SDL
//	close();
//
//	return 0;
//}

//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
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

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Input handler
void handleKeys(unsigned char key, int x, int y);

//Per frame update
void update();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

//Graphics program
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
//GLuint gIBO = 0;
GLuint gVAO = 0;



bool init()
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


void handleKeys(unsigned char key, int x, int y)
{
	//Toggle quad
	if (key == 'q')
	{
		gRenderQuad = !gRenderQuad;
	}
}

void update()
{
	//No per frame update needed
}

void close()
{
	//Deallocate program
	glDeleteProgram(gProgramID);

	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{


		glEnable(GL_DEPTH_TEST);

		Shader basic = Shader("Shaders/BasicVertex.glsl", "Shaders/BasicFragment.glsl");
		Shader model_Loading = Shader("Shaders/model_loadingV.glsl", "Shaders/model_loadingF.glsl");
		MeshRenderer mr = MeshRenderer("Objects/duck/duck.obj",&model_Loading, false);

		Camera c = Camera();

		mr.Setup();

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
			}


			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Render quad
			c.UpdateCamera();
			c.SetProjMat(&model_Loading);
			c.SetViewMat(&model_Loading);
			glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(0.1f * SDL_GetTicks()), glm::vec3(1, 1, 1));
			model_Loading.SetMat4("model", model);
			mr.Draw();

			//Update screen
			SDL_GL_SwapWindow(gWindow);
		}

		//Disable text input
		SDL_StopTextInput();
	}

	//Free resources and close SDL
	close();

	return 0;
}