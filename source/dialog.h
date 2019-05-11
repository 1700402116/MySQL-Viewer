#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QFont>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QString version, QString info, QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_updButton_yes_clicked();

    void on_updButton_no_clicked();

public:
    QString ver;

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
