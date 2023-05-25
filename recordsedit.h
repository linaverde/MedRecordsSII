#ifndef RECORDSEDIT_H
#define RECORDSEDIT_H

#include <QWidget>

namespace Ui {
class RecordsEdit;
}

class RecordsEdit : public QWidget
{
    Q_OBJECT

public:
    explicit RecordsEdit(QWidget *parent = nullptr);
    ~RecordsEdit();

private:
    Ui::RecordsEdit *ui;
};

#endif // RECORDSEDIT_H
