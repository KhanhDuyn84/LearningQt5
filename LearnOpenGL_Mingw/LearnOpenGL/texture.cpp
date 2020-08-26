#include "texture.h"

namespace GSEngine
{

Texture::Texture(unsigned int textureID, unsigned int TextureUnit)
    : m_TextureID(textureID), m_TextureUnit(TextureUnit)
{
}
unsigned int Texture::getTextureID() const
{
    return m_TextureID;
}

unsigned int Texture::getTextureUnit() const
{
    return m_TextureUnit;
}

}
