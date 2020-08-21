#ifndef LAYOUTDIALOG_H
#define LAYOUTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class LayoutDialog; }
QT_END_NAMESPACE

class LayoutDialog : public QDialog
{
    Q_OBJECT

public:
    LayoutDialog(QWidget *parent = nullptr);
    ~LayoutDialog();

private:
    Ui::LayoutDialog *ui;
};
#endif // LAYOUTDIALOG_H
