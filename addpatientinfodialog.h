#ifndef ADDPATIENTINFODIALOG_H
#define ADDPATIENTINFODIALOG_H

#include <QDialog>
#include "deseasetreeitem.h"
#include "userentity.h"
#include <QListWidgetItem>
#include <QListWidget>

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

    QListWidget *listGroupDesease = new QListWidget(this);
    QListWidget *listSymptoms = new QListWidget(this);
    QListWidget *listSymptomsValue = new QListWidget(this);
    QListWidget *listSelected = new QListWidget(this);

    TreeItem* currentGroup = nullptr;
    TreeItem *currentSymptom = nullptr;
    QList<TreeItem*> selectedValues;

    QList<TreeItem*> desiasesGroups;

    void parseData(QStringList lines, TreeItem *parentNode);

    void showGroup();
    void showGroup(TreeItem *parent);
    void showSymptoms(TreeItem *parent);
    void showSymptomsValues(TreeItem *parent);
    void updateSelected();
    QString formatSymptomSelected(TreeItem *symptom);

private Q_SLOTS:

    void onDeseaseGroupItemClicked(QListWidgetItem* item);
    void onSymptomItemClicked(QListWidgetItem* item);
    void onSymptomValueItemClicked(QListWidgetItem* item);
    void onSelectedValueItemClicked(QListWidgetItem* item);
    void onBackClicked();
    void onCancelClicked();
    void onSaveClicked();

};

#endif // ADDPATIENTINFODIALOG_H
