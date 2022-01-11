#include "basketdialog.h"
#include "ui_basketdialog.h"

basketDialog::basketDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::basketDialog)
{
    ui->setupUi(this);
}

basketDialog::~basketDialog()
{
    delete ui;
}
