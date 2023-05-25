#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "userentity.h"

#include <QMainWindow>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();
    void setUser(UserEntity user);

private:
    UserEntity user;
    Ui::MenuWindow *ui;

private Q_SLOTS:
    void patientClicked();
//    void owerviewClicked();
    void loadClicked();
    void downloadClicked();
    void logoutClicked();
};

#endif // MENUWINDOW_H
