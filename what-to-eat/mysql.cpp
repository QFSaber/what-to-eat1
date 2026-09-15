#include "mysql.h"
#include "QDebug"
#include "QString"
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
MySql::MySql()
{
    db.open();
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("2");
    db.setUserName("root");
    db.setPassword("123456789");
    bool ok = db.open();
    if (ok){
        //QMessageBox::information(this,"infor","已经成功连接到数据库");
    }
    else {
        QMessageBox::information(this, "infor", "open failed");
        qDebug()<<"error open database because"<<db.lastError().text();
    }
}
int MySql::getNumber(bool South,bool North,bool Drink)
{
    //查询操作

    int i=0;
    if(South)
    {
        QSqlQuery query;
        query.exec("SELECT * FROM  south");
        while(query.next()){
            i++;
        }
        return i;
    }
    else if(North)
    {
        QSqlQuery query;
        query.exec("SELECT * FROM  north");
        while(query.next()){
            i++;
        }
        return i;
    }
    else if(Drink)
    {
        QSqlQuery query;
        query.exec("SELECT * FROM  drink");
        while(query.next()){
            i++;
        }
        return i;
    }
}
QString MySql::ShowData(int INDEX,bool South,bool North,bool Drink)
{
    QSqlQuery query;
    int i=0;
    if(North)
    {
        query.exec("SELECT * FROM north");
        while(query.next()){
            i++;
            if(i==INDEX)return query.value("name").toString().toUtf8().data();
        }
    }
    else if(South)
    {
        query.exec("SELECT * FROM south");
        while(query.next()){
            i++;
            if(i==INDEX)return query.value("name").toString().toUtf8().data();
        }
    }
    else if(Drink)
    {
        query.exec("SELECT * FROM drink");
        while(query.next()){
            i++;
            if(i==INDEX)return query.value("name").toString().toUtf8().data();
        }
    }


}
void MySql::InsertData(QString name1,bool South,bool North,bool Drink)
{
    bool result_successed;
    QSqlQuery insertQuery;
    QSqlQuery result = db.exec(" SELECT * FROM caidan");
    result.clear();
    qDebug()<<South<<' '<<North<<' '<<Drink<<'\n';
    // 使用绑定参数的方式插入数据，防止 SQL 注入攻击
    if(South)
    {

        insertQuery.prepare("INSERT INTO south(name) VALUES (:name)");
        insertQuery.bindValue(":name", name1);
        result_successed = insertQuery.exec();
    }
    else if(North)
    {
        insertQuery.prepare("INSERT INTO north(name) VALUES (:name)");
        insertQuery.bindValue(":name", name1);
        result_successed = insertQuery.exec();
    }
    else if(Drink)
    {
        insertQuery.prepare("INSERT INTO drink(name) VALUES (:name)");
        insertQuery.bindValue(":name", name1);
        result_successed = insertQuery.exec();
    }

    if(result_successed){
        qDebug()<<"插入成功！";
        QMessageBox::information(this,"提示","添加成功");
        return;
    }else {
        qDebug() << "插入失败！" ;
    }
}
void MySql::DeleteData(QString name1)
{
    QSqlQuery result = db.exec(" SELECT * FROM caidan");
    result.clear();
    // 使用绑定参数的方式插入数据，防止 SQL 注入攻击
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM caidan WHERE name=:name");
    deleteQuery.bindValue(":name", name1);

    bool result_successed =  deleteQuery.exec();

    if(result_successed){
        qDebug()<<"删除成功！";
        return;
    }else {
        qDebug() << "删除失败！" <<  deleteQuery.lastError().text();
    }
}
void MySql::UpData()
{
    QSqlQuery result = db.exec(" SELECT * FROM caidan");
    //ODBC更新数据
    result.clear();
    bool result_successed2 = result.exec("update users set score=10 where user_id=2");

    if(result_successed2){
        qDebug()<<"更新成功！";
    }else{
        qDebug()<<"更新失败！";
    }
}
