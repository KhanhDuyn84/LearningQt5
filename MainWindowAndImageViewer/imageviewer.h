#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageViewer; }
class QLabel;
class QScrollArea;
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

    void InitMenuBar();
    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};
#endif // IMAGEVIEWER_H
