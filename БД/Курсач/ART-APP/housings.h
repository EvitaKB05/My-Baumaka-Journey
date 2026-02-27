#ifndef HOUSINGS_H
#define HOUSINGS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "globals.h"
#pragma once
namespace Ui {
class Housings;
}

class Housings : public QWidget
{
    Q_OBJECT

public:
    explicit Housings(QWidget *parent = nullptr);
    ~Housings();

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
    void on_btn_to_faculties_clicked();
    void on_btnHome_clicked();
    void on_le_search_h_textChanged(const QString &text);
    void fillTitleComboBox();

private:
    Ui::Housings *ui;
    QSqlDatabase dbconn;
    QSqlTableModel *model;
    int currentRow;

    void dbconnect();
    void refreshFields();
    void clearFields();
    void setupTableWidget();
    void refreshTableData();
    void onTableRowClicked(int row);
    void highlightCurrentRowInTable();
    void setupPermissions();
    int getNextAvailableId();
};

#endif // HOUSINGS_H
