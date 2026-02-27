#include "faculties.h"
#include "ui_faculties.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

faculties::faculties(QWidget *parent, QSqlDatabase &db)
    : QMainWindow(parent),
    ui(new Ui::faculties),
    dbconn(db)
{
    ui->setupUi(this);
    ui->twData->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->twData->setSelectionBehavior(QAbstractItemView::SelectRows);
}

faculties::~faculties()
{
    delete ui;
}

void faculties::loadFaculties(const QString &ID)
{
    // Очищаем таблицу перед загрузкой новых данных
    ui->twData->clearContents();
    ui->twData->setRowCount(0);

    // Создаем и подготавливаем SQL-запрос
    QSqlQuery query(dbconn);
    query.prepare(R"(
        SELECT f.id_faculty, f.title, h.title
        FROM faculties AS f JOIN housings AS h ON f.id_housing = h.id_housing
        WHERE f.id_housing = :id;
    )");
    query.bindValue(":id", ID);

    // Выполняем запрос
    if (!query.exec())
    {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось загрузить историю посещений:\n" +
                                  query.lastError().text());
        return;
    }

    QStringList headers = {"ID", "Faculty title", "Housing title"};
    ui->twData->setColumnCount(headers.size());
    ui->twData->setHorizontalHeaderLabels(headers);

    int row = 0;
    while(query.next()) {
        ui->twData->insertRow(row);

        // Добавляем данные в каждую колонку
        for(int col = 0; col < headers.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->twData->setItem(row, col, item);
        }
        row++;
    }


    ui->twData->resizeColumnsToContents();
    ui->twData->horizontalHeader()->setStretchLastSection(true);
}
