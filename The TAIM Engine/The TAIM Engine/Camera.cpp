#include "Camera.h"
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <vector>


#include <iostream>
Camera::Camera() {
    type = ComponentType::Camera;
}

void Camera::Setup() {
    //if (IsSet) {
    //    EM->CC->SetMonitorCam(slot, this);
    //}

}

void Camera::SetValues(glm::vec3 tar) {
    target = tar;
}

//void Camera::Update() {
//
//    glm::vec2 mousePos = EM->Input->GetCurrMousePosition();
//
//    //std::cout << " " << EM->Input->GetAnyPressedKey() << " was pressed!" << "\r" << std::endl; 
//
//    if (EM->Input->GetFirstMouse() && EM->Input->GetFirstCallback()) {
//        lastX = mousePos.x;
//        lastY = mousePos.y;
//        EM->Input->SetFirstCallback(false);
//        EM->Input->SetFirstMouse(false);
//    }
//
//    float xoffset = mousePos.x - lastX;
//    float yoffset = lastY - mousePos.y;
//    lastX = mousePos.x;
//    lastY = mousePos.y;
//
//    float sensitivity = 0.05;
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    yaw += xoffset;
//    pitch += yoffset;
//
//    if (pitch > 89.0f) {
//        pitch = 89.0f;
//    }
//    if (pitch < -89.0f) {
//        pitch = -89.0f;
//    }
//
//    glm::vec3 direction;
//    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    direction.y = sin(glm::radians(pitch));
//    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    cameraFront = glm::normalize(direction);
//
//    float cameraSpeed = 2.5f * (EM->Time->GetDeltaTime());
//
//    if (EM->Input->GetCurrKey(GLFW_KEY_W)) {
//        cameraPos += cameraSpeed * cameraFront;
//    }
//    if (EM->Input->GetCurrKey(GLFW_KEY_S)) {
//        cameraPos -= cameraSpeed * cameraFront;
//    }
//    if (EM->Input->GetCurrKey(GLFW_KEY_A)) {
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    }
//    if (EM->Input->GetCurrKey(GLFW_KEY_D)) {
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    }
//
//    zoom -= (float)EM->Input->GetCurrScrollOffset().y;
//    if (zoom <= 1.0f) {
//        zoom = 1.0f;
//    }
//    else if (zoom >= 45.0f) {
//        zoom = 45.0f;
//    }
//
//}

glm::mat4 Camera::GetProj() {
    return proj;
}
glm::mat4 Camera::GetView() {
    return view;
}
glm::mat4 Camera::GetUIProj() {
    return UIProj;
}

Camera::~Camera() {
    std::cout << "camera has been deleted!" << std::endl;
}

void Camera::UpdateCamera(glm::vec2 size) {
    view = glm::lookAt(GO->pos, target, glm::vec3(0,1,0));
    proj = glm::perspective(glm::radians(zoom), size.x / size.y, 0.1f, 100.0f);
    UIProj = glm::ortho(0.0f, size.x, 0.0f, size.y, -1000.0f, 1000.0f);
}