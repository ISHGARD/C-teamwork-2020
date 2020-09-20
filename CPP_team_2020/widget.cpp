#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QButtonGroup>
#include <QDialog>
#include <QInputDialog>
#include <QTime>

int statu = 0, tabl = 0;
QString bor, id_s, statu_s, time_s, book_s;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->pushButton_user->hide();
    ui->widget_manager->hide();
    ui->widget_user->hide();
    ui->widget_logout->hide();

    QSqlDatabase user = QSqlDatabase::addDatabase("QSQLITE");
    user.setDatabaseName("user.db");

    if( !user.open() )
    {
        QMessageBox::warning(this,"错误",user.lastError().text());
        return ;
    }

    QSqlQuery q_user;

    q_user.exec("create table student("
                "id int primary key,"
                "name varchar(255),"
                "book vachar(255),"
                "status varchar(30),"
                "username varchar(30),"
                "password varchar(30),"
                "borrowtime varchar(50))");

    q_user.exec("create table manager("
                "id int primary key,"
                "username varchar(30),"
                "password varchar(30))");

    q_user.exec("create table book("
                "id int primary key,"
                "name varchar(50),"
                "type varchar(30),"
                "publisher varchar(50),"
                "publisher_year int,"
                "author varchar(50),"
                "status varchar(30))");

    //q_user.exec("insert into manager(id, username, password ) "
    //            "values(2, 'chenzhenjie', '2561203429')");

    //q_user.exec("insert into student(id, name, book, status, username, password, borrowtime ) "
    //            "values(2, '曹笛', '无', '正常', 'caodi', '2972049273', '无')");

    //q_user.exec("insert into book(id, name, type, publisher, publisher_year, author, status ) "
    //            "values(2, '高等数学（下）', '教材', '高等教育出版社', 2019, '南京理工大学理学院', '空闲')");

    mod = new QSqlTableModel(ui->tableView);
    mod -> setTable("book");

    ui -> tableView -> setModel(mod);

    mod -> select();

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->pushButton_login , &QPushButton::clicked , [=] () mutable{   //登录
    bool k = ui->checkBox_manager->isChecked(), jud = 0 ,jud2 = 0;

    QString a = ui->lineEdit_username->text(),
            b = ui->lineEdit_password->text(), te ;

    if( k == 1 )                                                    //管理员登录
    {
        q_user.exec("select * from manager");

         while(q_user.next())
         {
             if(q_user.value("username").toString() == a )
             {
                 jud = 1;
                 if(q_user.value("password").toString() == b )
                 {
                     jud2 = 1;
                     statu = 1;
                     mod->setEditStrategy(QSqlTableModel::OnManualSubmit);
                     ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
                 }
                 break;
             }

         }

         if(jud == 1 && jud2 == 1)
         {
             statu = 1;
             ui->widget_log->hide();
             ui->widget_manager->show();
             ui->pushButton_user->show();
             ui->widget_user->hide();
             ui->widget_logout->show();
             mod->setEditStrategy(QSqlTableModel::OnManualSubmit);
         }
    }

    if( k == 0 )                                                  //学生登陆
    {
         q_user.exec("select * from student");

         while(q_user.next())
         {
             if(q_user.value("username").toString() == a )
             {
                 jud = 1;

                 if(q_user.value("password").toString() == b )
                 {
                     jud2 = 1;
                     statu = 2;
                     int d;

                     d = q_user.value("id").toInt();                      //存id
                     id_s = QString::number(d);
                     qDebug() << id_s;

                     statu_s = q_user.value("status").toString();         //存状态
                     qDebug() << statu_s;

                     time_s = q_user.value("borrowtime").toString();       //存时间
                     qDebug() << time_s;

                     book_s = q_user.value("book").toString();       //存书
                     qDebug() << book_s;

                     te = q_user.value("name").toString();
                 }

                 break;
             }
         }

         if(jud == 1 && jud2 == 1 )
         {
             statu = 2;
             ui->widget_log->hide();
             ui->widget_user->show();
             ui->widget_logout->show();

             ui->label_wel->setText(QString("welcome! %1").arg(te));
         }
    }

    if( jud == 0 )
    {
        QMessageBox::warning(this,"登陆失败","账号不存在");
    }
    if( jud == 1 && jud2 == 0)
    {
        QMessageBox::warning(this,"登陆失败","密码错误");
    }

    });

    connect(ui->pushButton_logout , &QPushButton::clicked , [=]() mutable{   //退出
        if( statu == 1 )
        {
            ui->widget_manager->hide();
            ui->widget_user->hide();
            ui->pushButton_user->hide();
            ui->widget_logout->hide();
            ui->widget_log->show();
        }

        if( statu == 2 )
        {
            ui->widget_user->hide();
            ui->widget_logout->hide();
            ui->label_wel->setText(QString("welcome!"));
            ui->widget_log->show();
        }
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        statu = 0;
        //ui->lineEdit_username->setText("");
        //ui->lineEdit_password->setText("");
        //ui->checkBox_manager->setChecked(0);

    });

    connect(ui->pushButton_user, &QPushButton::clicked, [=]() mutable{       //用户表
        if( tabl == 0 && statu == 1)
        {
            ui->radioButton_type->setText(QString("book"));

            mod->setTable("student");

            ui->tableView->setModel(mod);

            mod->select();

            mod->setEditStrategy(QSqlTableModel::OnManualSubmit);
            ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
            tabl = 1;
        }
    });

    connect(ui->pushButton_book, &QPushButton::clicked, [=]() mutable {       //图书表
        if( tabl == 1 && statu == 1)
        {
            ui->radioButton_type->setText(QString("type"));

            mod->setTable("book");

            ui->tableView->setModel(mod);

            mod->select();

            mod->setEditStrategy(QSqlTableModel::OnManualSubmit);
            ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
            tabl = 0;
        }
    });

    connect(ui->pushButton_borrow, &QPushButton::clicked, [=]() mutable{      //借书
        bool ok, jud = 0;

        int d = QInputDialog::getInt(this, tr("请输入图书的ID"), tr("ID:")
                                     , 0 , 0, 100000, 1, &ok );

        if( !ok )
        {
            QMessageBox::warning(this,"错误", "错误ID");
            return ;
        }

        QString di = QString::number(d);

        qDebug() << di;

        q_user.exec("select * from book");

         while(q_user.next())
         {
             if(q_user.value("id").toString() == di )
             {
                 qDebug() << "----";

                 jud = 1;

                 QString boo = q_user.value("name").toString();

                 QString timi = QDateTime::currentDateTime().toString("yyyy-MM-dd");
                 qDebug() << timi;

                 if( q_user.value("status").toString() == "空闲" && statu_s == "正常" )
                 {
                     time_s = timi;
                     book_s = q_user.value("name").toString();

                     q_user.prepare("update book set status=? where id=?");

                     q_user.addBindValue("借出");
                     q_user.addBindValue(di);

                     q_user.exec();

                     q_user.prepare("update student set status=?,book=?,borrowtime=? where id=?");

                     q_user.addBindValue("借阅");
                     q_user.addBindValue(boo);
                     q_user.addBindValue(timi);
                     q_user.addBindValue(id_s);

                     q_user.exec();

                 }
                 else if(q_user.value("status").toString() != "空闲")
                 {
                     QMessageBox::warning(this,"错误", "图书已经被借走");
                 }
                 else if(statu_s == "借阅")
                 {
                     QMessageBox::warning(this,"错误", "不能再借了");
                 }
                 else if(statu_s == "惩罚")
                 {
                     QMessageBox::warning(this,"错误", "禁止借书,请寻找管理员");
                 }

                 break;
             }

         }

        if( jud == 0 )
        {
            QMessageBox::warning(this,"错误", "图书不存在");
            return ;
        }

        on_pushButton_clicked(); //刷新

    });

    connect(ui->pushButton_return, &QPushButton::clicked, [=]() mutable {   //还书
        if( book_s == "无" )
        {
            QMessageBox::warning(this,"错误", "并未借阅书籍");
        }
        else
        {
            bool  jud = 0;
            int a;

            a = QMessageBox::question(this, "确认", QString("是否归还 %1").arg(book_s));

            if( a == QMessageBox::Yes )
            {
                q_user.exec("select * from book");

                while(q_user.next())
                {

                    if( q_user.value("name") == book_s )
                    {
                        jud = 1;

                        QString timo = QDateTime::currentDateTime().toString("yyyy-MM-dd");

                        qDebug() << timo;

                        int da = difference(timo, time_s);

                        qDebug() << da;

                        if( da <= 7 )
                        {

                            q_user.prepare("update book set status=? where name=?");

                            q_user.addBindValue("空闲");
                            q_user.addBindValue(book_s);

                            q_user.exec();

                            q_user.prepare("update student set status=?,book=?,borrowtime=? where id=?");

                            q_user.addBindValue("正常");
                            q_user.addBindValue("无");
                            q_user.addBindValue("无");
                            q_user.addBindValue(id_s);

                            q_user.exec();
                        }
                        else if( da > 7 )
                        {
                            q_user.prepare("update book set status=? where name=?");

                            q_user.addBindValue("空闲");
                            q_user.addBindValue(book_s);

                            q_user.exec();

                            q_user.prepare("update student set status=?,book=?,borrowtime=? where id=?");

                            q_user.addBindValue("惩罚");
                            q_user.addBindValue("无");
                            q_user.addBindValue("无");
                            q_user.addBindValue(id_s);

                            q_user.exec();
                        }

                    }
                }

                if( jud == 0 )
                {
                    QMessageBox::warning(this,"错误", "图书不存在，请寻找管理员");
                }

            }
        }

        on_pushButton_clicked(); //刷新

    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_insert_clicked()    //插入
{
    QSqlRecord rec = mod -> record();
    int row = mod->rowCount();
    mod->insertRecord(row, rec);
}

void Widget::on_pushButton_save_clicked()      //保存
{
    mod->submitAll();
}

void Widget::on_pushButton_cancle_clicked()    //取消
{
    mod->revertAll();
    mod->submitAll();
}

void Widget::on_pushButton_delete_clicked()    //删除
{
    QItemSelectionModel *smod = ui->tableView->selectionModel();
    QModelIndexList list = smod->selectedRows();
    for(int i = 0; i < list.size(); i++)
    {
        mod->removeRow(list.at(i).row() );
    }
}

void Widget::on_pushButton_search_clicked()     //查找
{
    QString sear = ui->lineEdit_search->text(), see;
    int statu_se = 0;

    if( ui->radioButton_ID->isChecked()) statu_se = 1;
    if( ui->radioButton_name->isChecked()) statu_se = 2;
    if( ui->radioButton_type->isChecked()) statu_se = 3;

    if( statu_se == 2 || statu_se == 0) see =  QString("name = '%1'").arg(sear);
    if( statu_se == 3 && tabl == 0) see = QString("type = '%1'").arg(sear);
    if( statu_se == 3 && tabl == 1) see = QString("book = '%1'").arg(sear);
    if( statu_se == 1 ) see = QString("id = %1").arg(sear);

    mod->setFilter(see);
    mod->select();
}

void Widget::on_pushButton_clicked()           //刷新
{
    if(tabl == 0)
    {
        mod->setTable("book");

        ui->tableView->setModel(mod);

        mod->select();
    }
    if( tabl == 1)
    {
        mod->setTable("student");

        ui->tableView->setModel(mod);

        mod->select();
    }
}

int Widget::Days(int y,int m,int d)
{
    int day;

    day=(y-1)*365+(y-1)/4-(y-1)/100+(y-1)/400;

    switch(m-1)
    {
    case 11:day+=30;

    case 10:day+=31;

    case 9:day+=30;

    case 8:day+=31;

    case 7:day+=31;

    case 6:day+=30;

    case 5:day+=31;

    case 4:day+=30;

    case 3:day+=31;

    case 2: if( y%4==0 && y%100!=0 || y%400==0 )
            day+=29;
            else day+=28;

    case 1:day+=31;

    case 0:day+=0;
    }

    day+=d;

    return day;
}

int Widget::difference(QString a, QString b)
{
    int year1,year2,month1,month2,day1,day2,n;
    QString y1,y2,m1,m2,d1,d2;
    bool ok=true;

    y1=a.left(4);
    y2=b.left(4);

    m1=a.mid(5,2);
    m2=b.mid(5,2);

    d1=a.mid(8,2);
    d2=b.mid(8,2);

    year1=y1.toInt(&ok,10);
    year2=y2.toInt(&ok,10);

    month1=m1.toInt(&ok,10);
    month2=m2.toInt(&ok,10);

    day1=d1.toInt(&ok,10);
    day2=d2.toInt(&ok,10);

    n=Days(year2,month2,day2)-Days(year1,month1,day1);
    return n;
}
