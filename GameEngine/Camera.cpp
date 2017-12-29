//
//  Camera.cpp
//  GameEngine
//
//  Created by Jakub Hladik on 12/29/17.
//  Copyright © 2017 Jakub Hladik. All rights reserved.
//

#include "Camera.hpp"
#include <iostream>

Camera::Camera(glm::vec3 aPosition, glm::vec3 aUp, float aYaw, float aPitch) : forward(glm::vec3(0.0f, 0.0f, -1.0f)), speed(2.5f), sensitivity(0.2f)
{
    position = aPosition;
    worldUp = aUp;
    yaw = aYaw;
    pitch = aPitch;
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

void Camera::processOrientation(float xOffset, float yOffset)
{
    yaw   += xOffset * sensitivity;
    pitch += yOffset * sensitivity;
    
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    updateVectors();
}

void Camera::processPosition(CameraPositionChangeEnum direction, float deltaTime)
{
    float velocity = speed * deltaTime;
    if (direction == FORWARD)
        position += forward * velocity;
    if (direction == BACKWARD)
        position -= forward * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + forward, up);
}
