#include <QPainter>

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

            else
            day+=28;

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

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p;
    p.begin(this);

    p.drawPixmap(0, 0, width(), height(), QPixmap("../image/timg.jpg"));

    p.end();
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
