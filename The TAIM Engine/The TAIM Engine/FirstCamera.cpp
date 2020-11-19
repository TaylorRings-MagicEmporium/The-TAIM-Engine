#include "FirstCamera.h"

void FirstCamera::SetOffset(glm::vec3 off) {
	Offset = off;
	type = ComponentType::Camera;

}
void FirstCamera::Setup() {
	CamType = CameraTypes::FIRST;
}
void FirstCamera::UpdateCamera(glm::vec2 size) {
	//view = glm::lookAt(GO->pos, target, glm::vec3(0, 1, 0));
	//view = glm::translate(glm::mat4(1), GO->pos + Offset);
	view *= glm::toMat4(GO->rot);
	view = glm::lookAt(GO->pos + (Offset*GO->rot), GO->pos + (Offset + glm::vec3(0,0,-1)) * GO->rot,glm::vec3(0,1,0));
	proj = glm::perspective(glm::radians(zoom), size.x / size.y, 0.1f, 100.0f);
	UIProj = glm::ortho(0.0f, size.x, 0.0f, size.y, -1000.0f, 1000.0f);
}