#ifndef MODEL_H
#define MODEL_H

namespace GSEngine
{

class Model
{
private:
    unsigned int m_VAOID;
    unsigned int m_VertexCount;

public:
    Model(unsigned int VAOID, unsigned int VertexCount);
    ~Model();
    unsigned int getVAOID() const;
    unsigned int getVertexCount() const;
};

}

#endif // MODEL_H
