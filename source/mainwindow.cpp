#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>

//QString VERSION = "1.0.0";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->setDisabled(true);

    isConnect = false;
    view_mode = false;
    edit_mode = false;
    is_Error  = false;

    ip = "47.100.173.197";
    databases = "mysql";
    user = "root";
    //password = "cjluxk808";

    ui->lineEdit_ip->setText(ip);
    ui->comboBox_2->clear();
    //ui->comboBox_2->addItem(databases);
    ui->lineEdit_user->setText(user);
    ui->lineEdit_pass->setText(password);

    version_check();
}

MainWindow::~MainWindow()
{
    delete version_info;
    delete ui;
}

//初始化数据库连接
void MainWindow::MySQL_Init()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ip);//设置你远程服务器的IP
    db.setUserName(user);//数据库用户名和密码
    db.setPassword(password);
    db.setDatabaseName(databases);//use test_qt;
    if (!db.open())
    {
        ui->label->setText("连接失败！");
        is_Error = true;
    }
    else
        {
            ui->label->setText("连接成功！");
            is_Error = false;
            QString cmd = "show databases;";
            QSqlQuery query(cmd);
            char a = 0;
            if(!isConnect)
            {
                ui->comboBox_2->clear();
                while(query.seek(a))
                {
                    ui->comboBox_2->addItem(query.value(0).toString());
                    a += 1;
                }
                ui->pushButton->setText("连接至数据库");
             }
        }
}
//将表中数据显示到combo box中
void MainWindow::table_init()
{
    //保存数据库列名
    QStringList titles;
    QStringList header;

    QString cmd = "SELECT * FROM ";
    cmd = cmd.append(db_tables);
    cmd = cmd.append(";");

    char a = 0;
    //用于控制query.value(datas)的显示列数
    int datas = 0;
    //执行SELECT * FROM <table_name>指令
    QSqlQuery query;
    query.prepare(QString(cmd));
    query.exec();
    //获取列数
    QSqlRecord sqlRecord(query.record());
    col = sqlRecord.count();

    for(int i = 0; i < sqlRecord.count(); i++)
    {
        header << sqlRecord.fieldName(i);
        datas = i;
    }
/**************************************获取数据类型的指令*****************************************/
    cmd = "select COLUMN_NAME,DATA_TYPE from information_schema.columns where TABLE_SCHEMA='";
    cmd.append(databases);
    cmd.append("' and TABLE_NAME='");
    cmd.append(db_tables);
    cmd.append("';");

    query.exec(cmd);
    QSqlRecord Record(query.record());
    //ui->label->setText(cmd);
    while(query.seek(a))
    {
        QString type;
        QString column_name;
        type = query.value(1).toString();
        column_name = header.at(a);
        column_name = column_name.append("(").append(type).append(")");

        titles << column_name;
        a += 1;
    }
/*****************************以上实现将字段类型整合到表头****************************************/
    if(isConnect)
    {
        //再次执行SELECT * FROM <table_name>指令
        cmd = "SELECT * FROM ";
        cmd = cmd.append(db_tables);
        cmd = cmd.append(";");
        query.prepare(QString(cmd));
        query.exec();
        //获取列表的行数
        int initialPos = query.at();
        row = 0;
        if (query.last())
        {
            row = query.at() + 1;
        }
        else
        {
            row = 0;
        }
        //对query和计数变量a进行复位
        query.seek(initialPos);
        a = 0;

        MyList* lists = new MyList(col,row,titles,db_tables);
        //把所有的数据都显示到TableWidget上
        while(query.seek(a))
        {
            for(int b=0; b<=datas;b++)
            {
                lists->setItem(a,b,new QTableWidgetItem(query.value(b).toString()));
            }
            a += 1;
        }
        lists->show();
    }

}
/******************************************按键响应*******************************/
void MainWindow::on_pushButton_clicked()
{
    MySQL_Init();
    if(!is_Error)
    {
        show_tables();
        isConnect = true;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    table_init();
}

/********************************************************************************/
void MainWindow::show_tables()
{
    if(isConnect)
    {
        QString cmd = "show tables;";
        QSqlQuery query(cmd);

        char a = 0;
        ui->comboBox->clear();
        while(query.seek(a))
        {
            ui->comboBox->addItem(query.value(0).toString());
            a += 1;
        }
    }
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if(isConnect)
    {
        databases = ui->comboBox_2->currentText();
        ui->pushButton_2->setDisabled(true);
        ui->comboBox->clear();
        ui->pushButton->setEnabled(true);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    db_tables = ui->comboBox->currentText();
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setDisabled(true);
}

void MainWindow::on_actionrefresh_R_triggered()
{
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    isConnect = false;

//    QString cmd = "show databases;";
//    QSqlQuery query(cmd);
//    char a = 0;

//    while(query.seek(a))
//    {
//        ui->comboBox_2->addItem(query.value(0).toString());
//        a += 1;
//    }

    ui->pushButton->setEnabled(true);
}
/*******************************版本检测与升级********************************************/
//用于显示当前版本信息
void MainWindow::on_actionversion_V_triggered()
{
    QString ver = "版本信息：v";
    ver = ver.append(VERSION);
    version_info->information(NULL,"版本信息", ver);
}

//前往软件下载界面
void MainWindow::on_actionupdate_U_triggered()
{
    version_check();
    if(is_latest)
    {
        QString ver = "当前版本已为最新\n软件版本：";
        ver = ver.append(VERSION);
        version_info->information(NULL,"版本信息", ver);
    }
}
//检查升级
void MainWindow::version_check()
{
    QString latest_ver;
    QString info;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("47.100.173.197");//设置你远程服务器的IP
    db.setUserName("root");//数据库用户名和密码
    db.setPassword("cjluxk808");
    db.setDatabaseName("remote");//use test_qt;
    if (!db.open())
        ui->label->setText("网络连接失败！");
    QSqlQuery   query;
    query.prepare(QString("SELECT * FROM version;"));
    query.exec();
    query.last();
    latest_ver = query.value(0).toString();
    info = query.value(1).toString();

    //怕不是又要内存泄漏了
    Dialog  *dlg = new Dialog(latest_ver,info,this);
    //这里最后要改一下，因为版本是一致的
    if(latest_ver != VERSION)
    {
        dlg->show();
        is_latest = false;
    }
    else
    {
        is_latest = true;
    }

}
/***************************用于在两种不同的模式之间进行选择**********************************/
void MainWindow::on_actionview_V_triggered()
{
    if(ui->actionview_V->isChecked())
    {
        ui->actionedit_E->setChecked(false);
        view_mode = true;
        edit_mode = false;
    }
    else
    {
        ui->actionedit_E->setChecked(true);
        view_mode = false;
        edit_mode = true;
    }
}

void MainWindow::on_actionedit_E_triggered()
{
    if(ui->actionedit_E->isChecked())
    {
        ui->actionview_V->setChecked(false);
        view_mode = false;
        edit_mode = true;
    }
    else
    {
        ui->actionview_V->setChecked(true);
        view_mode = true;
        edit_mode = false;
    }
}
/*****************************************************************************************/

//用户反馈窗口，用于向服务器发送bug报告
void MainWindow::on_actiondevelop_D_triggered()
{
    Developer* dev = new Developer;
    dev->show();
}

//用于从服务器获取bug数据
void MainWindow::get_bug_info()
{
    //版本信息，bug报告
    QStringList titles;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("47.100.173.197");//设置你远程服务器的IP
    db.setUserName("root");//数据库用户名和密码
    db.setPassword("cjluxk808");
    db.setDatabaseName("remote");//use test_qt;
    if (!db.open())
        ui->label->setText("网络连接失败！");
    QSqlQuery   query;
    query.prepare(QString("SELECT * FROM problem;"));
    query.exec();
    QSqlRecord sqlRecord(query.record());
    int col = sqlRecord.count();

    char query_seek = 0;
    //用于控制query.value(datas)的显示列数,这个datas不知道为什么不能拿col直接替换掉
    int datas = 0;
    //获取列数
    for(int i = 0; i < sqlRecord.count(); i++)
    {
        datas = i;
    }
    //获取行数
    int initialPos = query.at();
    int row = 0;
    if (query.last())
    {
        row = query.at() + 1;
    }
    else
    {
        row = 0;
    }
    //对query进行复位
    query.seek(initialPos);

    titles << "版本信息" << "bug报告";
    MyList* lists = new MyList(col,row,titles,db_tables,this);

    while(query.seek(query_seek))
    {
        for(int b=0; b<=datas;b++)
        {
            lists->setItem(query_seek,b,new QTableWidgetItem(query.value(b).toString()));
        }
        query_seek += 1;
    }
    lists->show();
}

void MainWindow::on_actionbug_info_B_triggered()
{
    get_bug_info();
}

/***********************新的LineEdit响应函数********************************************/

void MainWindow::on_lineEdit_ip_returnPressed()
{
    ip = ui->lineEdit_ip->text();
}

void MainWindow::on_lineEdit_user_returnPressed()
{
    user = ui->lineEdit_user->text();
}

void MainWindow::on_lineEdit_pass_editingFinished()
{
    password = ui->lineEdit_pass->text();
}

void MainWindow::on_lineEdit_ip_textChanged(const QString &arg1)
{
    ip = ui->lineEdit_ip->text();
}

void MainWindow::on_lineEdit_user_textChanged(const QString &arg1)
{
    user = ui->lineEdit_user->text();
}

void MainWindow::on_lineEdit_pass_textChanged(const QString &arg1)
{
    password = ui->lineEdit_pass->text();
}

/************************************************************************************/

//连接到一个新的服务器
void MainWindow::on_actionnew_N_triggered()
{
    isConnect = false;
    ui->lineEdit_ip->clear();
    ui->lineEdit_pass->clear();
    ui->lineEdit_user->clear();
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->pushButton->setEnabled(true);
    //由于要重新初始化，这里加入一个mysql里自带的数据库
    databases = "mysql";
}
