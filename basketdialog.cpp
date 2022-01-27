#include "basketdialog.h"
#include "ui_basketdialog.h"
#define Path_to_auth_DB "E:/auth.db"

basketDialog::basketDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::basketDialog)
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
    QSqlQuery* qry = new QSqlQuery(authDB);
    qry -> prepare("SELECT menu FROM Orders");


    //tableView
    if(qry -> exec())
        {
            ui -> label_state-> setText("Get successfully.");

            model -> setQuery(std::move(*qry));
            ui -> tableView -> setModel(model);
            ui -> tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
            ui -> tableView->verticalHeader()->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
            ui -> tableView->setStyleSheet("QHeaderView::section { background-color: rgb(23, 11, 14) }");
            ui->tableView->setColumnWidth(0,300);
            ui->tableView->setColumnWidth(1,300);
            ui->tableView->setColumnWidth(2,40);
            qDebug() << (model -> rowCount());
        }else
        {
            ui -> label_state-> setText("Get unsuccessfull.");
        }
}

basketDialog::~basketDialog()
{
    delete ui;
}
