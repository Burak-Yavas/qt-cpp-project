#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#define Path_to_auth_DB "E:/auth.db"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    authDB = QSqlDatabase:: addDatabase("QSQLITE");
    authDB.setDatabaseName(Path_to_auth_DB);
    QFileInfo checkFile(Path_to_auth_DB);

    if(!checkFile.isFile())
    {
        return;
        ui -> labelResult -> setText("Not Connected");

    }else{
        ui -> labelResult -> setText("Connected");

    }

    //QPixmap pix(":/resources/img/background.jpg");
    //int w = ui->label_picture->width();
    //int h = ui->label_picture->height();
    //ui->label_picture->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "Closing the connection on db";
    authDB.close();
}




void MainWindow::on_signUpButton_clicked()
{
    authDB.close();
    regDialog = new RegisterDialog(this);
    regDialog -> show();
}



void MainWindow::on_loginButton_clicked()
{
    QString username = ui-> lineEdit_user -> text();
    QString password = ui-> lineEdit_password -> text();
    if(authDB.open())
    {
        ui -> labelResult -> setText("Connected");
    }
    else{
        ui -> labelResult -> setText("Not Connected");
    }

    QSqlQuery qry;
    if(qry.exec("SELECT userName, password FROM Auth WHERE userName=\'" + username + "\' AND password=\'" + password + "\'"))
    {
      if(qry.next()){
          ui -> labelResult-> setText("Valid login");
          QMessageBox::warning(this,"Register","Logged In.");
          secDialog = new SecDialog(this);
          secDialog -> show();
          hide();
      }else{
          ui-> labelResult -> setText("Invalid login");
          QMessageBox::warning(this,"Login","Login Failed.");

      }
    }
}
