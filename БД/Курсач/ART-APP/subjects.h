#ifndef SUBJECTS_H
#define SUBJECTS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QTableView>
#include <QVBoxLayout>
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QDateTime>
#include <QCompleter>
#include <QSqlError>
#include <QSqlRecord>
#include "globals.h"
#pragma once

namespace Ui {
class Subjects;
}

class Subjects : public QWidget
{
    Q_OBJECT

public:
    explicit Subjects(QWidget *parent = nullptr);
    ~Subjects();

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
    void on_btnHome_clicked();
    void on_btn_to_schedules_clicked();
    void on_le_search_sub_textChanged(const QString &text);
    void on_btnTeach_by_Sub_clicked();
    void on_btnStud_by_Sub_clicked();
    void on_btnSub_by_Fac_clicked();
    void on_btnAllSubs_clicked();


private:
    Ui::Subjects *ui;
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
    void fillFacultyComboBox();
    void fillSubjectsComboBox();
    int getNextAvailableId();
    void setupCompleters();
    void setupPermissions();
    QString getFacultyTitleById(const QString &id);
    QString getFacultyIdByTitle(const QString &title);
    QString getTeachersForSubject(const QString& subjectId);
    void generateTeachersPdf(QSqlQueryModel *model, const QString &title);
    void generateStudentsPdf(QSqlQueryModel *model, const QString &title);
    void generateSubjectsPdf(QSqlQueryModel *model, const QString &title);
    void generateAllSubjectsPdf(QSqlQueryModel *model, const QString &title);
};

#endif // SUBJECTS_H
