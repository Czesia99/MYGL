#include "Scene.hpp"
#include "Context.hpp"
#include "Shape.hpp"
#include "Texture.hpp"
#include "stb_image.h"

namespace mygl
{
    DefaultScene::DefaultScene(Context &ctx) : Scene(ctx)
    {
        cube_shader = Shader("default_cube.vs", "default_cube.fs");
        cube.transform.position.z += 10.0;
    }

    void DefaultScene::storeSceneInCtx()
    {
        ctx.scenes.push_back(this);
    }

    void DefaultScene::openScene()
    {
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(ctx.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void DefaultScene::closeScene()
    {
        return;
    }

    void DefaultScene::update()
    {
        clock.update();

        sky.render(camera);
        cube.render(cube_shader, camera);
    }

    void DefaultScene::sceneClear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void DefaultScene::processInput()
    {
        if (glfwGetKey(ctx.window, GLFW_KEY_W) == GLFW_PRESS)
            camera.processKeyboardMovement(FORWARD, clock.delta_time);
        if (glfwGetKey(ctx.window, GLFW_KEY_S) == GLFW_PRESS)
            camera.processKeyboardMovement(BACKWARD, clock.delta_time);
        if (glfwGetKey(ctx.window, GLFW_KEY_A) == GLFW_PRESS)
            camera.processKeyboardMovement(LEFT, clock.delta_time);
        if (glfwGetKey(ctx.window, GLFW_KEY_D) == GLFW_PRESS)
            camera.processKeyboardMovement(RIGHT, clock.delta_time);
    }

    void DefaultScene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(ctx.window, true);
        }
    }

    void DefaultScene::mouseCallback(GLFWwindow* window, int x, int y, float dx, float dy)
    {
        camera.processMouseMovement((float)dx, (float)-dy);
    }

    void DefaultScene::leftClickCallback(GLFWwindow* window, int button, int action, int mods)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "xpos = " << xpos << std::endl;
        std::cout << "ypos = " << ypos << std::endl;
    }

    void DefaultScene::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        camera.processMouseScroll(static_cast<float>(yoffset));
    }

    void DefaultScene::framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        camera.width = width;
        camera.height = height;
    }
}