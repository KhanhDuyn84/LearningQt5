#include "layoutdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LayoutDialog w;
    w.show();
    return a.exec();
}
