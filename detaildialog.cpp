#include "detaildialog.h"
#include "ui_detaildialog.h"
#include <QMessageBox>

#define Path_to_auth_DB "E:/auth.db"

detailDialog::detailDialog(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detailDialog)
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

    ui -> label_restaurant -> setText(restaurantData);

    QSqlQuery* qry = new QSqlQuery(authDB);

    qry -> prepare("SELECT password FROM Auth WHERE userName = :restaurant");
    qry -> bindValue(":restaurant",restaurantData.toLocal8Bit().constData());

    if(qry -> exec())
    {
        ui -> label_state-> setText("Get successfully.");
        model -> setQuery(std::move(*qry));
        ui -> listView -> setModel(model);
        authDB.close();
        qDebug() << (model -> rowCount());
    }else
    {
        ui -> label_state-> setText("Get unsuccessfull.");
    }

}



detailDialog::~detailDialog()
{
    delete ui;
    qDebug() << "Closing the connection on db.";
    authDB.close();
}
