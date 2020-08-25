#ifndef APPLICATION_H
#define APPLICATION_H
#include "glad/glad.h"
class GLFWwindow;

class Application
{
private:
    void InitWindow();
    void InitOpenGL();
    void InitCallBackFunc();
    void processInput();
    GLFWwindow *m_Window;

    static void framebuffer_size_callback(GLFWwindow *window, int Width, int Height);
public:
    Application();
    ~Application();
    void Run();
};

#endif // APPLICATION_H
