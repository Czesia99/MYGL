#pragma once

#include "ICamera.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>


namespace mygl
{
    enum Camera3D_Movement  {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    const float YAW             =  -90.0f;
    const float PITCH           =  0.0f;
    const float SENSITIVITY     =  0.1f;
    const float FOV             =  45.0f;
    const glm::vec3 DEFAULT_POS = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 FRONT       =  glm::vec3(0.0f, 0.0f, -1.0f);
    const glm::vec3 WORLD_UP    =  glm::vec3(0.0f, 1.0f, 0.0f);

    class Camera3D : public ICamera {
        public:
            Camera3D(glm::vec3 pos = DEFAULT_POS, int cam_width = 1980, int cam_height = 1080, float speed = 2.5f, bool is_fps = false);
            glm::mat4 getViewMatrix() const;
            glm::mat4 getProjectionMatrix() const;
            void processKeyboardMovement(Camera3D_Movement direction, double delta_time);
            void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
            void processMouseScroll(float yoffset);

            void setMovementSpeed(float speed);
            void setNearFarPlanes(float near_plane, float far_plane);
            void setLock(bool lock);

            std::vector<glm::vec4> getFrustumCornersWorldSpace();
            void updateCameraVectors();
        public:
            glm::vec3 position;
            glm::vec3 initial_pos;
            glm::vec3 front;
            glm::vec3 up;
            glm::vec3 right;
            glm::vec3 world_up;

            float yaw;
            float pitch;
            float movement_speed;
            float sensitivity;
            float fov;

            float near_plane;
            float far_plane;

            int width;
            int height;

            bool fps;

            bool movement_lock;

        private:

    };
}