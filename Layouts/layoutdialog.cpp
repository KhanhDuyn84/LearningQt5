#include "layoutdialog.h"
#include "ui_layoutdialog.h"

LayoutDialog::LayoutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LayoutDialog)
{
    ui->setupUi(this);
}

LayoutDialog::~LayoutDialog()
{
    delete ui;
}

