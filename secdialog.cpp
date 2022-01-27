#include "secdialog.h"
#include "ui_secdialog.h"
#include <QMessageBox>

#define Path_to_auth_DB "E:/auth.db"

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
    model2 = new QSqlQueryModel(this);

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

    //listView
    ui -> listView->setFlow(QListView::Flow::LeftToRight);
    QSqlQuery* qry = new QSqlQuery(authDB);
    if(qry -> exec("SELECT name FROM food_categories"))
    {
        ui -> label_state-> setText("Get successfully.");
        model -> setQuery(std::move(*qry));
        ui -> listView -> setModel(model);
        qDebug() << (model -> rowCount());
    }else
    {
        ui -> label_state-> setText("Get unsuccessfull.");
    }


    //tableView
    QSqlQuery* qry2 = new QSqlQuery(authDB);
    qry2 -> prepare("SELECT name, address, star FROM restaurants WHERE star > 7");
    if(qry2 -> exec())
    {
        ui -> label_state-> setText("Get successfully.");
        model2 -> setQuery(std::move(*qry2));
        ui -> tableView -> setModel(model2);
        ui -> tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
        ui -> tableView->verticalHeader()->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
        ui -> tableView->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
        ui->tableView->setColumnWidth(0,200);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,40);
        qDebug() << (model2 -> rowCount());
    }else
    {
        ui -> label_state-> setText("Get unsuccessfull.");
    }
}

SecDialog::~SecDialog()
{
    delete ui;
    qDebug() << "Closing the connection on db.";
    authDB.close();
}


void SecDialog::on_pushButton_Select_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();
    qDebug() << (itemText);
    detailDialog *w = new detailDialog(itemText, this);
    w-> show();
}


void SecDialog::on_pushButton_clicked()
{
    allRestaurantsDialog *w = new allRestaurantsDialog(this);
    w -> show();
}


void SecDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString itemText = index.data(Qt::DisplayRole).toString();
    menuDialog *w = new menuDialog(itemText, this);
    w-> show();
}


void SecDialog::on_pushButton_2_clicked()
{
    basketDialog *w = new basketDialog(this);
        w -> show();

}

