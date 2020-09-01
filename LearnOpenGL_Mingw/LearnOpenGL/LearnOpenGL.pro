QT -= gui
#CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DESTDIR = $$PWD/../bin

DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        application.cpp \
        filehelper.cpp \
        fps.cpp \
        glslshader.cpp \
        loader.cpp \
        main.cpp \
        model.cpp \
        src/glad.c \
        texture.cpp

INCLUDEPATH += $$PWD/../GLFW/include
INCLUDEPATH += $$PWD/../GLM
INCLUDEPATH += $$PWD/../SOIL2/include
INCLUDEPATH += $$PWD/include

LIBS += $$PWD/../GLFW/lib/glfw3.dll
LIBS += $$PWD/../SOIL2/lib/soil2.dll

PROJECT_PATH = $$PWD
DEFINES += PROJECT_PATH

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Global.h \
    application.h \
    filehelper.h \
    fps.h \
    glslshader.h \
    loader.h \
    model.h \
    noncopyable.h \
    texture.h


