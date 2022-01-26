#include "menudialog.h"
#include "ui_menudialog.h"
#include <QMessageBox>

#define Path_to_auth_DB "E:/auth.db"

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
        //ui-> tableView->setColumnCount(3);
        ui->tableView->setColumnWidth(0,200);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,40);
        ui -> tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
        ui -> tableView->verticalHeader()->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
        ui -> tableView->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");


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

