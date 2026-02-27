#ifndef TEACHERS_H
#define TEACHERS_H

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
#include <QCompleter>
#include "globals.h"
#pragma once

namespace Ui {
class Teachers;
}

class Teachers : public QWidget
{
    Q_OBJECT

public:
    explicit Teachers(QWidget *parent = nullptr);
    ~Teachers();

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
    void on_btn_to_schedules_clicked();
    void on_btnHome_clicked();
    void on_le_search_te_textChanged(const QString &text);
    void on_btnTeach_by_Fac_clicked();
    void on_btn_All_Teach_by_All_Facs_clicked();

private:
    Ui::Teachers *ui;
    QSqlDatabase dbconn;
    QSqlTableModel *model;
    int currentRow;
    QMap<QString, QString> facultyMap;
    QMap<QString, QString> postMap;

    void dbconnect();
    void setupModel();

    void refreshFields();
    void refreshTableData();
    void clearFields();
    void setupTableWidget();
    void highlightCurrentRowInTable();
    void onTableRowClicked(int row);
    void setupPermissions();

    void fillFioComboBox();
    void fillFacultyComboBox();
    void fillPostComboBox();
    int getNextAvailableId();


    QString getFacultyIdByTitle(const QString &title);
    QString getFacultyTitleById(const QString &id);
    QString getPostIdByTitle(const QString &title);
    QString getPostTitleById(const QString &id);


    void generateTeachersPdf(QSqlQueryModel *model, const QString &facultyTitle);
    void generateAllTeachersPdf(QSqlQueryModel *model, const QString &title);
    void setupPostCompleter();
    void setupFacultyCompleter();
};

#endif // TEACHERS_H
