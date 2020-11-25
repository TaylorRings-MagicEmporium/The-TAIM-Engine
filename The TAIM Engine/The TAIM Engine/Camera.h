#pragma once
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Component.h"
#include <iostream>


enum class CameraTypes { FIRST, THIRD, STATIC, FREEFORM };

// the camera class hold and calulates the matrices needed to view the world through it. this technically means that multiple cameras can be set up if properly executed.
class Camera : public Component {
protected:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 UIProj = glm::mat4(1.0f);

	bool IsSet = false;
	CameraTypes CamType;
public:

	float zoom = 45.0f;
	// initialises the camera
	Camera();

	//destroys the camera
	~Camera();

	// setups the camera
	virtual void Setup() = 0;
	
	// generic update of the camera using the width and height from the engine
	virtual void UpdateCamera(glm::vec2 size) = 0;


	//gets the current projection matrix 
	glm::mat4 GetProj() { return proj; };

	//gets the current view matrix
	glm::mat4 GetView() { return view; };

	//gets the current UI projection matrix
	glm::mat4 GetUIProj() { return UIProj;};

	CameraTypes GetCamType() { return CamType; };

};