#ifndef CONTAINEROBJ_H
#define CONTAINEROBJ_H
#include "glm/glm.hpp"

namespace  GSEngine{
    class GLSLShader;
    class Texture;
    class Model;
}

class FileHelper;

class ContainerObj
{
private:
    GSEngine::Model *containerModel;
    GSEngine::GLSLShader *containerShader;
    GSEngine::Texture *containerTexture;
    GSEngine::Texture *containerSpecular;
    FileHelper *fileHelper;

    glm::vec3 lightPos;
    glm::vec3 viewPos;
    glm::mat4 model, view, projection;

    void InitShader();
    void InitModel();
    void InitTexture();

public:
    ContainerObj();
    ~ContainerObj();
    void Render();
    void setLightPos(const glm::vec3 &LightPosition);
    void setViewPos(const glm::vec3 &ViewPosition);
    void setViewMatrix(const glm::mat4 &view);
    void setProjectionMatrix(const glm::mat4 &projection);
};

#endif // CONTAINEROBJ_H
