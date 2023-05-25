#ifndef ADDPATIENTINFODIALOG_H
#define ADDPATIENTINFODIALOG_H

#include <QDialog>
#include "deseasetreeitem.h"
#include "userentity.h"
#include <QListWidgetItem>

namespace Ui {
class AddPatientInfoDialog;
}

class AddPatientInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatientInfoDialog(QWidget *parent = nullptr);
    ~AddPatientInfoDialog();
    void setUser(UserEntity user);

private:
    UserEntity user;
    Ui::AddPatientInfoDialog *ui;
    bool getDesiasesData();

    TreeItem* currentSelectedGroup;

    QList<TreeItem> desiasesGroups;

    void parseData(QStringList lines, TreeItem *parentNode);

    void showGroup();
    void showGroup(TreeItem *parent);
    void showSymptoms(TreeItem *parent);
    void showSymptomsValues(TreeItem *parent);

private Q_SLOTS:
    void groupSelectionChanged();
    void symptomSelectionChanged();
    void symptomValueSelectionChanged();

    void onDeseaseGroupItemClicked(QListWidgetItem* item);

};

#endif // ADDPATIENTINFODIALOG_H
