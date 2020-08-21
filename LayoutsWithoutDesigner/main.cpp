#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QHBoxLayout *hLayout = new QHBoxLayout;
    QPushButton *btn1 = new QPushButton("A");
    QPushButton *btn2 = new QPushButton("B");
    QPushButton *btn3 = new QPushButton("C");
    hLayout->addWidget(btn1);
    hLayout->addWidget(btn2);
    hLayout->addWidget(btn3);

    //Vertical layout

    QVBoxLayout *vLayout = new QVBoxLayout;
    QPushButton *btn4 = new QPushButton("D");
    QPushButton *btn5 = new QPushButton("E");
    QPushButton *btn6 = new QPushButton("F");
    vLayout->addWidget(btn4);
    vLayout->addWidget(btn5);
    vLayout->addWidget(btn6);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(vLayout);

    QWidget widget;
    widget.setLayout(mainLayout);
    widget.setWindowTitle("Layouts");
    widget.show();
    return a.exec();
}
