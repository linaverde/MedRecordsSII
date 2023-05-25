#include "authwindow.h"
#include "ui_authwindow.h"
#include <QCryptographicHash>
#include <QSqlQuery>
#include "databasehelper.h"
#include <QErrorMessage>
#include "userentity.h"
#include "menuwindow.h"

#define SALT "hospital_password_salt"

AuthWindow::AuthWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(loginClicked()));

}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::loginClicked(){
    QString login = ui->loginEdit->text();

    QByteArray pswNsalt (ui->passwordEdit->text().toStdString().c_str());
    pswNsalt.append(SALT);
    QString password = QCryptographicHash::hash(pswNsalt, QCryptographicHash::Sha256).toHex();

    QSqlQuery queryUser;
    QSqlQuery queryCount;
    queryCount.exec("SELECT COUNT(*) FROM " TABLE_USERS " WHERE " ATTR_USERS_LOGIN  " = '" + login + "'");
    queryCount.next();

    if (queryCount.value(0).toInt() == 0) {
            (new QErrorMessage(this))->showMessage("Пользователя с таким логином не существует");
            return;
    } else if(queryCount.value(0).toInt() == 1){
            queryUser.exec("SELECT * FROM " TABLE_USERS " WHERE " ATTR_USERS_LOGIN  " = '" + login + "'");
            queryUser.next();
            if (queryUser.value(1).toString() != password){
                (new QErrorMessage(this))->showMessage("Неверный пароль");
                return;
            }
            UserEntity user = UserEntity(
                        queryUser.value(2).toString(),
                        queryUser.value(3).toString(),
                        queryUser.value(4).toString(),
                        queryUser.value(5).toString(),
                        queryUser.value(6).toString());
            MenuWindow *menu = new MenuWindow();
            menu->setUser(user);
            menu->show();
            this->close();
    } else {
            (new QErrorMessage(this))->showMessage("Ошибка в базе данных, свяжитесь с системным адмиинистратором");
            return;
    }
}

