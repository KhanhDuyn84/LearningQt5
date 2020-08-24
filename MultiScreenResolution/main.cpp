#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QScreen>
#include <QQmlContext>
#include "notificationclient.h"
#include "resourcemanager.h"
#if defined (Q_OS_ANDROID)
    #include <QAndroidJniObject>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QScreen *screen = QGuiApplication::primaryScreen();
    qreal dpi;
#if defined (Q_OS_WIN)
    dpi = screen->logicalDotsPerInch() * app.devicePixelRatio();
#elif defined (Q_OS_ANDROID)
    QAndroidJniObject qtActivity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",
                                                                             "activity",
                                                                             "()Landroid/app/Activity;");
    QAndroidJniObject resources = qtActivity.callObjectMethod("getResources", "()Landroid/content/res/Resources;");
    QAndroidJniObject displayMetrics = resources.callObjectMethod("getDisplayMetrics", "()Landroid/util/DisplayMetrics;");
    int density = displayMetrics.getField<int>("densityDpi");
    dpi = density;
#else
    dpi = screen->physicalDotsPerInch() * app.devicePixelRatio();
#endif

    QQmlContext *context = engine.rootContext();
    NotificationClient notificationClient(context);
    context->setContextProperty("notificationClient", &notificationClient);
    context->setContextProperty("resourceManager", ResourceManager::getInstance());
    context->setContextProperty("screenDpi", dpi);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
