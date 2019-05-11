#ifndef MYLIST_H
#define MYLIST_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QFont>

namespace Ui {
class MyList;
}

class MyList : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyList(int col,int row,
                    QStringList header, QString db_tables,
                    QWidget *parent = nullptr);
    ~MyList();

    void setItem(int row, int column, QTableWidgetItem* widget);

private slots:
    void mySortByColumn(int column);
private:
    Ui::MyList *ui;
};

#endif // MYLIST_H
