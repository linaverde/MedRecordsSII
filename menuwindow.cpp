#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <QFileDialog>
#include "authwindow.h"
#include "constants.h"
#include "addpatientinfodialog.h"
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    connect(ui->loadFileButton, SIGNAL(clicked()), this, SLOT(loadClicked()));
    connect(ui->fillPatientButton, SIGNAL(clicked()), this, SLOT(patientClicked()));
    connect(ui->downloadFileButton, SIGNAL(clicked()), this, SLOT(downloadClicked()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(logoutClicked()));
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::setUser(UserEntity user){
    this->user = user;
    ui->doctorFio->setText(user.fio);
    ui->hospitalInfo->setText(user.hospital + ", " + user.city + ", " + user.district);
    if (!user.isDoctor()){
        ui->fillPatientButton->hide();
        ui->overviewButton->hide();
        ui->loadFileButton->show();
        ui->downloadFileButton->show();
    }
    if (!user.isAdmin()){
        ui->fillPatientButton->show();
        ui->overviewButton->show();
        ui->loadFileButton->hide();
        ui->downloadFileButton->hide();
    }
    ui->overviewButton->hide();
}

void MenuWindow::loadClicked(){
    QString filename = QFileDialog::getOpenFileName(this,
             tr("Open model file"), QDir::currentPath(), tr("TXT files (*.txt)"));
        QFile model(filename);

        model.open(QIODevice::ReadOnly|QIODevice::Text);
        QByteArray data = model.readAll();
        model.close();

            QString saveFileName = DESEASE_FILENAME;
            QFileInfo fileInfo(saveFileName);

            QDir::setCurrent(fileInfo.path());

            QFile newFile(saveFileName);
            if (!newFile.open(QIODevice::WriteOnly))
            {
                return;
            }

            newFile.write(data);
            newFile.close();
}

void MenuWindow::patientClicked(){
    AddPatientInfoDialog *w = new AddPatientInfoDialog();
    w->setUser(this->user);
    w->show();
}

void MenuWindow::logoutClicked(){
    AuthWindow *w = new AuthWindow();
    w->show();
    this->close();
}

void MenuWindow::downloadClicked(){
    QSqlQuery records;
    records.exec("SELECT * FROM " TABLE_RECORDS);
    QJsonArray result = QJsonArray();
    while(records.next()){
        QJsonObject record = QJsonObject();

        QJsonObject doctor = QJsonObject();
        doctor.insert(ATTR_RECORDS_DOCTOR_FIO, record.value(ATTR_RECORDS_DOCTOR_FIO).toString());
        doctor.insert(ATTR_RECORDS_HOSPITAL_NAME, record.value(ATTR_RECORDS_HOSPITAL_NAME).toString());
        doctor.insert(ATTR_RECORDS_CITY, record.value(ATTR_RECORDS_CITY).toString());
        doctor.insert(ATTR_RECORDS_DISTRICT, record.value(ATTR_RECORDS_DISTRICT).toString());
        record.insert("doctor", doctor);

        QJsonObject patient;
        patient.insert(ATTR_RECORDS_PATIENT_FIO, record.value(ATTR_RECORDS_PATIENT_FIO).toString());
        patient.insert(ATTR_RECORDS_PATIENT_SEX, record.value(ATTR_RECORDS_PATIENT_SEX).toString());
        patient.insert(ATTR_RECORDS_DATE_OF_BIRTH, record.value(ATTR_RECORDS_DATE_OF_BIRTH).toString());
        record.insert("patient", patient);

        record.insert(ATTR_RECORDS_DATE_OF_RECORD, record.value(ATTR_RECORDS_DATE_OF_RECORD).toString());
        QStringList symptoms = record.value(ATTR_RECORDS_SYMPTOMS).toString().split(",");
        QJsonArray symptomsArray = QJsonArray();
        QString symptom;
        foreach(symptom, symptoms){
            symptomsArray.append(symptom);
        }
        record.insert("records", symptomsArray);
        result.append(record);
    }

    //save config json

    // С помощью диалогового окна получаем имя файла с абсолютным путём
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save GenerateModelConfig"),
                                                        QString(),
                                                        tr("JSON (*.json)"));
    QFileInfo fileInfo(saveFileName);
    QDir::setCurrent(fileInfo.path());

    QFile jsonFile(saveFileName);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    jsonFile.write(QJsonDocument(result).toJson(QJsonDocument::Indented));
    jsonFile.close();
}
