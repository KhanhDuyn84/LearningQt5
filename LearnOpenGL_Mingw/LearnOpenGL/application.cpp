#include "application.h"
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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <windows.h>

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
    //glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowOpacity(m_Window, 0.7f);
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
    std::cout<<imagePath<<std::endl;
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
    glfwSetCursorPosCallback(m_Window, &Application::mouse_callback);
    glfwSetWindowFocusCallback(m_Window, &Application::window_focus_callback);
}

void Application::InitMember()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    triangleModel = Loader::LoadModelWithVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
    //triangleModel = Loader::LoadModelWithIndices(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));

    FileHelper *fileHelper = FileHelper::getInstance();
    std::string triangleVSPath = fileHelper->getPath("TRIANGLE_VS");
    std::string triangleFSPath = fileHelper->getPath("TRIANGLE_FS");
    std::string brokenImagePath = fileHelper->getPath("BROKEN_IMAGE");

    triangleShader = new GLSLShader(triangleVSPath.c_str(), triangleFSPath.c_str());
    triangleTexture = Loader::LoadTexture(brokenImagePath.c_str(), 0);

    triangleShader->addUniform("ourTexture");
    triangleShader->addUniform("MVP");
    triangleShader->setInt("ourTexture", 0);

    fps = new FPS();

    m_Camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Application::Run()
{

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND_SRC);
    while (!glfwWindowShouldClose(m_Window))
    {

        Update();
        Render();
        //double PosX, PosY;
        //glfwGetCursorPos(m_Window, &PosX, &PosY);
        //std::cout<<PosX<<"  "<<PosY<<std::endl;
        fps->DoFrame();
        //std::cout<< fps->getFPS()<<std::endl;
        processInput();


        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Application::Update()
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 MVP = glm::mat4(1.0f);

    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-50.0f), glm::vec3(1.0f, 0.5f, 0.0f));
    view = glm::lookAt(m_Camera->getPosition(), m_Camera->getPosition() + m_Camera->getTarget(), m_Camera->getVectorUp());
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);
    MVP = projection * view * model;

    triangleShader->Use();
    triangleShader->setMat4("MVP", MVP);
}

void Application::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    triangleShader->Use();
    glBindVertexArray(triangleModel->getVAOID());
    glActiveTexture(GL_TEXTURE0 + triangleTexture->getTextureUnit());
    glBindTexture(GL_TEXTURE_2D, triangleTexture->getTextureID());
    glDrawArrays(GL_TRIANGLES, 0 , triangleModel->getVertexCount());
    //glDrawElements(GL_TRIANGLES, triangleModel->getVertexCount(), GL_UNSIGNED_INT, 0);
}

void Application::processInput()
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

    POINT p;
    if (GetCursorPos(&p))
    {
        //cursor position now in p.x and p.y
        std::cout<<p.x<<"   "<<p.y<<std::endl;
        float xpos = p.x;
        float ypos = p.y;
//        if (isFirstMouse)
//        {
//            lastX = xpos;
//            lastY = ypos;
//            isFirstMouse = false;
//        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        m_Camera->InputMouse(xoffset, yoffset);
    }
}

Application::~Application()
{
    Loader::CleanUp();
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
//    (void)window;
//    if (isFirstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        isFirstMouse = false;
//    }

//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//    lastX = xpos;
//    lastY = ypos;

//    m_Camera->InputMouse(xoffset, yoffset);
}

void Application::framebuffer_size_callback(GLFWwindow *window, int Width, int Height)
{
    (void)window;
    glViewport(0, 0, Width, Height);
}

void Application::window_focus_callback(GLFWwindow *window, int focused)
{
//    if(focused)
//    {
//        glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE);
//    }
//    else
//    {
//        glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
//    }
}
