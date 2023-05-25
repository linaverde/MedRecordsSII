#include "userentity.h"

UserEntity::UserEntity()
{

}

UserEntity::UserEntity(QString fio, QString hospital, QString city, QString district, QString role){
    this->fio = fio;
    this->hospital = hospital;
    this->city = city;
    this->district = district;
    this->role = role;
}

bool UserEntity::isDoctor(){
    return this->role.contains(ROLE_DOCTOR);
}

bool UserEntity::isAdmin(){
    return this->role.contains(ROLE_ADMIN);
}
