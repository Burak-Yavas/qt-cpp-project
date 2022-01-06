#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#define Path_to_auth_DB "E:/auth.db"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    authDB = QSqlDatabase:: addDatabase("QSQLITE");
    authDB.setDatabaseName(Path_to_auth_DB);
    QFileInfo checkFile(Path_to_auth_DB);
    if(!checkFile.isFile())
    {
        return;
        ui -> label_state -> setText("Not Connected");

    }else
    {
        ui -> label_state -> setText("Connected");
    }
}
RegisterDialog::~RegisterDialog()
{
    delete ui;
    qDebug() << "Closing the connection on db.";
    authDB.close();
}

void RegisterDialog::on_pushButton_clicked()
{
    QString email = ui-> lineEdit_email -> text();
    QString username = ui-> lineEdit_userName -> text();
    QString password = ui-> lineEdit_regPassword -> text();
    QString password2 = ui-> lineEdit_regPassword2 -> text();

    if(authDB.open())
    {
        ui -> label_state -> setText("Connected");
        qDebug()<< "Connected";
    }
    else{
        ui -> label_state -> setText("Not Connected");
        qDebug()<< "Connection Failed";
        return;

    }
    QSqlQuery qry;
    qry.prepare("INSERT INTO Auth (userName,email,password) VALUES(:username, :email, :password)");
    qry.bindValue(":username",username);
    qry.bindValue(":email",email);
    qry.bindValue(":password",password);
    if(username.length() < 3 )
    {
        ui -> label_state -> setText("name must be more than 3 characters.");
        QMessageBox::warning(this,"Register","Cannot Registered.");

    }
    else if(password2 != password)
    {
        ui -> label_state -> setText("Password fields must match!");
        QMessageBox::warning(this,"Register","Register Failed.");
    }
    else{
        if(qry.exec())
        {
            QMessageBox::information(this,"Register","Registered Successfully.");
            ui -> label_state-> setText("Registered successfully.");
            hide();
        }
    }
}
