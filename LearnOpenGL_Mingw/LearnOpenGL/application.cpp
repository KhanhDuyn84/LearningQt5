#include "application.h"
#include "GLFW/glfw3.h"
#include "glslshader.h"
#include "Global.h"
#include "fps.h"
#include "model.h"
#include "loader.h"
#include <iostream>

using namespace GSEngine;

Application::Application()
{
    InitWindow();
    InitOpenGL();
    InitCallBackFunc();
    InitMember();
    glViewport(0, 0, 800, 600);
}

void Application::InitWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if(m_Window == nullptr)
    {
        std::cout<< "FAILED TO CREATE GLFW CONTEXT"<< std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_Window);
}

void Application::InitOpenGL()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<< "FAILED TO INITIALIZE GLAD" << std::endl;
    }
}

void Application::InitCallBackFunc()
{
    glfwSetFramebufferSizeCallback(m_Window, &Application::framebuffer_size_callback);
}

void Application::InitMember()
{
    float vertices [] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    triangleModel = Loader::LoadModelWithVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
    //triangleModel = Loader::LoadModelWithIndices(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));

    triangleShader = new GLSLShader(TRIANGLE_VS, TRIANGLE_FS);

    fps = new FPS();
}
void Application::Run()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(m_Window))
    {
        Render();

        fps->DoFrame();

        processInput();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Application::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    triangleShader->Use();
    glBindVertexArray(triangleModel->getVAOID());
    glDrawArrays(GL_TRIANGLES, 0 , 3);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Application::framebuffer_size_callback(GLFWwindow *window, int Width, int Height)
{
    (void)window;
    glViewport(0, 0, Width, Height);
}

void Application::processInput()
{
    if(glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_Window, true);
    }
}

Application::~Application()
{
    Loader::CleanUp();
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}
