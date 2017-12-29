//
//  Camera.cpp
//  GameEngine
//
//  Created by Jakub Hladik on 12/29/17.
//  Copyright © 2017 Jakub Hladik. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : forward(glm::vec3(0.0f, 0.0f, -1.0f)), speed(2.5f), sensitivity(0.1f)
{
        position = position;
        worldUp = up;
        yaw = yaw;
        pitch = pitch;
        updateVectors();
}

void Camera::updateVectors()
{
    glm::vec3 recalculatedForward;
    recalculatedForward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    recalculatedForward.y = sin(glm::radians(pitch));
    recalculatedForward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(recalculatedForward);
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::normalize(glm::cross(right, forward));
}
