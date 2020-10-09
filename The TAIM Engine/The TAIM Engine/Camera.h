#pragma once
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
//#include "stb_image.h"
//#include "EngineModules.h"
#include <vector>

#include <iostream>

// the camera creates an object that creates the matrices needed to view the world through it. this technically means that multiple cameras can be set up \
if properly executed.
class Camera {
private:
	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 20.0f);
	//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj;
	glm::mat4 UIProj;

	bool IsSet = false;
	//Slots slot;
public:

	float zoom = 45.0f;
	Camera();
	//Camera(Slots slot);

	~Camera();

	void Setup();

	void Update();

	void SetViewMat(Shader *shader);
	void SetProjMat(Shader *shader);

	glm::mat4 GetProj();
	glm::mat4 GetView();
	glm::mat4 GetUIProj();

	void UpdateCamera();
};