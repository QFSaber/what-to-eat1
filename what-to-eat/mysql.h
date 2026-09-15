#ifndef MYSQL_H
#define MYSQL_H
#include <QWidget>
#include "QDebug"
#include "QSqlDatabase"
#include "QMessageBox"
#include "QSqlError"
#include "QSqlQuery"
#include "QString"
class MySql : public QWidget
{
    Q_OBJECT
public:
    MySql();
    QString ShowData(int INDEX,bool South,bool Nourth,bool Drink);
    void InsertData(QString name1,bool South,bool North,bool Drink);
    void UpData();
    void DeleteData(QString name1);
    int getNumber(bool South,bool North,bool Drink);
signals:
};

#endif // MYSQL_H
