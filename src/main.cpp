#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream> 
#include <chrono>

#include "Game/Game.h"
#include "Resources/ResourcMenager.h"
#include "Renderer/Renderer.h"

glm::ivec2 g_windowSize(13 * 16, 14 * 16);
//обернуто в уник поинтр для правильной выгрузки ресурсов
std::unique_ptr<Game> g_game = std::make_unique<Game>(g_windowSize);


void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSize.x = width;
    g_windowSize.y = height;

    //временно для недопузения искажений объектов игры при изменении размера окна
    const float map_aspect_ratio = 13.f / 14.f;
    unsigned int viewPortWidth = g_windowSize.x;
    unsigned int viewPortheight = g_windowSize.y;
    unsigned int viewportLeftOffset = 0;
    unsigned int viewportBottomOffset = 0;
    if (static_cast<float>(g_windowSize.x) / g_windowSize.y > map_aspect_ratio)
    {
        viewPortWidth = static_cast<unsigned int>(g_windowSize.y * map_aspect_ratio);
        viewportLeftOffset = (g_windowSize.x - viewPortheight) / 2;
    }
    else
    {
        viewPortheight = static_cast<unsigned int>(g_windowSize.x / map_aspect_ratio);
        viewportBottomOffset = (g_windowSize.y - viewPortWidth) / 2;
    }

    RenderEngine::Renderer::setVieport(viewPortWidth, viewPortheight, viewportLeftOffset, viewportBottomOffset);
   // glViewport(0, 0, width, height);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    g_game->setKey(key, action);
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru");

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    //подкдючение glad
    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
        //return -1;
    }
    std::cout << "Renderer: " << RenderEngine::Renderer::getRendererStr() << std::endl;
    std::cout << "OpenGL version: " << RenderEngine::Renderer::getVersionStr() << std::endl;
    

    RenderEngine::Renderer::setClearColor(0, 0, 0, 1);
   // glClearColor(0, 0, 0, 1);

    {
        ResourceMenager::setExecutablePath(argv[0]);
        g_game->init(); 
        //запись текущего времени
        auto lastTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            //запись времени кадра
            auto currentTime = std::chrono::high_resolution_clock::now();
            // разница времени
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
                lastTime = currentTime;
              g_game->update(duration);
               
            
            /* Render here */
            RenderEngine::Renderer::clear();
            //glClear(GL_COLOR_BUFFER_BIT);
         
            g_game->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
        g_game = nullptr;
        ResourceMenager::unLoadAllResources();
    }

    glfwTerminate();
    return 0;
}