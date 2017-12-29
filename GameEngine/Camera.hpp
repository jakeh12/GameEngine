//
//  Camera.hpp
//  GameEngine
//
//  Created by Jakub Hladik on 12/29/17.
//  Copyright © 2017 Jakub Hladik. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#pragma clang diagnostic ignored "-Wdocumentation"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma clang diagnostic pop


enum CameraPositionChangeEnum
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // euler
    float yaw;
    float pitch;
    // settings
    float speed;
    float sensitivity;
    
    void updateVectors();
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
    void processOrientation(float xOffset, float yOffset);
    void processPosition(CameraPositionChangeEnum direction, float deltaTime);
    glm::mat4 getViewMatrix();
};

#endif /* Camera_hpp */
