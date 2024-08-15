#pragma once

#include <GLFW/glfw3.h>

namespace mygl 
{
    class Clock
    {
        public:
            double current_time = 0.0f;
            float delta_time = 0.0f;
            float last_frame = 0.0f;

            Clock() { update(); };

            void update() {
                current_time = glfwGetTime();
                delta_time = current_time - last_frame;
                last_frame = current_time;
            };

            void reset() {
                current_time = glfwGetTime();
                delta_time = current_time - last_frame;
                last_frame = current_time;
            }
    };
}