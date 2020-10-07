#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include "signup.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    int Days(int y,int m,int d);

    signup rr;

    int difference(QString a,QString b);

private slots:

    void on_pushButton_insert_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_cancle_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_clicked();

    void on_pushButton_signup_clicked();

private:
    Ui::Widget *ui;

    QSqlTableModel *mod;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // WIDGET_H
