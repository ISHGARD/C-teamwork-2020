#include "signup.h"
#include "ui_signup.h"
#include "connection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

signup::signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);



}

signup::~signup()
{
    delete ui;
}

void signup::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();

    QString username = ui->lineEdit_2->text();

    QString password = ui->lineEdit_3->text();

    QSqlQuery query;
    bool i = 1;
    int k;

    query.exec("select * from student");

    while(query.next())
    {
        qDebug() << query.value("name").toString();

        if(query.value("name").toString() == name)
        {
            QMessageBox::warning(this, "错误", "用户已存在");
            i = 0;
        }
        k = query.value("id").toInt();
    }

    k++;
    QString kk = QString::number(k);

    if(i)
    {
        query.exec(QString("insert into student(id, name, book, status, username, password, borrowtime ) "
                              "values(%1, '%2', '无', '正常', '%3', '%4', '无')")
                      .arg(kk).arg(name).arg(username).arg(password));

        query.exec();

        QMessageBox::information(this, "提示", "注册成功", QMessageBox::Ok);

        this->close();
    }

}
