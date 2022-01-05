#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include "QDebug"
#include <QtSql>
#include <QFileInfo>
#include <QtCore>
#include <QtGui>


namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Select_clicked();

private:
    Ui::SecDialog *ui;
    QSqlDatabase authDB;
    //QSqlQueryModel* model;
    QSqlQueryModel* model;


};

#endif // SECDIALOG_H
