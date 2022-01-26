#include "detaildialog.h"
#include "ui_detaildialog.h"
#include <QMessageBox>

#define Path_to_auth_DB "E:/auth.db"

detailDialog::detailDialog(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detailDialog)
{
    ui->setupUi(this);

    QString categoryData = text;

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

    ui -> label_restaurant -> setText(categoryData);

    QSqlQuery* qry = new QSqlQuery(authDB);

    //tableView
    qry -> prepare("SELECT name, address, star FROM restaurants WHERE category_id = :category");
    qry -> bindValue(":category",categoryData.toLocal8Bit().constData());

    if(qry -> exec())
    {
        ui -> label_state-> setText("Get successfully.");
        model -> setQuery(std::move(*qry));
        ui -> tableView -> setModel(model);
        ui -> tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
        ui -> tableView->verticalHeader()->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
        ui -> tableView->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
        ui->tableView->setColumnWidth(0,200);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,40);
        //authDB.close();
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

void detailDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString itemText = index.data(Qt::DisplayRole).toString();
    menuDialog *w = new menuDialog(itemText, this);
    w-> show();
}

