#include "Camera3D.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
namespace mygl
{
    Camera3D::Camera3D(glm::vec3 pos, int cam_width, int cam_height, float speed, bool is_fps)
    {
        initial_pos = pos;
        position = pos;
        front = FRONT;
        width = cam_width;
        height = cam_height;
        fps = is_fps;
        world_up = WORLD_UP;
        sensitivity = SENSITIVITY;
        fov = FOV;
        pitch = PITCH;
        yaw = YAW;
        near_plane = 0.1f;
        far_plane = 1000.0f;
        movement_speed = speed;
        movement_lock = false;
        updateCameraVectors();
    }

    glm::mat4 Camera3D::getViewMatrix() const
    {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 Camera3D::getProjectionMatrix() const
    {
        return glm::perspective(glm::radians(fov), (float)width / height, near_plane, far_plane);
    }

    void Camera3D::processKeyboardMovement(Camera3D_Movement direction, double delta_time)
    {
        float velocity = movement_speed * delta_time;
        if (direction == FORWARD)
            position += front * velocity;
        if (direction == BACKWARD)
            position -= front * velocity;
        if (direction == LEFT)
            position -= right * velocity;
        if (direction == RIGHT)
            position += right * velocity;
        if (direction == UP)
            position += WORLD_UP * velocity;
        if (direction == DOWN)
            position -= WORLD_UP * velocity;
        if (fps)
            position.y = initial_pos.y;
    }

    void Camera3D::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
    {
        if (movement_lock == true)
            return;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void Camera3D::processMouseScroll(float yoffset)
    {
        // fov -= (float)yoffset;
        // if (fov < 1.0f)
        //     fov = 1.0f;
        // if (fov > 45.0f)
        //     fov = 45.0f;

        movement_speed += yoffset;
        movement_speed = glm::clamp(movement_speed, 0.0f, 300.0f);
    }

    void Camera3D::updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 nfront;
        nfront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        nfront.y = sin(glm::radians(pitch));
        nfront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(nfront);
        // also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(front, world_up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up = glm::normalize(glm::cross(right, front));
    }

    //getter and setter
    void Camera3D::setMovementSpeed(float speed)
    {
        movement_speed = speed;
    }

    void Camera3D::setNearFarPlanes(float near, float far)
    {
        near_plane = near;
        far_plane = far;
    }

    void Camera3D::setLock(bool lock)
    {
        movement_lock = lock;
    }

    std::vector<glm::vec4> Camera3D::getFrustumCornersWorldSpace()
    {
        const glm::mat4 &proj = getProjectionMatrix();
        const glm::mat4 &view = getViewMatrix();
        const auto inv = glm::inverse(proj * view);

        std::vector<glm::vec4> frustumCorners;
        for (unsigned int x = 0; x < 2; ++x)
        {
            for (unsigned int y = 0; y < 2; ++y)
            {
                for (unsigned int z = 0; z < 2; ++z)
                {
                    const glm::vec4 pt =
                        inv * glm::vec4(
                            2.0f * x - 1.0f,
                            2.0f * y - 1.0f,
                            2.0f * z - 1.0f,
                            1.0f);
                    frustumCorners.push_back(pt / pt.w);
                }
            }
        }

        return frustumCorners;
    }
}