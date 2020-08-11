#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageViewer; }
class QLabel;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();

private:
    Ui::ImageViewer *ui;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    float scaleFactor;

    void InitMenuBar();
    void InitConnection();
    void updateAction();
    void scaleImage(float scaleFactor);
    void adjustScrollBar(QScrollBar *scrollBar, float factor);
private slots:
    void open();
    void print();

    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
};
#endif // IMAGEVIEWER_H
