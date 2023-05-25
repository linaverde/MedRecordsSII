#include "addpatientinfodialog.h"
#include "ui_addpatientinfodialog.h"
#include <QFile>
#include "constants.h"
#include <QErrorMessage>
#include <QTextStream>

AddPatientInfoDialog::AddPatientInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatientInfoDialog)
{
    getDesiasesData();
    ui->setupUi(this);
    //connect(ui->listDeseaseGroup, SIGNAL(itemSelectionChanged()), this, SLOT(groupSelectionChanged()));
    connect(listGroupDesease, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onDeseaseGroupItemClicked(QListWidgetItem*)));
    connect(listSymptoms, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onSymptomItemClicked(QListWidgetItem*)));
    connect(listSymptomsValue, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onSymptomValueItemClicked(QListWidgetItem*)));
    connect(listSelected, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onSelectedValueItemClicked(QListWidgetItem*)));
    connect(ui->groupBackButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));

    listGroupDesease->move(20, 400);
    listGroupDesease->resize(360, 620);
    listGroupDesease->show();


    listSymptoms->move(410, 400);
    listSymptoms->resize(360, 620);
    listSymptoms->show();

    listSymptomsValue->move(810, 400);
    listSymptomsValue->resize(360, 620);
    listSymptomsValue->show();

    listSelected->move(1210, 70);
    listSelected->resize(411, 951);
    listSelected->show();
}

AddPatientInfoDialog::~AddPatientInfoDialog()
{
    delete ui;
}

bool AddPatientInfoDialog::getDesiasesData() {

    QString filename = DESEASE_FILENAME;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        (new QErrorMessage(this))->showMessage("Нет данных о болезнях для создания записи о пациенте");
        this->close();
        return false;
    };

    QTextStream in(&file);
    in.setCodec("UTF-8");


    while(!in.atEnd()){
        QString currentLine = in.readLine();
        QString value = currentLine.split("::").first();
        QStringList currentGroup;
        desiasesGroups.append(new TreeItem(DeseaseItem(value)));
        while(currentLine.startsWith(value)){
            currentGroup.append(currentLine.mid(value.length()+2));
            if(!in.atEnd()){
                currentLine = in.readLine();
            } else {
                break;
            }
        }
        parseData(currentGroup, desiasesGroups.last());
    }
    file.close();

    showGroup();

}

void AddPatientInfoDialog::setUser(UserEntity user){
    this->user = user;
    ui->doctorFioEdit->setText(user.fio);
    ui->hospitalEdit->setText(user.hospital + ", " + user.city + ", " + user.district);
}

bool isLastGroup(QString line){
    return line.split("::").length() == 1;
}

void AddPatientInfoDialog::parseData(QStringList lines, TreeItem *parentNode){
    while(!lines.isEmpty()){
        bool isLast = isLastGroup(lines.first());
        QString value;
        QString currentLine = lines.first();
        if (!isLast){
            value = currentLine.split("::").first();
        } else {
            value = currentLine.split("|").first();
        }
        QStringList currentGroup;
        TreeItem* child = new TreeItem(DeseaseItem(value, isLast), parentNode);
        parentNode->appendChild(child);
        while(currentLine.startsWith(value)){
            if(!isLast){
                currentGroup.append(currentLine.mid(value.length()+2));
            } else {
                currentGroup.append(currentLine.split("|").last());
            }
            lines.removeFirst();
            if(!lines.isEmpty()){
                currentLine = lines.first();
            } else {
                break;
            }
        }
        if (!isLast){
            parseData(currentGroup, child);
        } else {
            for ( const auto& i : currentGroup  )
            {
                child->appendChild(new TreeItem(DeseaseItem(i), child));
            }
        }

    }
}

void AddPatientInfoDialog::showGroup(){
    listGroupDesease->clear();
    for(int i = 0; i < desiasesGroups.length(); i++){
        listGroupDesease->addItem(desiasesGroups.at(i)->data().data);
    }


}

void AddPatientInfoDialog::showGroup(TreeItem *parent){
    listGroupDesease->clear();
    for(int i = 0; i < parent->childCount(); i++){
        listGroupDesease->addItem(parent->child(i)->data().data);
    }
}

void AddPatientInfoDialog::showSymptoms(TreeItem *parent){
    listSymptoms->clear();
    for(int i = 0; i < parent->childCount(); i++){
        listSymptoms->addItem(parent->child(i)->data().data);
    }
}

void AddPatientInfoDialog::showSymptomsValues(TreeItem *parent){
    listSymptomsValue->clear();
    for(int i = 0; i < parent->childCount(); i++){
        listSymptomsValue->addItem(parent->child(i)->data().data);
    }
}


void AddPatientInfoDialog::onDeseaseGroupItemClicked(QListWidgetItem* item){
    listSymptomsValue->clear();
    listSymptoms->clear();
    if(currentGroup == nullptr){

        for(int i = 0; i < desiasesGroups.length(); i++){
            if(desiasesGroups.at(i)->data().data == item->text()){
                currentGroup = desiasesGroups.at(i);
                break;
            }
        }

        showGroup(currentGroup);

    } else {
        TreeItem *selected = nullptr;
        for(int i = 0; i < currentGroup->childCount(); i++){
            if(currentGroup->children().at(i)->data().data == item->text()){
                selected = currentGroup->children().at(i);
                break;
            }
        }

        if(selected == nullptr){
            TreeItem *group = currentGroup->parentItem();
            for(int i = 0; i < group->childCount(); i++){
                if(group->children().at(i)->data().data == item->text()){
                    selected = group->children().at(i);
                    break;
                }
            }
        }

        if(selected->child(0) != nullptr){
            currentGroup = selected;
            if(!selected->child(0)->data().isSymptom){
                showGroup(currentGroup);

            } else {
                showSymptoms(selected);
            }
        }
    }
}

void AddPatientInfoDialog::onSymptomItemClicked(QListWidgetItem* item){
    for(int i = 0; i < currentGroup->childCount(); i++){
        if (currentGroup->child(i)->data().data == item->text()){
            currentSymptom = currentGroup->child(i);
            break;
        }
    }
    showSymptomsValues(currentSymptom);
}

void AddPatientInfoDialog::onSymptomValueItemClicked(QListWidgetItem* item){
    TreeItem* selectedValue;
    for (int i = 0; i< currentSymptom->childCount(); i++){
        if(currentSymptom->child(i)->data().data == item->text()){
            selectedValue = currentSymptom->child(i);
            break;
        }
    }

    bool contains = false;
    for(int i = 0; i < selectedValues.length(); i++){
        if(formatSymptomSelected(selectedValues.at(i)) ==formatSymptomSelected(selectedValue)){
            contains = true;
            selectedValues.removeAt(i);
            break;
        }
    }
    if(!contains){
        selectedValues.append(selectedValue);
    }
    updateSelected();
}

void AddPatientInfoDialog::onSelectedValueItemClicked(QListWidgetItem* item){
    for(int i = 0; i < selectedValues.length(); i++){
        if(formatSymptomSelected(selectedValues.at(i)) == item->text()){
            selectedValues.removeAt(i);
            break;
        }
    }
    updateSelected();
}

void AddPatientInfoDialog::updateSelected(){
    listSelected->clear();
    for(int i = 0; i < selectedValues.length(); i++){
        TreeItem* symptom = selectedValues.at(i);
        QString value = formatSymptomSelected(symptom);
        listSelected->addItem(value);
    }
}


void AddPatientInfoDialog::onBackClicked(){
    listSymptomsValue->clear();
    listSymptoms->clear();
    currentSymptom = nullptr;
    if(currentGroup == nullptr) return;
    if(currentGroup->parentItem() != nullptr){
        currentGroup = currentGroup->parentItem();
        showGroup(currentGroup);
    } else {
        currentGroup = nullptr;
        showGroup();
    }
}

void AddPatientInfoDialog::onCancelClicked(){
    this->close();
}

QString formatDbSymptomValue(TreeItem* child){
    QString result;
    result = child->data().data;
    result = "=>"+result;
    while(child->parentItem() != nullptr){
        child = child->parentItem();
        result = child->data().data + result;
        if(child->parentItem()!= nullptr){
            result = "::"+result;
        }
    }
    return result;
}

void AddPatientInfoDialog::onSaveClicked(){
    QDateTime date = QDateTime::currentDateTime();
    QString formattedDate = date.toString("dd.MM.yyyy");

    QString symptoms;
    for (int i = 0; i <selectedValues.length(); i++){
        symptoms.append(formatDbSymptomValue(selectedValues.at(i)));
        if(i!=selectedValues.length()-1){
            symptoms.append(",");
        }
    }

    QSqlQuery insertQuery;
    if (insertQuery.exec("INSERT INTO " TABLE_RECORDS " (" ATTR_RECORDS_DOCTOR_FIO ", " ATTR_RECORDS_HOSPITAL_NAME ", " ATTR_RECORDS_CITY ", " ATTR_RECORDS_DISTRICT ", "
                      ATTR_RECORDS_PATIENT_FIO ", " ATTR_RECORDS_PATIENT_SEX ", " ATTR_RECORDS_DATE_OF_BIRTH ", " ATTR_RECORDS_DATE_OF_RECORD ", " ATTR_RECORDS_SYMPTOMS ")"
                      " VALUES ('" + user.fio + "', '" + user.hospital + "', '" + user.city + "', '"
                      + user.district + "', '" + ui->patientFioEdit->text() + "', '" + ui->patientSex->currentText() + "', '" +
                         ui->patientDateOfBirth->text() + "', '" + formattedDate + "', '" + symptoms+ "')")){

        currentGroup = nullptr;
        currentSymptom = nullptr;
        listSelected->clear();
        listSymptoms->clear();
        listSymptomsValue->clear();
        showGroup();
        selectedValues.clear();
        ui->patientFioEdit->clear();

    } else {
        (new QErrorMessage(this))->showMessage("Ошибка записи в базу данных");
        qDebug() << insertQuery.lastError();

    }
}

QString  AddPatientInfoDialog::formatSymptomSelected(TreeItem *symptom) {
    return symptom->parentItem()->parentItem()->data().data + ", "+ symptom->parentItem()->data().data + "=>" + symptom->data().data;
}
