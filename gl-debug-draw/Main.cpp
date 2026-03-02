#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "DebugDraw.h"
#include <glm/glm.hpp>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
   
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL 3.3 Test", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    DebugDraw::Init();
   
    glViewport(0, 0, 800, 600);

  
    glm::mat4 viewProj = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window))
    {
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        DebugDraw::BeginFrame();
        DebugDraw::DrawLine(
            { -0.5f, 0.0f, 0.0f },
            { 0.5f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f }
        );

        DebugDraw::EndFrame(viewProj);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    DebugDraw::Shutdown();

    glfwTerminate();
    return 0;
}