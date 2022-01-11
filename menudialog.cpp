#include "menudialog.h"
#include "ui_menudialog.h"
#include <QMessageBox>

#define Path_to_auth_DB "D:/auth.db"

menuDialog::menuDialog(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuDialog)
{
    ui->setupUi(this);

    QString restaurantData = text;
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

    model = new QSqlQueryModel(this);
    ui -> label -> setText(restaurantData);
    QSqlQuery* qry = new QSqlQuery(authDB);

    //tableView
    qry -> prepare("SELECT name, detail, price FROM restaurant_menu WHERE restaurant = :restaurant");
    qry -> bindValue(":restaurant",restaurantData.toLocal8Bit().constData());

    if(qry -> exec())
    {
        ui -> label_state-> setText("Get successfully.");
        model -> setQuery(std::move(*qry));
        ui -> tableView -> setModel(model);
        qDebug() << (model -> rowCount());
    }else
    {
        ui -> label_state-> setText("Get unsuccessfull.");
    }
}

menuDialog::~menuDialog()
{
    delete ui;
    qDebug() << "Closing the connection on db.";
    authDB.close();
}

void menuDialog::on_pushButton_clicked()
{

}

