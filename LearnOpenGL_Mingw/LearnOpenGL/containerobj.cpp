#include "containerobj.h"
#include "texture.h"
#include "glslShader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"
#include "filehelper.h"

using namespace GSEngine;

ContainerObj::ContainerObj()
{
    fileHelper = FileHelper::getInstance();
    InitTexture();
    InitShader();
    InitModel();
    containerShader->Use();
    containerShader->setInt("material.diffuse",  containerTexture->getTextureUnit());
    containerShader->setInt("material.specular", containerSpecular->getTextureUnit());
    containerShader->setFloat("material.shininess",  64.0f);

    containerShader->setVec3("light.ambient", glm::vec3(0.4,	0.4,	0.4));
    containerShader->setVec3("light.diffuse",  glm::vec3(0.7,	0.70,	0.7));
    containerShader->setVec3("light.specular", glm::vec3(1.0,	1.0,	1.0));
    containerShader->setVec3("light.position",  lightPos);
}

ContainerObj::~ContainerObj()
{
    if(containerModel)
    {
        delete containerModel;
        containerModel = nullptr;
    }
    if(containerShader)
    {
        delete containerShader;
        containerShader = nullptr;
    }
    if(containerTexture)
    {
        delete containerTexture;
        containerTexture = nullptr;
    }
    if(containerSpecular)
    {
        delete containerSpecular;
        containerSpecular = nullptr;
    }
}

void ContainerObj::InitShader()
{
    std::string objectVSPath    = fileHelper->getPath("OBJECT_VS");
    std::string objectFSPath    = fileHelper->getPath("OBJECT_FS");
    containerShader = new GLSLShader(objectVSPath.c_str(), objectFSPath.c_str());
    containerShader->Use();
    //containerShader->addAttribute("aPos");
    //containerShader->addAttribute("aNormal");
   // containerShader->addAttribute("aTexCoords");

    //Matrix
    containerShader->addUniform("MVP");
    containerShader->addUniform("model");

    containerShader->addUniform("viewPos");

    //Material
    containerShader->addUniform("material.diffuse");
    containerShader->addUniform("material.specular");
    containerShader->addUniform("material.shininess");

    //Light
    containerShader->addUniform("light.position");
    containerShader->addUniform("light.ambient");
    containerShader->addUniform("light.diffuse");
    containerShader->addUniform("light.specular");
    containerShader->UnUse();
}

void ContainerObj::InitModel()
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

    GLuint vertexCount = sizeof(vertices) / (sizeof(vertices[0]) * 8);
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    containerModel = new Model(VAO, vertexCount);
}

void ContainerObj::InitTexture()
{
    std::string container2Path = fileHelper->getPath("CONTAINER2_IMAGE");
    std::string container2_specularPath = fileHelper->getPath("CONTAINER2_SPECULAR_IMAGE");
    containerTexture = new Texture();
    containerSpecular = new Texture();

    containerTexture->LoadTexture(container2Path, 0);
    containerSpecular->LoadTexture(container2_specularPath, 1);
}

void ContainerObj::Render()
{
    glm::mat4 MVP = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    //model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    MVP = projection * view * model;
    containerShader->Use();
    containerShader->setMat4("MVP", MVP);
    containerShader->setMat4("model", model);
    containerShader->setVec3("viewPos", viewPos);
    containerShader->setVec3("light.position", lightPos);
    glBindVertexArray(containerModel->getVAOID());

    glActiveTexture(GL_TEXTURE0 + containerTexture->getTextureUnit());
    glBindTexture(GL_TEXTURE_2D, containerTexture->getTextureID());
    glActiveTexture(GL_TEXTURE0 + containerSpecular->getTextureUnit());
    glBindTexture(GL_TEXTURE_2D, containerSpecular->getTextureID());

    glDrawArrays(GL_TRIANGLES, 0 , containerModel->getVertexCount());
}

void ContainerObj::setLightPos(const glm::vec3 &LightPosition)
{
    lightPos = LightPosition;
}

void ContainerObj::setViewPos(const glm::vec3 &ViewPosition)
{
    viewPos = ViewPosition;
}

void ContainerObj::setViewMatrix(const glm::mat4 &view)
{
    this->view = view;
}

void ContainerObj::setProjectionMatrix(const glm::mat4 &projection)
{
    this->projection = projection;
}
