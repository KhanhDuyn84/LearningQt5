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
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    FileHelper *fileHelper      = FileHelper::getInstance();
    std::string objectVSPath    = fileHelper->getPath("OBJECT_VS");
    std::string objectFSPath    = fileHelper->getPath("OBJECT_FS");
    std::string lampFSPath      = fileHelper->getPath("LAMP_FS");
    std::string container2Path = fileHelper->getPath("CONTAINER2_IMAGE");
    std::string container2_specularPath = fileHelper->getPath("CONTAINER2_SPECULAR_IMAGE");
    lightPos    = glm::vec3(1.2f, 0.0f, 1.0f);
    lightColor  = glm::vec3(1.0f, 1.0f, 1.0f);
    objectColor = glm::vec3(1.0f, 0.5f, 0.31f);

    //For container object
    objectModel = Loader::LoadModelWithVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
    //objectModel = Loader::LoadModelWithIndices(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));

    objectShader    = new GLSLShader(objectVSPath.c_str(), objectFSPath.c_str());
    objectTexture   = Loader::LoadTexture(container2Path.c_str(), 0);
    objectTexture1  = Loader::LoadTexture(container2_specularPath.c_str(), 1);

    objectShader->addUniform("MVP");
    objectShader->addUniform("model");

    objectShader->addUniform("objectColor");
    objectShader->addUniform("lightColor");
    objectShader->addUniform("lightPos");
    objectShader->addUniform("viewPos");

    objectShader->addUniform("material.diffuse");
    objectShader->addUniform("material.specular");
    objectShader->addUniform("material.shininess");

    objectShader->addUniform("light.position");
    objectShader->addUniform("light.ambient");
    objectShader->addUniform("light.diffuse");
    objectShader->addUniform("light.specular");

    objectShader->Use();
    objectShader->setVec3("objectColor", objectColor);
    objectShader->setVec3("lightColor",  lightColor);

    objectShader->setInt("material.diffuse",  objectTexture->getTextureUnit());
    objectShader->setInt("material.specular", objectTexture1->getTextureUnit());
    objectShader->setFloat("material.shininess",  64.0f);

    objectShader->setVec3("light.ambient", glm::vec3(0.2,	0.2,	0.2));
    objectShader->setVec3("light.diffuse",  glm::vec3(0.5,	0.5,	0.5));
    objectShader->setVec3("light.specular", glm::vec3(1.0,	1.0,	1.0));
    objectShader->setVec3("light.position",  lightPos);

    objectShader->setInt("ourTexture", 0);

    //For Lamp Object
    lampModel       = Loader::LoadModelWithVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
    lampShader      = new GLSLShader(objectVSPath.c_str(), lampFSPath.c_str());
    lampShader->addUniform("lightColor");
    lampShader->addUniform("MVP");

    lampShader->Use();
    lampShader->setVec3("lightColor", lightColor);

    fps = new FPS();
    m_Camera = new Camera(glm::vec3(-1.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Application::Run()
{

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(m_Window))
    {
        Update();

        Render();

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

    //For object
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-50.0f), glm::vec3(1.0f, 0.5f, 0.0f));
    view = glm::lookAt(m_Camera->getPosition(), m_Camera->getPosition() + m_Camera->getTarget(), m_Camera->getVectorUp());
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);
    MVP = projection * view * model;
    lightPos.x = 2.0f * cos(glfwGetTime());
    lightPos.z = 2.0f * sin(glfwGetTime());
    objectShader->Use();
    objectShader->setVec3("lightPos", lightPos);
    objectShader->setVec3("viewPos", m_Camera->getPosition());
    objectShader->setMat4("MVP", MVP);
    objectShader->setMat4("model", model);

    //For Lamp
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    MVP = projection * view * model;
    lampShader->Use();
    lampShader->setMat4("MVP", MVP);
}

void Application::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render Object
    objectShader->Use();
    glBindTexture(GL_TEXTURE_2D, objectTexture->getTextureID());
    glActiveTexture(GL_TEXTURE0 + objectTexture->getTextureUnit());
    glBindTexture(GL_TEXTURE_2D, objectTexture1->getTextureID());
    glActiveTexture(GL_TEXTURE0 + objectTexture1->getTextureUnit());
    glBindVertexArray(objectModel->getVAOID());
    glDrawArrays(GL_TRIANGLES, 0, objectModel->getVertexCount());

    //Render Lamp
    lampShader->Use();
    glBindVertexArray(lampModel->getVAOID());
    glDrawArrays(GL_TRIANGLES, 0, lampModel->getVertexCount());
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
    Loader::CleanUp();
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::framebuffer_size_callback(GLFWwindow *window, int Width, int Height)
{
    (void)window;
    glViewport(0, 0, Width, Height);
}
