#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secdialog.h"
#include "registerdialog.h"
#include "QDebug"
#include <QtSql>
#include <QFileInfo>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void fTime();

private slots:
    void on_loginButton_clicked();

    void on_signUpButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase authDB;
    SecDialog * secDialog;
    RegisterDialog * regDialog;
    QTimer *timer;


};
#endif // MAINWINDOW_H
