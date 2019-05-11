#ifndef DEVELOPER_H
#define DEVELOPER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Developer;
}

class Developer : public QDialog
{
    Q_OBJECT

public:
    explicit Developer(QWidget *parent = nullptr);
    ~Developer();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Developer *ui;

    QPalette succeed;
    QPalette failed;
    QString anti_repeat;

    bool isFirst;

    void SQLConnecting();
};

#endif // DEVELOPER_H
