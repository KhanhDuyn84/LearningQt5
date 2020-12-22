#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif
QT_BEGIN_NAMESPACE
class QLabel;
class QScrollArea;
class QScrollBar;
class QAction;
class QPrinter;
namespace Ui { class ImageViewer; }
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();

private slots:
    void open();
    void print();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    void about();

private:
    void InitMenu();
    void InitCentralView();
    void InitConnection();
    Ui::ImageViewer *ui;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QAction *openAction;
    QAction *printAction;
    QAction *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *normalSizeAction;
    QAction *fitToWindowAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    double scaleFactor;

    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif
};
#endif // IMAGEVIEWER_H
