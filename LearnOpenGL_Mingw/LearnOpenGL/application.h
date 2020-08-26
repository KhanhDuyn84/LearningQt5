#ifndef APPLICATION_H
#define APPLICATION_H
#include "glad/glad.h"

namespace GSEngine {
   class GLSLShader;
   class FPS;
   class Texture;
   class Model;
}

class GLFWwindow;
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
    GLFWwindow *m_Window;
    GSEngine::FPS *fps;

    GSEngine::GLSLShader *triangleShader;
    GSEngine::Texture *triangleTexture;
    GSEngine::Model *triangleModel;

    static void framebuffer_size_callback(GLFWwindow *window, int Width, int Height);
public:
    Application();
    ~Application();
    void Run();
};

#endif // APPLICATION_H
