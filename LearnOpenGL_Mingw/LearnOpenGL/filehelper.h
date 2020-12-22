#ifndef FILEHELPER_H
#define FILEHELPER_H
#include "noncopyable.h"
#include <iostream>
#include <map>

class FileHelper : public Noncopyable
{
private:
    std::string m_currentPath;
    std::string m_ResoucePath;
    std::string m_ImagesPath;
    std::string m_ShadersPath;
    std::map<std::string, std::string> m_MapPath;

    FileHelper();
    ~FileHelper();
public:

    static FileHelper* getInstance()
    {
        static FileHelper fileHelper;
        return &fileHelper;
    }

    std::string getPath(const std::string &ID_NAME);
};

#endif // FILEHELPER_H
