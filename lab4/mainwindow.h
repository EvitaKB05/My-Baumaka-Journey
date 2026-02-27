#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QSqlDatabase>
#include "patientvisits.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    patientvisits *m_patientVisits;

public slots:
    void dbconnect();
    void selectAll();
    void add();
    void del();
    void edit();
    void upd();
    void showPatientVisits();
    void loadMedicalCard();

private:
    QSqlDatabase dbconn;
    Ui::MainWindow *ui;
    patientvisits *visitsForm;


};
#endif // MAINWINDOW_H
