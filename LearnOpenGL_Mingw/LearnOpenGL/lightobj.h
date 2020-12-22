#ifndef LIGHTOBJ_H
#define LIGHTOBJ_H
#include "glm/glm.hpp"

namespace  GSEngine{
    class GLSLShader;
    class Model;
}

class FileHelper;

class LightObj
{
private:
    GSEngine::Model *lightModel;
    GSEngine::GLSLShader *lightShader;

    glm::vec3 lightPos;
    glm::mat4 model, view, projection;

    FileHelper *fileHelper;

    void InitShader();
    void InitModel();
    void InitTexture();
public:
    LightObj();
    ~LightObj();
    void Render();
    void setLightPos(const glm::vec3 &LightPosition);
    void setViewMatrix(const glm::mat4 &view);
    void setProjectionMatrix(const glm::mat4 &projection);
};

#endif // LIGHTOBJ_H
