#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include <QDialog>
#include <QDialog>
#include "QDebug"
#include <QtSql>
#include <QFileInfo>
#include <QtCore>
#include <QtGui>

namespace Ui {
class menuDialog;
}

class menuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit menuDialog(QString text, QWidget *parent = nullptr);
    ~menuDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::menuDialog *ui;
    QSqlDatabase authDB;
    QSqlQueryModel* model;
    QString restaurantData;

};

#endif // MENUDIALOG_H
