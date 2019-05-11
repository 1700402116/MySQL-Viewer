#ifndef MYSQLLIST_H
#define MYSQLLIST_H

#include <QMainWindow>

static int col;
static int row;

namespace Ui {
class MySQLlist;
}

class MySQLlist : public QMainWindow
{
    Q_OBJECT

public:
    explicit MySQLlist(QWidget *parent = nullptr);
    ~MySQLlist();

private:
    Ui::MySQLlist *ui;
};

#endif // MYSQLLIST_H
