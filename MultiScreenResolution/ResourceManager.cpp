#include "resourcemanager.h"

ResourceManager::ResourceManager(QObject *parent) : QObject(parent)
{
#if defined (Q_OS_WIN)
    m_ImagesPath.insert("Cat","file:/Users/duy3.nguyen/Desktop/QT_PROJECT/MultiScreenResolution/android/assets/Images/cat.jpg");

#elif defined (Q_OS_ANDROID)
    m_ImagesPath.insert("Cat","assets:/Images/cat.jpg");

#endif
}

ResourceManager::~ResourceManager()
{

}

QString ResourceManager::getImagePath(const QString &name)
{
    if(m_ImagesPath.contains(name))
    {
        return m_ImagesPath[name];
    }
    return m_ImagesPath["file_not_found"];
}
