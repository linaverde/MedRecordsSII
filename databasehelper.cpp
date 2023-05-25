#include "databasehelper.h"


DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

void DataBase::connectToDataBase()
{
    qDebug() << "Current path" << QCoreApplication::applicationDirPath();
    if(!QFile(QCoreApplication::applicationDirPath() + DATABASE_NAME).exists()){
        qDebug() << "Восстановление базы данных";
        this->restoreDataBase();
    } else {
        this->openDataBase();
        qDebug() << "Открытие базы данных";
    }
}


bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}


bool DataBase::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(QCoreApplication::applicationDirPath() + DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}


void DataBase::closeDataBase()
{
    db.close();
}

bool DataBase::deleteRow(QString table, QString id, QString value){
    QSqlQuery query;
    if (!query.exec("DELETE FROM " + table + " WHERE " + id + "= '" + value + "'")){
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::execQuery(QString queryStr){
    QSqlQuery query;
    if (!query.exec(queryStr)){
        qDebug() << "Ошибка выполнения запроса";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::isExist(QString tableName, QString keyName, QString key){
    QSqlQuery querySelect;
    if(!querySelect.exec("SELECT COUNT(*) FROM " + tableName + " WHERE " + keyName + " = '" + key + "'"))
    {
        qDebug() << "Error select from table " + tableName;
        qDebug() << querySelect.lastError().text();
        return false;
    } else {
        querySelect.next();
        return querySelect.value(0).toInt() > 0;
    }
}

bool DataBase::createTable()
{
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys=on");
    //создание таблицы пользователей
    if (!query.exec( "CREATE TABLE " TABLE_USERS " ("
                     ATTR_USERS_LOGIN " VARCHAR(255) PRIMARY KEY NOT NULL, "
                     ATTR_USERS_PASSWORD " TEXT NOT NULL, "
                     ATTR_USERS_NAME " VARCHAR(255) NOT NULL, "
                     ATTR_USERS_HOSPITAL " VARCHAR(255) , "
                     ATTR_USERS_CITY " VARCHAR(255) NOT NULL, "
                     ATTR_USERS_DISTRICT " VARCHAR(255) , "
                     ATTR_USERS_ROLE " VARCHAR(255) NOT NULL "
                     ")"
                     )){
        qDebug() << "DataBase: error of create " << TABLE_USERS;
        qDebug() << query.lastError().text();
        return false;
    }

    if(!query.exec("CREATE TABLE " TABLE_RECORDS " ("
                   ATTR_RECORDS_DOCTOR_FIO " TEXT NOT NULL, "
                   ATTR_RECORDS_HOSPITAL_NAME " TEXT NOT NULL, "
                   ATTR_RECORDS_CITY "	TEXT NOT NULL, "
                   ATTR_RECORDS_DISTRICT " TEXT, "
                   ATTR_RECORDS_PATIENT_FIO "	TEXT NOT NULL, "
                   ATTR_RECORDS_DATE_OF_BIRTH "	TEXT NOT NULL,"
                   ATTR_RECORDS_DATE_OF_RECORD	" TEXT NOT NULL,"
                   ATTR_RECORDS_SYMPTOMS " TEXT NOT NULL, "
                   ATTR_RECORDS_PATIENT_SEX "	TEXT NOT NULL, "
                   "PRIMARY KEY(" ATTR_RECORDS_DATE_OF_RECORD "," ATTR_RECORDS_PATIENT_FIO ", " ATTR_RECORDS_DATE_OF_RECORD ")"
                   )){
            qDebug() << "DataBase: error of create " << TABLE_USERS;
            qDebug() << query.lastError().text();
            return false;
}
    //создание таблицы записей о пациентах
    return true;
}
