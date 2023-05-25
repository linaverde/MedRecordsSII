#include "recordsedit.h"
#include "ui_recordsedit.h"

RecordsEdit::RecordsEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordsEdit)
{
    ui->setupUi(this);
}

RecordsEdit::~RecordsEdit()
{
    delete ui;
}
