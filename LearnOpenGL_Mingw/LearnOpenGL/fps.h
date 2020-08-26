#ifndef FPS_H
#define FPS_H
#include "noncopyable.h"

namespace GSEngine
{

class FPS : public Noncopyable
{
private:
    float m_deltaTime = 0.0f;
    float m_lastFrame = 0.0f;
    float m_currentFrame = 0.0f;

public:
    void DoFrame();
    unsigned int getFPS() const;
    float getDeltaTime() const;
    FPS();
    ~FPS();
};

}
#endif // FPS_H
