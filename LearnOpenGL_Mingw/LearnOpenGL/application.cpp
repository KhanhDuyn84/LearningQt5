#include "application.h"
#include <iostream>
#include <windows.h>
#include "GLFW/glfw3.h"
#include "glslshader.h"
#include "Global.h"
#include "fps.h"
#include "model.h"
#include "loader.h"
#include "SOIL2/SOIL2.h"
#include "texture.h"
#include "filehelper.h"
#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "lightobj.h"
#include "containerobj.h"


float Application::lastX = SCR_WIDTH / 2;
float Application::lastY = SCR_HEIGHT / 2;
bool Application::isFirstMouse = true;
GSEngine::Camera* Application::m_Camera = nullptr;
using namespace GSEngine;

Application::Application()
{
    InitWindow();
    InitOpenGL();
    InitIcon();
    InitCallBackFunc();
    InitMember();
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void Application::InitWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    m_Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, TITLE_WINDOW, nullptr, nullptr);
    if(m_Window == nullptr)
    {
        std::cout<< "FAILED TO CREATE GLFW CONTEXT"<< std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *modes = glfwGetVideoMode(primaryMonitor);
    glfwSetWindowPos(m_Window, modes->width/2 - SCR_WIDTH/2, modes->height/2 - SCR_HEIGHT/2);
    //glfwSetWindowOpacity(m_Window, 0.7f);
}

void Application::InitOpenGL()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<< "FAILED TO INITIALIZE GLAD" << std::endl;
    }
}

void Application::InitIcon()
{
    GLFWimage icon;
    int width, height, channels;
    std::string imagePath = FileHelper::getInstance()->getPath("IMAGE_ICON");
    icon.pixels = SOIL_load_image(imagePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
    if(icon.pixels != nullptr)
    {
        icon.width = width;
        icon.height = height;
        glfwSetWindowIcon(m_Window, 1, &icon);
        SOIL_free_image_data(icon.pixels);
    }
    else
    {
        std::cout<<"FAILED TO LOAD ICON"<<std::endl;
    }
}

void Application::InitCallBackFunc()
{
    glfwSetFramebufferSizeCallback(m_Window, &Application::framebuffer_size_callback);
}

void Application::InitMember()
{
    lightPos    = glm::vec3(1.2f, 0.5f, 1.0f);

    container = new ContainerObj();
    lamp      = new LightObj();

    fps = new FPS();
    m_Camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Application::Run()
{

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(m_Window))
    {
        Render();

        fps->DoFrame();
        //std::cout<< fps->getFPS()<<std::endl;

        processInput();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Application::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lightPos.x = 1.5f * cos(glfwGetTime());
    lightPos.z = 1.5f * sin(glfwGetTime());

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view =  glm::lookAt(m_Camera->getPosition(), m_Camera->getPosition() + m_Camera->getTarget(), m_Camera->getVectorUp());
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);

    container->setViewMatrix(view);
    container->setProjectionMatrix(projection);
    container->setViewPos(m_Camera->getPosition());
    container->setLightPos(lightPos);
    container->Render();

    //Render Lamp
    lamp->setViewMatrix(view);
    lamp->setProjectionMatrix(projection);
    lamp->setLightPos(lightPos);
    lamp->Render();
}

void Application::processInput()
{
    KeyboardInput();

    MouseInput();
}

void Application::KeyboardInput()
{
    float deltaTime = fps->getDeltaTime();
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_Window, GL_TRUE);
    }
    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_Camera->InputKeyBoard(Camera_Movement::FORWARD, deltaTime);
    }
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_Camera->InputKeyBoard(Camera_Movement::BACKWARD, deltaTime);
    }
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_Camera->InputKeyBoard(Camera_Movement::LEFT, deltaTime);
    }
    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_Camera->InputKeyBoard(Camera_Movement::RIGHT, deltaTime);
    }
}

void Application::MouseInput()
{
    POINT p;
    if (GetCursorPos(&p))
    {
        float xpos = p.x;
        float ypos = p.y;

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        m_Camera->InputMouse(xoffset, yoffset);
    }
}

Application::~Application()
{
    if(container)
    {
        delete container;
        container = nullptr;
    }
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::framebuffer_size_callback(GLFWwindow *window, int Width, int Height)
{
    (void)window;
    glViewport(0, 0, Width, Height);
}
