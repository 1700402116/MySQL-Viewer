#include "mysqllist.h"
#include "ui_mysqllist.h"
#include "mainwindow.h"

MySQLlist::MySQLlist(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MySQLlist)
{
    ui->setupUi(this);
    ui->tableWidget->setWindowTitle(db_tables);
    ui->tableWidget->setColumnCount(col);
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->label->setText(QString::number(col));
}

MySQLlist::~MySQLlist()
{
    delete ui;
}
