#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "mylist.h"
#include "developer.h"

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlTableModel>
#include <QVBoxLayout>
#include <QtDebug>
#include <QtSql/QSqlRecord>
#include <QLabel>
#include <QMessageBox>
#include <QFont>
#include <QSqlField>
#include <QLibrary>
//每次升级程序后，除了更改数据库中的版本信息外，还要改变VERSION
#define VERSION "1.2.6"
#define DOWNLOAD_ADDR   "https://github.com/1700402116/MySQL-Viewer"
//mysql -h 47.100.179.226 -uroot -p293368902

//extern QString VERSION;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_actionrefresh_R_triggered();

    void on_actionversion_V_triggered();

    void on_actionview_V_triggered();

    void on_actionedit_E_triggered();

    void on_actiondevelop_D_triggered();

    void on_actionupdate_U_triggered();

    void on_actionbug_info_B_triggered();

    void on_lineEdit_ip_returnPressed();

    void on_lineEdit_user_returnPressed();

    void on_lineEdit_pass_editingFinished();

    void on_lineEdit_ip_textChanged(const QString &arg1);

    void on_lineEdit_user_textChanged(const QString &arg1);

    void on_lineEdit_pass_textChanged(const QString &arg1);

    void on_actionnew_N_triggered();

private:
    Ui::MainWindow *ui;
    void MySQL_Init();
    void table_init();
    void show_tables();
    void version_check();   //开启时自动检测更新
    void get_bug_info();

    QString ip;
    QString user;
    QString password;
    QString databases;
    QString db_tables;

    bool isConnect;
    bool view_mode;
    bool edit_mode;
    bool is_latest;
    bool is_Error;

    int col;
    int row;

    QMessageBox *version_info = new QMessageBox;
};

#endif // MAINWINDOW_H
