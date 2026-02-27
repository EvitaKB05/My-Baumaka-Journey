#ifndef MARKS_H
#define MARKS_H

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
class Marks;
}

class Marks : public QWidget
{
    Q_OBJECT

public:
    explicit Marks(QWidget *parent = nullptr);
    ~Marks();

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
    void on_le_search_mark_textChanged(const QString &text);
    void onTableRowClicked(int row);

    void on_btn_Marks_by_Stud_clicked();
    void on_btn_Marks_by_Teach_clicked();
    void on_btnMarks_by_Fac_clicked();
    void on_btn_Avg_Marks_by_All_Facs_clicked();

private:
    Ui::Marks *ui;
    QSqlDatabase dbconn;
    QSqlTableModel *model;
    int currentRow;
    QMap<QString, QString> studentMap;
    QMap<QString, QString> teacherMap;
    QMap<QString, QString> subjectMap;
    QMap<QString, QString> scheduleMap;

    void dbconnect();
    void setupModel();
    void setupTableWidget();
    void refreshTableData();
    void refreshFields();
    void clearFields();
    void highlightCurrentRowInTable();
    void fillStudentComboBox();
    void fillTeacherComboBox();
    void fillSubjectComboBox();
    void fillScheduleComboBox();
    void fillMarkTypeComboBox();
    void fillMarkComboBox();
    void setupCompleters();
    void setupPermissions();
    int getNextAvailableId();

    QString getStudentNameById(const QString &id);
    QString getStudentIdByName(const QString &name);
    QString getTeacherNameById(const QString &id);
    QString getTeacherIdByName(const QString &name);
    QString getSubjectTitleById(const QString &id);
    QString getSubjectIdByTitle(const QString &title);
    QString getScheduleDayById(const QString &id);
    QString getScheduleIdByDay(const QString &day);

    void generateReportPdf(QSqlQueryModel *model, const QString &title);
    QSqlQueryModel* getMarksByStudent(const QString &studentId);
    QSqlQueryModel* getMarksByTeacher(const QString &teacherId);
    QSqlQueryModel* getMarksByFaculty(const QString &facultyId);
    QSqlQueryModel* getAvgMarksByAllFaculties();
};

#endif // MARKS_H
