#pragma once
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <vector>

#include <iostream>

// the camera class hold and calulates the matrices needed to view the world through it. this technically means that multiple cameras can be set up if properly executed.
class Camera {
private:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 UIProj = glm::mat4(1.0f);

	bool IsSet = false;
public:

	float zoom = 45.0f;
	// initialises the camera
	Camera();

	//destroys the camera
	~Camera();

	// setups the camera
	void Setup();

	//gets the current projection matrix 
	glm::mat4 GetProj();

	//gets the current view matrix
	glm::mat4 GetView();

	//gets the current UI projection matrix
	glm::mat4 GetUIProj();

	// generic update of the camera using the width and height from the engine
	void UpdateCamera(int WIDTH, int HEIGHT);
};