#include "widget.h"
#include <QApplication>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    w.setWindowTitle("图书管理系统");

    w.show();

    return a.exec();
}
