#ifndef APPLICATION_H
#define APPLICATION_H
#include "glad/glad.h"

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
    void InitMember();
    void Render();
    void Update();
    GLFWwindow *m_Window;
    GSEngine::FPS *fps;

    GSEngine::GLSLShader *triangleShader;
    GSEngine::Texture *triangleTexture;
    GSEngine::Model *triangleModel;

    static GSEngine::Camera *m_Camera;
    static float lastX, lastY;
    static bool isFirstMouse;
    static void window_focus_callback(GLFWwindow *window, int focused);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void framebuffer_size_callback(GLFWwindow *window, int Width, int Height);
public:
    Application();
    ~Application();
    void Run();
};

#endif // APPLICATION_H
