#ifndef SCHEDULES_H
#define SCHEDULES_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include "globals.h"
#pragma once

namespace Ui {
class Schedules;
}

class Schedules : public QWidget
{
    Q_OBJECT

public:
    explicit Schedules(QWidget *parent = nullptr);
    ~Schedules();

signals:
    void returnToMainMenu();

private slots:
    void on_btnPrevious_clicked();
    void on_btnNext_clicked();
    void on_btnLast_clicked();
    void on_btnAddNew_clicked();
    void on_btnEditRow_clicked();
    void on_btnDelete_clicked();
    void on_btnSave_clicked();
    void on_btnHome_clicked();
    void on_btn_to_Teachers_clicked();
    void on_le_search_sched_textChanged(const QString &text);
    void onTableRowClicked(int row);

    void on_btn_Sched_by_Fac_clicked();
    void on_btnSched_by_Teach_clicked();
    void on_btn_All_Scheds_clicked();

private:
    Ui::Schedules *ui;
    QSqlDatabase dbconn;
    QSqlTableModel *model;
    int currentRow;
    QMap<QString, QString> facultyMap;
    QMap<QString, QString> teacherMap;
    QMap<QString, QString> subjectMap;
    QMap<QString, QString> housingMap;

    void dbconnect();
    void setupModel();
    void setupTableWidget();
    void refreshTableData();
    void refreshFields();
    void clearFields();
    void highlightCurrentRowInTable();
    void fillFacultyComboBox();
    void fillTeacherComboBox();
    void fillSubjectComboBox();
    void fillHousingComboBox();
    void fillWeekDayComboBox();
    int getNextAvailableId();
    void fillLessonTypeComboBox();
    void setupPermissions();
    void setupCompleters();

    QString getFacultyTitleById(const QString &id);
    QString getFacultyIdByTitle(const QString &title);
    QString getTeacherNameById(const QString &id);
    QString getTeacherIdByName(const QString &name);
    QString getSubjectTitleById(const QString &id);
    QString getSubjectIdByTitle(const QString &title);
    QString getHousingTitleById(const QString &id);
    QString getHousingIdByTitle(const QString &title);

    void generateReportPdf(QSqlQueryModel *model, const QString &title);
    QSqlQueryModel* getScheduleByFaculty(const QString &facultyId);
    QSqlQueryModel* getScheduleByTeacher(const QString &teacherId);
    QSqlQueryModel* getAllSchedules();
};

#endif // SCHEDULES_H
