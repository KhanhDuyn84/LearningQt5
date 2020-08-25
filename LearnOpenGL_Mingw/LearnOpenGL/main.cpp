#include "application.h"
#include <QDir>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    //qDebug()<< QCoreApplication::applicationDirPath();
    Application app;
    app.Run();
}
