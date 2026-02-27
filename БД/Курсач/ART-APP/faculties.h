#ifndef FACULTIES_H
#define FACULTIES_H
#pragma once
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
#include <QTableWidgetItem>
#include "globals.h"

namespace Ui {
class Faculties;
}

class Faculties : public QWidget
{
    Q_OBJECT

public:
    explicit Faculties(QWidget *parent = nullptr);
    ~Faculties();

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
    void on_btn_to_housings_clicked();
    void on_btnHome_clicked();
    void on_le_search_f_textChanged(const QString &text);

private:
    Ui::Faculties *ui;
    QSqlDatabase dbconn;
    QSqlTableModel *model;
    int currentRow;
    QMap<QString, QString> housingMap;

    void dbconnect();
    void setupModel();
    void refreshFields();
    void clearFields();
    void fillTitleComboBox();
    void setupTableWidget();
    void refreshTableData();
    void onTableRowClicked(int row);
    void highlightCurrentRowInTable();
    void fillHousingComboBox();
    void setupPermissions();
    int getNextAvailableId();
    QString getHousingIdByTitle(const QString &title);
    QString getHousingTitleById(const QString &id);
};

#endif // FACULTIES_H
