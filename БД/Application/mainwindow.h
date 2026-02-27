#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlError>
#include "faculties.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSqlDatabase dbconn;

private slots:
    void dbconnect();
    void selectAll();
    void add();
    void del();
    void edit();
    void showFaculties();
    void onTableItemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    faculties *m_faculties;

    // Вспомогательные методы
    bool validateHousingId(const QString &id);
    void clearInputFields();
    void populateFieldsFromSelectedRow();
};

#endif // MAINWINDOW_H
