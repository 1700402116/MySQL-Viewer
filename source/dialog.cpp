#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QString version, QString info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QFont font;
    font.setBold(true);

    ui->label_sta->setFont(font);
    ui->label_ver->setFont(font);
    ui->label_ver->setText(version);
    ui->label_cur_ver->setText(VERSION);
    //这里有个巨坑，中文逗号和英文句号都转为换行符
    info.replace(".","\n");
    info.replace("。","\n");
    ui->label_info->setText(info);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_updButton_yes_clicked()
{
    QUrl    web;
    web = "http://47.100.173.197//1.rar";
    QDesktopServices::openUrl(web);
}

void Dialog::on_updButton_no_clicked()
{
    QDialog::accept();
}
