#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "ICamera.hpp"

namespace mygl
{
    class CameraOrtho : public ICamera {
        public:
            CameraOrtho(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), int win_width = 800, int win_height = 600);
            glm::mat4 getViewMatrix() const;
            glm::mat4 getProjectionMatrix() const;
            void processMouseScroll(float yoffset);

        public:
            glm::vec3 position;
            glm::vec3 front;
            glm::vec3 up;
            glm::vec3 right;
            glm::vec3 world_up;

            float yaw;
            float pitch;

            float movement_speed;
            float mouse_sensitivity;
            float fov;

            float width;
            float height;

            bool fps;

        private:
            void updateCameraVectors();
    };
}