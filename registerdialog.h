#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "QDebug"
#include <QtSql>
#include <QFileInfo>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RegisterDialog *ui;
    QSqlDatabase authDB;

};

#endif // REGISTERDIALOG_H
