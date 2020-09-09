#ifndef APPLICATION_H
#define APPLICATION_H
#include "glad/glad.h"
#include "glm/glm.hpp"

namespace GSEngine {
   class GLSLShader;
   class FPS;
   class Texture;
   class Model;
   class Camera;
}

class GLFWwindow;
class FileHelper;

class Application
{
private:
    void InitWindow();
    void InitOpenGL();
    void InitIcon();
    void InitCallBackFunc();
    void processInput();
    void KeyboardInput();
    void MouseInput();
    void InitMember();
    void Render();
    void Update();
    GLFWwindow *m_Window;
    GSEngine::FPS *fps;

    GSEngine::GLSLShader *objectShader;
    GSEngine::Texture *objectTexture;
    GSEngine::Texture *objectTexture1;
    GSEngine::Model *objectModel;

    GSEngine::GLSLShader *lampShader;
    GSEngine::Model *lampModel;

    glm::vec3 lightPos;
    glm::vec3 lightColor;
    glm::vec3 objectColor;

    static GSEngine::Camera *m_Camera;
    static float lastX, lastY;
    static bool isFirstMouse;
    static void framebuffer_size_callback(GLFWwindow *window, int Width, int Height);
public:
    Application();
    ~Application();
    void Run();
};

#endif // APPLICATION_H
