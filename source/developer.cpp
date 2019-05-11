#include "developer.h"
#include "ui_developer.h"
#include "mainwindow.h"

Developer::Developer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Developer)
{
    ui->setupUi(this);
    SQLConnecting();
    isFirst = true;
}

Developer::~Developer()
{
    delete ui;
}

//连接服务器
void Developer::SQLConnecting()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    QFont font;
    QPalette succeed;
    QPalette failed;
    succeed.setColor(QPalette::WindowText,QColor(100,200,100));
    failed.setColor(QPalette::WindowText,QColor(200,50,50));

    font.setBold(true);

    db.setHostName("47.100.173.197");//设置你远程服务器的IP
    db.setUserName("root");//数据库用户名和密码
    db.setPassword("cjluxk808");
    db.setDatabaseName("remote");//use test_qt;
    if (!db.open())
    {
        ui->label_status->setPalette(failed);
        ui->label_status->setFont(font);
        ui->label_status->setText("连接出错");
        ui->pushButton->setDisabled(true);
    }
    else
    {
        ui->label_status->setPalette(succeed);
        ui->label_status->setFont(font);
        ui->label_status->setText("等待反馈");
    }
}

void Developer::on_pushButton_clicked()
{
    QPalette succeed;
    QPalette failed;
    //这里把VERSION直接赋值给一个变量，而不能直接在下面用VERSION
    QString version = VERSION;

    succeed.setColor(QPalette::WindowText,QColor(100,200,100));
    failed.setColor(QPalette::WindowText,QColor(200,50,50));

    QString info = ui->lineEdit->text();
    QString cmd = "INSERT INTO problem VALUES('";
    //如果直接用VERSION，在VERSION改变后此处的值不会发生改变
    cmd.append(version);
    cmd.append("','");
    cmd.append(info);
    cmd.append("');");

    if((anti_repeat == info)&&(!isFirst))
    {
        ui->label_status->setPalette(failed);
        ui->label_status->setText("内容重复");
    }
    else
    {
        QSqlQuery query(cmd);
        ui->label_status->setText("反馈成功");
        ui->pushButton->setDisabled(true);
    }
    //将第一次发送的数据记录下来，用于对之后的发送进行是否重复判断
    if(isFirst)
    {
        anti_repeat = info;
        isFirst = false;
    }
}

void Developer::on_lineEdit_returnPressed()
{
    QPalette succeed;
    QPalette failed;
    QString version = VERSION;
    succeed.setColor(QPalette::WindowText,QColor(100,200,100));
    failed.setColor(QPalette::WindowText,QColor(200,50,50));

    QString info = ui->lineEdit->text();
    QString cmd = "INSERT INTO problem VALUES('";
    cmd.append(version);
    cmd.append("','");
    cmd.append(info);
    cmd.append("');");

    if((anti_repeat == info)&&(!isFirst))
    {
        ui->label_status->setPalette(failed);
        ui->label_status->setText("内容重复");
    }
    else
    {
        QSqlQuery query(cmd);
        ui->label_status->setText("反馈成功");
        ui->pushButton->setDisabled(true);
    }
    //将第一次发送的数据记录下来，用于对之后的发送进行是否重复判断
    if(isFirst)
    {
        anti_repeat = info;
        isFirst = false;
    }
}

void Developer::on_lineEdit_textChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(true);
}
