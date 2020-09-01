#include "application.h"
#include <iostream>
#include <string.h>
#include <QDir>
using namespace std;
int main(int argc, char *argv[])
{
    //QDir::currentPath();
    cout<< QDir::currentPath().toStdString()<<std::endl;
    Application app;
    app.Run();
}
