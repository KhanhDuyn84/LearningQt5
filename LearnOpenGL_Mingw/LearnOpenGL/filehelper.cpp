#include "filehelper.h"
#include <QDir>

FileHelper::FileHelper()
{
    m_currentPath = QDir::currentPath().toStdString();
    m_ResoucePath = m_currentPath + "/../Resources";
    m_ImagesPath = m_ResoucePath + "/Images";
    m_ShadersPath = m_ResoucePath + "/Shaders";

    m_MapPath["OBJECT_VS"] = m_ShadersPath + "/objectShaderVS.vs";
    m_MapPath["OBJECT_FS"] = m_ShadersPath + "/objectShaderFS.fs";
    m_MapPath["LAMP_FS"]   = m_ShadersPath + "/lampShaderFS.fs";

    m_MapPath["IMAGE_ICON"] = m_ImagesPath + "/icon2.png";
    m_MapPath["CONTAINER2_IMAGE"] = m_ImagesPath + "/container2.png";
    m_MapPath["CONTAINER2_SPECULAR_IMAGE"] = m_ImagesPath + "/container2_specular.png";
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
