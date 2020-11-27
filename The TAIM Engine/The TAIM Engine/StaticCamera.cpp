#include "StaticCamera.h"

void StaticCamera::Setup() {
    CamType = CameraTypes::STATIC;
    type = ComponentType::Camera;

}

void StaticCamera::SetValues(glm::vec3 tar) {
    target = tar;
}

void StaticCamera::UpdateCamera(glm::vec2 size) {
	view = glm::lookAt(GO->transform.position, target, glm::vec3(0, 1, 0));
	proj = glm::perspective(glm::radians(zoom), size.x / size.y, 0.1f, 100.0f);
	UIProj = glm::ortho(0.0f, size.x, 0.0f, size.y, -1000.0f, 1000.0f);
}

