#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlTableModel>
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

    int difference(QString a,QString b);

private slots:

    void on_pushButton_insert_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_cancle_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QSqlTableModel *mod;
};

#endif // WIDGET_H
