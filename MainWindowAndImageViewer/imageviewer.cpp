#include "imageviewer.h"
#include "ui_imageviewer.h"
#include <QLabel>
#include <QScrollArea>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>
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
    InitConnection();
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

void ImageViewer::InitConnection()
{
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void ImageViewer::updateAction()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void ImageViewer::open()
{
    qDebug()<<"Open ()";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if(!fileName.isEmpty())
    {
        QImage image(fileName);
        if(image.isNull())
        {
            QMessageBox::information(this, tr("Image Viewer"), tr("Cannot load %1.").arg(fileName));
            return;
        }
        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;
        printAct->setEnabled(true);
        fitToWindowAct->setEnabled(true);
        updateAction();
        if(!fitToWindowAct->isChecked())
        {
            imageLabel->adjustSize();
        }
    }
}

void ImageViewer::print()
{
    qDebug()<<"PRINT";
}

void ImageViewer::zoomIn()
{
    scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
    scaleImage(0.8);
}

void ImageViewer::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::fitToWindow()
{
    bool isFitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(isFitToWindow);
    if(!isFitToWindow)
    {
        normalSize();
    }
    updateAction();
}

void ImageViewer::scaleImage(float scaleFactor)
{
    Q_ASSERT(imageLabel->pixmap());
    this->scaleFactor *= scaleFactor;
    imageLabel->resize(this->scaleFactor * imageLabel->pixmap()->size());
    adjustScrollBar(scrollArea->horizontalScrollBar(), scaleFactor);
    adjustScrollBar(scrollArea->verticalScrollBar(), scaleFactor);
    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, float factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor -1) * scrollBar->pageStep()/2)));
}
