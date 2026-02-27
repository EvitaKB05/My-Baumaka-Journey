#ifndef PATIENTVISITS_H
#define PATIENTVISITS_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class patientvisits;
}

class patientvisits : public QMainWindow
{
    Q_OBJECT

public:
    explicit patientvisits(QWidget *parent = nullptr);
    ~patientvisits();
    void loadPatientVisits(const QString &cardId, QSqlDatabase &db);
private:
    Ui::patientvisits *ui;


};

#endif // PATIENTVISITS_H
