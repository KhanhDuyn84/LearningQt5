#ifndef TEXTURE_H
#define TEXTURE_H

#include "noncopyable.h"

namespace GSEngine
{

class Texture : public Noncopyable
{
private:
    unsigned int m_TextureID;
    unsigned int m_TextureUnit;
public:
    Texture(unsigned int textureID = 0 , unsigned int TextureUnit = 0);
    unsigned int getTextureID() const;
    unsigned int getTextureUnit() const;
};

}
#endif // TEXTURE_H
