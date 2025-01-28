#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace mygl
{
    class Scene;
    class DefaultScene;

    class Context {
        public:
            Context(int width = 1280, int height = 720, const char *name = "MYGL");
            void setCallbacks();
            void loadScene(Scene *scene);
            void loadSceneId(int id);
            void run();

            GLFWwindow *window;
            int win_width = 0;
            int win_height = 0;
            const char *win_name;
            int mouse_x = 0;
            int mouse_y = 0;

            Scene *current_scene = nullptr;
            std::vector<Scene*> scenes;

            DefaultScene *default_scene;

        private:
            GLFWwindow *createWindow();
            int loadGlad();
            static void framebufferSizeCallbackWrapper(GLFWwindow* window, int width, int height);
            static void keyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void mouseCallbackWrapper(GLFWwindow* window, double xpos, double ypos);
            static void scrollCallbackWrapper(GLFWwindow* window, double xoffset, double yoffset);
            static void leftClickCallbackWrapper(GLFWwindow* window, int button, int action, int mods);
    };
}