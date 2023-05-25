#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QObject>
#include <QDir>
#include <QCoreApplication>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_HOSTNAME "HospitalDatabase"
#define DATABASE_NAME "HospitalDatabase.db"

#define TABLE_USERS "userstable"
#define ATTR_USERS_LOGIN "login"
#define ATTR_USERS_PASSWORD "password"
#define ATTR_USERS_NAME "fio"
#define ATTR_USERS_CITY "city"
#define ATTR_USERS_DISTRICT "district"
#define ATTR_USERS_HOSPITAL "hospital"
#define ATTR_USERS_ROLE "role"

#define TABLE_RECORDS "patientinfotable"
#define ATTR_RECORDS_DOCTOR_FIO "doctor_fio"
#define ATTR_RECORDS_HOSPITAL_NAME "hospital_name"
#define ATTR_RECORDS_CITY "city"
#define ATTR_RECORDS_DISTRICT "district"
#define ATTR_RECORDS_PATIENT_FIO "patient_fio"
#define ATTR_RECORDS_PATIENT_SEX "sex"
#define ATTR_RECORDS_DATE_OF_BIRTH "date_of_birth"
#define ATTR_RECORDS_DATE_OF_RECORD "date_of_record"
#define ATTR_RECORDS_SYMPTOMS "symptoms"


class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    void connectToDataBase();
    bool deleteRow(QString table, QString id, QString value);
    bool execQuery(QString queryStr);
    bool isExist(QString tableName, QString keyName, QString key);

private:
    QSqlDatabase    db;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();

public slots:
//    bool inserIntoTable(const QVariantList &data);
//    bool removeRecord(const int id);
};

#endif // DATABASEHELPER_H
