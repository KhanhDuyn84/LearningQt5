#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QObject>
#include <QHash>

class ResourceManager : public QObject
{
private:
    Q_OBJECT
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    explicit ResourceManager(QObject *parent = nullptr);
    ~ResourceManager();

    QHash<QString, QString> m_ImagesPath;
public:
    static ResourceManager* getInstance()
    {
        static ResourceManager resourceManager;

        return &resourceManager;
    }

    Q_INVOKABLE QString getImagePath(const QString &name);
signals:

};

#endif // RESOURCEMANAGER_H
