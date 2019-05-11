#include "mylist.h"
#include "ui_mylist.h"
#include "mainwindow.h"

MyList::MyList(int col, int row,
    QStringList header, QString db_tables,
               QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MyList)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(col);
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setWindowTitle(db_tables);
    //列数大于6的话就直接按原比例放好了
    if(col <= 6)
    {
        //x先自适应宽度
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //然后设置要根据内容使用宽度的列
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    }

    //针对表头的设计
    QFont font;
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:lightblue;}");
    //隐藏垂直表头
    ui->tableWidget->verticalHeader()->setVisible(false);

/**************************在单元格中添加combo box**************************
    QStringList sexList;
    sexList<<"Men"<<"Women";
    QComboBox *sex=new QComboBox();
    sex->addItems(sexList);
    ui->tableWidget->setCellWidget(0,0,sex);
*************************************************************************/

    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(mySortByColumn(int)));
}

void MyList::setItem(int row, int column, QTableWidgetItem* widget)
{
    ui->tableWidget->setItem(row,column,widget);
    ui->tableWidget->item(row,column)->setTextAlignment(Qt::AlignCenter);
    //改变每一行数据的颜色，看起来稍微好一点
    if(!row%2)
    {
        ui->tableWidget->item(row,column)->setBackgroundColor(QColor(190,190,190));
    }
    else
    {
        ui->tableWidget->item(row,column)->setBackgroundColor(QColor(220,220,220));
    }
}

MyList::~MyList()
{
    delete ui;
}

void MyList::mySortByColumn(int column)
{
    static bool f = true;
    ui->tableWidget->sortByColumn(column, f ? Qt::AscendingOrder : Qt::DescendingOrder);
    f = !f;

}

