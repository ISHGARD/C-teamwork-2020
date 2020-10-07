#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

static bool createconnect()
{
    QSqlDatabase user = QSqlDatabase::addDatabase("QSQLITE");

    user.setDatabaseName("../data/user.db");

    if( !user.open() )
    {
        QMessageBox::warning(0,"错误",user.lastError().text());
        return false;
    }

    return true;
}

#endif // CONNECTION_H
