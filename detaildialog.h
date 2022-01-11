#ifndef DETAILDIALOG_H
#define DETAILDIALOG_H

#include <QDialog>
#include "QDebug"
#include <QtSql>
#include <QFileInfo>
#include <QtCore>
#include <QtGui>
#include "menudialog.h"


namespace Ui {
class detailDialog;
}

class detailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit detailDialog(QString text, QWidget *parent = nullptr);
    ~detailDialog();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::detailDialog *ui;
    QSqlDatabase authDB;
    QSqlQueryModel* model;
    QString restaurantData;
};

#endif // DETAILDIALOG_H
