#include "notificationclient.h"
#include <QtGlobal>
#include <QDebug>
#if defined (Q_OS_ANDROID)
    #include <QtAndroid>
#endif

NotificationClient::NotificationClient(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateAndroidNotification()));
}

void NotificationClient::setNotification(const QString &notification)
{
    if (m_notification == notification)
        return;

    m_notification = notification;
    emit notificationChanged();
}

QString NotificationClient::notification() const
{
    return m_notification;
}

void NotificationClient::updateAndroidNotification()
{
    #if defined (Q_OS_ANDROID)
        QAndroidJniObject javaNotification = QAndroidJniObject::fromString(m_notification);
        QAndroidJniObject::callStaticMethod<void>(
            "org/qtproject/example/MultiScreenResolution/NotificationClient",
            "notify",
            "(Landroid/content/Context;Ljava/lang/String;)V",
            QtAndroid::androidContext().object(),
            javaNotification.object<jstring>());
    #else
        qDebug()<<m_notification;
    #endif
}
