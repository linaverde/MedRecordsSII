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
    //connect(ui->listDeseaseGroup, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onDeseaseGroupItemClicked(QListWidgetItem*)));

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
        desiasesGroups.append(TreeItem(DeseaseItem(value)));
        while(currentLine.startsWith(value)){
            currentGroup.append(currentLine.mid(value.length()+2));
            if(!in.atEnd()){
                currentLine = in.readLine();
            } else {
                break;
            }
        }
        parseData(currentGroup, &desiasesGroups.last());
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
            value = currentLine.split("=>").first();
        }
        QStringList currentGroup;
        TreeItem* child = new TreeItem(DeseaseItem(value, isLast));
        parentNode->appendChild(child);
        while(currentLine.startsWith(value)){
            if(!isLast){
                currentGroup.append(currentLine.mid(value.length()+2));
            } else {
                currentGroup.append(currentLine.split("=>").last());
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
                child->appendChild(new TreeItem(DeseaseItem(i)));
            }
        }

    }
}

void AddPatientInfoDialog::showGroup(){
    QListWidget *listWidget = new QListWidget(this);
//    listWidget->addItem("Apple");
//    listWidget->addItem("Banana");
//    listWidget->addItem("Orange");

    ui->layoutDeseaseGroup->addWidget(listWidget);
//    QStringList labels;
//    ui->listDesiasesGroup.row
//    for(int i = 0; i < desiasesGroups.length(); i++){
//        QListWidgetItem *item = new QListWidgetItem();
//        item->setText(desiasesGroups.at(i).data().data);
//        ui->listDesiasesGroup->addItem(item);
    //}
//    ui->listDesiasesGroup->addItem("hello");
    //ui->listView->item
}

void AddPatientInfoDialog::showGroup(TreeItem *parent){

}

void AddPatientInfoDialog::showSymptoms(TreeItem *parent){

}

void AddPatientInfoDialog::showSymptomsValues(TreeItem *parent){

}

void AddPatientInfoDialog::groupSelectionChanged(){
    if(currentSelectedGroup == nullptr){

    }
}

void AddPatientInfoDialog::symptomSelectionChanged(){

}

void AddPatientInfoDialog::symptomValueSelectionChanged(){

}

void AddPatientInfoDialog::onDeseaseGroupItemClicked(QListWidgetItem* item){
    //item->
}


