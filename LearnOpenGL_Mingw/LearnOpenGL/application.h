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
class ContainerObj;
class LightObj;

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
    GLFWwindow *m_Window;
    GSEngine::FPS *fps;

    ContainerObj *container;
    LightObj     *lamp;

    glm::vec3 lightPos;

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
