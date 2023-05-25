#ifndef USERENTITY_H
#define USERENTITY_H

#include "databasehelper.h"

#define ROLE_DOCTOR "doctor"
#define ROLE_ADMIN "admin"

class UserEntity
{
public:
    UserEntity();
    UserEntity(QString fio, QString hospital, QString city, QString district, QString role);
    QString fio;
    QString hospital;
    QString city;
    QString district;
    QString role;

    bool isDoctor();
    bool isAdmin();
};

#endif // USERENTITY_H
