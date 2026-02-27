#ifndef STUDENTS_H
#define STUDENTS_H
#include <QTableView>
#include <QAbstractItemView>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QDebug>
#include <QMap>
#include <QInputDialog>
#include <QDialog>
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QDateTime>
#include "globals.h"
#pragma once


namespace Ui {
class Students;
}

class Students : public QWidget
{
    Q_OBJECT

public:
    explicit Students(QWidget *parent = nullptr);
    ~Students();

signals:
    void returnToMainMenu();

private slots:
    void on_btnPrevious_clicked();
    void on_btnAddNew_clicked();
    void on_btnEditRow_clicked();
    void on_btnDelete_clicked();
    void on_btnNext_clicked();
    void on_btnSave_clicked();
    void on_btnLast_clicked();
    void on_btn_to_marks_clicked();
    void on_btnHome_clicked();
    void on_le_search_st_textChanged(const QString &text);
    void on_btnStud_by_Fac_clicked();
    void on_btn_All_Studs_by_All_Facs_clicked();




private:
    Ui::Students *ui;
    QSqlDatabase dbconn;
    QSqlTableModel *model;
    int currentRow;
    QMap<QString, QString> facultyMap;

    void dbconnect();
    void setupModel();
    void refreshFields();
    void refreshTableData();
    void clearFields();
    void setupTableWidget();
    void highlightCurrentRowInTable();
    void onTableRowClicked(int row);
    void fillFioComboBox();
    void fillFacultyComboBox();
    void setupPermissions();
    int getNextAvailableId();
    void generateStudentsPdf(QSqlQueryModel *model, const QString &facultyTitle);
    void generateAllStudentsPdf(QSqlQueryModel *model, const QString &title);
    QString getFacultyIdByTitle(const QString &title);
    QString getFacultyTitleById(const QString &id);




};

#endif // STUDENTS_H
