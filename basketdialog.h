#ifndef BASKETDIALOG_H
#define BASKETDIALOG_H

#include <QDialog>
#include <QDialog>
#include "QDebug"
#include <QtSql>
#include <QFileInfo>
#include <QtCore>
#include <QtGui>


namespace Ui {
class basketDialog;
}

class basketDialog : public QDialog
{
    Q_OBJECT

public:
    explicit basketDialog(QWidget *parent = nullptr);
    ~basketDialog();

private:
    Ui::basketDialog *ui;
    QSqlDatabase authDB;
    QSqlQueryModel* model;
};

#endif // BASKETDIALOG_H
