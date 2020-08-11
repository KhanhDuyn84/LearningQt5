#include "imageviewer.h"
#include "ui_imageviewer.h"
#include <QLabel>
#include <QScrollArea>
ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    setWindowTitle(tr("Image Viewer"));
    resize(500, 400);
    InitMenuBar();
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::InitMenuBar()
{
    {
        openAct = new QAction(tr("&Open...;"), this);
        openAct->setShortcut(tr("Ctrl+O"));

        printAct = new QAction(tr("&Print...;"), this);
        printAct->setShortcut(tr("Ctrl+P"));
        printAct->setEnabled(false);

        exitAct = new QAction(tr("E&xit;"), this);
        exitAct->setShortcut(tr("Ctrl+Q"));

        QMenu *file = new QMenu("&File");
        file->addAction(openAct);
        file->addAction(printAct);
        file->addSeparator();
        file->addAction(exitAct);
        menuBar()->addMenu(file);
    }
    {
        zoomInAct = new QAction(tr("Zoom &In; (25%)"), this);
        zoomInAct->setShortcut(tr("Ctrl+="));   //(Ctrl)(+)
        zoomInAct->setEnabled(false);

        zoomOutAct = new QAction(tr("Zoom &Out; (25%)"), this);
        zoomOutAct->setShortcut(tr("Ctrl+-"));  //(Ctrl)(-)
        zoomOutAct->setEnabled(false);

        normalSizeAct = new QAction(tr("&Normal; Size"), this);
        normalSizeAct->setShortcut(tr("Ctrl+S"));
        normalSizeAct->setEnabled(false);

        fitToWindowAct = new QAction(tr("&Fit; to Window"), this);
        fitToWindowAct->setEnabled(false);
        fitToWindowAct->setCheckable(true);
        fitToWindowAct->setShortcut(tr("Ctrl+F"));

        QMenu *view = new QMenu("&View");
        view->addAction(zoomInAct);
        view->addAction(zoomOutAct);
        view->addAction(normalSizeAct);
        view->addSeparator();
        view->addAction(fitToWindowAct);
        menuBar()->addMenu(view);
    }
    {
        aboutAct = new QAction(tr("&About;"), this);
        aboutQtAct = new QAction(tr("About &Qt;"), this);
        QMenu *help = new QMenu("&Help");
        help->addAction(aboutAct);
        help->addAction(aboutQtAct);
        menuBar()->addMenu(help);
    }
}
