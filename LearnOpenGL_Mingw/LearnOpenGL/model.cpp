#include "model.h"
namespace GSEngine
{

Model::Model(unsigned int VAOID, unsigned int VertexCount)
    :m_VAOID(VAOID), m_VertexCount(VertexCount)
{
}

Model::~Model()
{
    m_VertexCount = 0;
}

unsigned int Model::getVAOID() const
{
    return m_VAOID;
}

unsigned int Model::getVertexCount() const
{
    return m_VertexCount;
}

}
