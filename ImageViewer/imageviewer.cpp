#include "imageviewer.h"
#include "ui_imageviewer.h"
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#ifndef QT_NO_PRINTER
#include <QPainter>
#include <QPrintDialog>
#endif

ImageViewer::ImageViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
    InitMenu();
    InitCentralView();
    InitConnection();
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::InitMenu()
{
    openAction = new QAction(tr("&Open..."));
    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key::Key_O));

    printAction = new QAction(tr("&Print..."));
    printAction->setEnabled(false);
    printAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key::Key_P));

    exitAction = new QAction(tr("E&xit"));
    exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key::Key_Q));

    zoomInAction = new QAction(tr("Zoom &In (25%)"));
    zoomInAction->setEnabled(false);
    zoomInAction->setShortcut(QKeySequence("Ctrl+="));

    zoomOutAction = new QAction(tr("Zoom &Out (25%)"));
    zoomOutAction->setEnabled(false);
    zoomOutAction->setShortcut(QKeySequence("Ctrl+-"));

    normalSizeAction = new QAction(tr("&Normal Size"));
    normalSizeAction->setEnabled(false);
    normalSizeAction->setShortcut(QKeySequence("Ctrl+S"));

    fitToWindowAction = new QAction(tr("&Fit to Window"));
    fitToWindowAction->setCheckable(true);
    fitToWindowAction->setEnabled(false);
    fitToWindowAction->setShortcut(QKeySequence("Ctrl+F"));

    aboutAction = new QAction(tr("&About"));
    aboutQtAction = new QAction(tr("About &Qt"));

    QMenu *fileMenu = new QMenu(tr("&File"));
    QMenu *viewMenu = new QMenu(tr("&View"));
    QMenu *aboutMenu = new QMenu(tr("&Help"));

    fileMenu->addAction(openAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(normalSizeAction);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAction);

    aboutMenu->addAction(aboutAction);
    aboutMenu->addAction(aboutQtAction);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(aboutMenu);
}

void ImageViewer::InitCentralView()
{
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
}

void ImageViewer::InitConnection()
{
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(normalSizeAction, SIGNAL(triggered()), this, SLOT(normalSize()));
    connect(fitToWindowAction, SIGNAL(triggered()), this, SLOT(fitToWindow()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void ImageViewer::updateActions()
{
    zoomInAction->setEnabled(!fitToWindowAction->isChecked());
    zoomOutAction->setEnabled(!fitToWindowAction->isChecked());
    normalSizeAction->setEnabled(!fitToWindowAction->isChecked());
}

void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);
    zoomInAction->setEnabled(scaleFactor < 3.0);
    zoomOutAction->setEnabled(scaleFactor > 0.33);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
}


void ImageViewer::open()
{
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
        printAction->setEnabled(true);
        fitToWindowAction->setEnabled(true);
        updateActions();
        if (!fitToWindowAction->isChecked())
            imageLabel->adjustSize();
    }
}

void ImageViewer::print()
{
    Q_ASSERT(imageLabel->pixmap());
#ifndef QT_NO_PRINTER
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
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
    bool fitToWindow = fitToWindowAction->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
    {
        normalSize();
    }
    updateActions();
}

void ImageViewer::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
               tr("<b>Image Viewer</b> example."));
}
