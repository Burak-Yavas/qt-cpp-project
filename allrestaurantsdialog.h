#ifndef ALLRESTAURANTSDIALOG_H
#define ALLRESTAURANTSDIALOG_H

#include <QDialog>
#include "QDebug"
#include <QtSql>
#include <QFileInfo>
#include <QtCore>
#include <QtGui>
#include "menudialog.h"


namespace Ui {
class allRestaurantsDialog;
}

class allRestaurantsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit allRestaurantsDialog(QWidget *parent = nullptr);
    ~allRestaurantsDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::allRestaurantsDialog *ui;
    QSqlDatabase authDB;
    QSqlQueryModel* model;
};

#endif // ALLRESTAURANTSDIALOG_H
