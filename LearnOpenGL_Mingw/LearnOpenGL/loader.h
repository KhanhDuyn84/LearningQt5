#ifndef LOADER_H
#define LOADER_H

#include "glad/glad.h"
#include "noncopyable.h"
#include <vector>
#include <iostream>

namespace GSEngine
{
class Texture;
class Model;

class Loader : public Noncopyable
{
private:
    static std::vector<GLuint> m_ListTextureID;
    static std::vector<GLuint> m_ListVAO;
    static std::vector<GLuint> m_ListVBO;
    static std::vector<GLuint> m_ListEBO;


public:
    Loader();
    ~Loader();
    static void CleanUp();
    static Model* LoadModelWithVertices(float *vertices, GLuint vertexCount);
    static Model* LoadModelWithIndices(float *vertices, GLuint vertexCount, GLuint *indices, GLuint indexCount);
    static Texture* LoadTexture(std::string fileName, GLuint TextureUnit, GLuint WRAP_S = GL_REPEAT, GLuint WRAP_T = GL_REPEAT,
                         GLuint FILTER_MAG = GL_LINEAR, GLuint FILTER_MIN = GL_LINEAR);
};
}
#endif // LOADER_H
