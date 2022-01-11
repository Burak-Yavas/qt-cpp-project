#include "allrestaurantsdialog.h"
#include "ui_allrestaurantsdialog.h"

#define Path_to_auth_DB "D:/auth.db"

allRestaurantsDialog::allRestaurantsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::allRestaurantsDialog)
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

    //tableView
    QSqlQuery* qry2 = new QSqlQuery(authDB);
    qry2 -> prepare("SELECT name, address, star FROM restaurants");
    if(qry2 -> exec())
    {
        ui -> label_state-> setText("Get successfully.");
        model -> setQuery(std::move(*qry2));
        ui -> tableView -> setModel(model);
        qDebug() << (model -> rowCount());
    }else
    {
        ui -> label_state-> setText("Get unsuccessfull.");
    }
}

allRestaurantsDialog::~allRestaurantsDialog()
{
    delete ui;
    qDebug() << "Closing the connection on db.";
    authDB.close();
}

void allRestaurantsDialog::on_pushButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();
    menuDialog *w = new menuDialog(itemText, this);
    w-> show();
}

