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

Camera::~Camera() {
    std::cout << "camera has been deleted!" << std::endl;
}
