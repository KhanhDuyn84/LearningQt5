#include "fps.h"
#include "GLFW/glfw3.h"
namespace GSEngine
{

FPS::FPS()
{

}

FPS::~FPS()
{

}

unsigned int FPS::getFPS() const
{
    return (float)(1.0) / m_deltaTime;
}

float FPS::getDeltaTime() const
{
    return m_deltaTime;
}

void FPS::DoFrame()
{
    m_currentFrame = glfwGetTime();
    m_deltaTime = m_currentFrame - m_lastFrame;
    m_lastFrame = m_currentFrame;
}

}
