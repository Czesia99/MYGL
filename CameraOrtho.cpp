#include "CameraOrtho.hpp"

namespace mygl
{
    CameraOrtho::CameraOrtho(glm::vec3 position, float win_width, float win_height)
    : front(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        position = position;
        width = win_width;
        height = win_height;
        movement_speed = 2.5f;
        mouse_sensitivity = 0.1f;
        world_up = glm::vec3(0.0f, 1.0f, 0.0f);

        updateCameraVectors();
    }

    glm::mat4 CameraOrtho::getViewMatrix() const
    {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 CameraOrtho::getProjectionMatrix() const
    {
        return glm::ortho(0.0f, width, 0.0f, height, -0.1f, 100.0f);
    }

    void CameraOrtho::processMouseScroll(float yoffset)
    {
        fov -= (float)yoffset;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;
    }

    void CameraOrtho::updateCameraVectors()
    {
        right = glm::normalize(glm::cross(front, world_up));
        up = glm::normalize(glm::cross(right, front));
    }
}