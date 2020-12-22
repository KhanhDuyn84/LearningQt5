#include "texture.h"
#include "SOIL2/SOIL2.h"
namespace GSEngine
{

Texture::Texture()
{
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_TextureID);
}

unsigned int Texture::getTextureID() const
{
    return m_TextureID;
}

unsigned int Texture::getTextureUnit() const
{
    return m_TextureUnit;
}

void Texture::LoadTexture(std::string fileName, GLuint TextureUnit, GLuint WRAP_S, GLuint WRAP_T, GLuint FILTER_MAG , GLuint FILTER_MIN)
{
    m_TextureUnit = TextureUnit;
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FILTER_MAG);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FILTER_MIN);

    int width, height, channels;
    unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
    if (image)
    {
        if (channels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        }
        else if (channels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        }
        glGenerateMipmap(0);
        SOIL_free_image_data(image);
    }
    else
    {
        std::cout << "FAILED TO LOAD IMAGE" << std::endl;
    }
}

}
