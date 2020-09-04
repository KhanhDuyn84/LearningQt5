#include "filehelper.h"
#include <QDir>

FileHelper::FileHelper()
{
    m_currentPath = QDir::currentPath().toStdString();
    m_ResoucePath = m_currentPath + "/../Resources";
    m_ImagesPath = m_ResoucePath + "/Images";
    m_ShadersPath = m_ResoucePath + "/Shaders";

    m_MapPath["TRIANGLE_VS"] = m_ShadersPath + "/triangleShaderVS.vs";
    m_MapPath["TRIANGLE_FS"] = m_ShadersPath + "/triangleShaderFS.fs";

    m_MapPath["IMAGE_ICON"] = m_ImagesPath + "/icon2.png";
    m_MapPath["BROKEN_IMAGE"] = m_ImagesPath + "/container.jpg";
}

FileHelper::~FileHelper()
{
    m_MapPath.clear();
}

std::string FileHelper::getPath(const std::string &ID_NAME)
{
    if(m_MapPath.find(ID_NAME) != m_MapPath.end())
    {
        return m_MapPath.at(ID_NAME);
    }
    return "FILE_NOT_EXIST";
}
