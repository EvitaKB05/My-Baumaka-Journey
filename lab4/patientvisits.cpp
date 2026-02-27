#include "patientvisits.h"
#include "ui_patientvisits.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

patientvisits::patientvisits(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::patientvisits)
{
    ui->setupUi(this);
    setWindowTitle("История посещений пациента");
    ui->twVisits->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->twVisits->setSelectionBehavior(QAbstractItemView::SelectRows);
}

patientvisits::~patientvisits()
{
    delete ui;
}

void patientvisits::loadPatientVisits(const QString &PatientFio, QSqlDatabase &db)
{
    // Очищаем таблицу перед загрузкой новых данных
    ui->twVisits->clearContents();
    ui->twVisits->setRowCount(0);

    // Создаем и подготавливаем SQL-запрос
    QSqlQuery query(db);
    query.prepare(R"(
        SELECT *
        FROM writtens
        WHERE "Пациент" = :patient_fio
        ORDER BY "Дата приёма" DESC
    )");
    query.bindValue(":patient_fio", PatientFio);

    // Выполняем запрос
    if (!query.exec())
    {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось загрузить историю посещений:\n" +
                                  query.lastError().text());
        return;
    }

    QStringList headers = {"Дата приёма","Пациент", "Диагноз", "Врач", "Специальность врача"};
    ui->twVisits->setColumnCount(headers.size());
    ui->twVisits->setHorizontalHeaderLabels(headers);

    int row = 0;
    while(query.next()) {
        ui->twVisits->insertRow(row);

        // Добавляем данные в каждую колонку
        for(int col = 0; col < headers.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->twVisits->setItem(row, col, item);
        }
        row++;
    }


    ui->twVisits->resizeColumnsToContents();
    ui->twVisits->horizontalHeader()->setStretchLastSection(true);
}
