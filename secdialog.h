#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include "QDebug"
#include <QtSql>
#include <QFileInfo>
#include <QtCore>
#include <QtGui>
#include "detaildialog.h"
#include "allrestaurantsdialog.h"
#include "menudialog.h"


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
    void on_pushButton_Select_clicked();

    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::SecDialog *ui;
    QSqlDatabase authDB;
    QSqlQueryModel* model;
    QSqlQueryModel* model2;


};

#endif // SECDIALOG_H
