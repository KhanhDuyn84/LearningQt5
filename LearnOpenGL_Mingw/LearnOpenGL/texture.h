#ifndef TEXTURE_H
#define TEXTURE_H
#include "glad/glad.h"
#include <iostream>
#include "noncopyable.h"

namespace GSEngine
{

class Texture : public Noncopyable
{
private:
    GLuint m_TextureID;
    GLuint m_TextureUnit;
public:
    Texture ();
    ~Texture();
    void LoadTexture(std::string fileName, GLuint TextureUnit, GLuint WRAP_S = GL_REPEAT, GLuint WRAP_T = GL_REPEAT,
                     GLuint FILTER_MAG = GL_LINEAR, GLuint FILTER_MIN = GL_LINEAR);
    GLuint getTextureID() const;
    GLuint getTextureUnit() const;
};

}
#endif // TEXTURE_H
