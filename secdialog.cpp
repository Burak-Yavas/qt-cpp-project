#include "secdialog.h"
#include "ui_secdialog.h"
#include <QMessageBox>

#define Path_to_auth_DB "D:/auth.db"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
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
    model = new QSqlQueryModel(this);

}

SecDialog::~SecDialog()
{
    delete ui;
    qDebug() << "Closing the connection on db.";
    authDB.close();
}

void SecDialog::on_pushButton_clicked()
{
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
    QSqlQuery* qry = new QSqlQuery(authDB);
    qry -> prepare("SELECT userName FROM Auth");
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


void SecDialog::on_pushButton_Select_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();

    QMessageBox::information(this,"Selected",itemText);
}

