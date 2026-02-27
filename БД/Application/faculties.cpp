#include "faculties.h"
#include "ui_faculties.h"
#include <QMessageBox>

faculties::faculties(QWidget *parent, QSqlDatabase *db)
    : QMainWindow(parent)
    , ui(new Ui::faculties)
    , dbconn(db)
{
    ui->setupUi(this);

    // Настройка таблицы
    ui->twData->setColumnCount(3);
    ui->twData->setHorizontalHeaderLabels({"ID", "Факультет", "Корпус"});
    ui->twData->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twData->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->twData->horizontalHeader()->setStretchLastSection(true);

    // Подключение сигналов
    connect(ui->btnAdd, &QPushButton::clicked, this, &faculties::add);
    connect(ui->btnEdit, &QPushButton::clicked, this, &faculties::edit);
    connect(ui->btnDel, &QPushButton::clicked, this, &faculties::del);
    connect(ui->twData, &QTableWidget::itemSelectionChanged, this, &faculties::populateFieldsFromSelectedRow);
}

faculties::~faculties()
{
    delete ui;
}

void faculties::loadFaculties(const QString &housingId)
{
    if(!dbconn || !dbconn->isOpen()) {
        QMessageBox::critical(this, "Ошибка", "Нет соединения с БД");
        return;
    }

    currentHousingId = housingId;
    ui->twData->clearContents();
    ui->twData->setRowCount(0);

    QSqlQuery query(*dbconn);
    query.prepare("SELECT f.id_faculty, f.title, h.title "
                  "FROM faculties f JOIN housings h ON f.id_housing = h.id_housing "
                  "WHERE f.id_housing = ? ORDER BY f.id_faculty");
    query.bindValue(0, housingId);

    if(!query.exec()) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    int row = 0;
    while(query.next()) {
        ui->twData->insertRow(row);
        for(int col = 0; col < 3; ++col) {
            ui->twData->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }
    ui->leHousingId->setText(housingId);
}

void faculties::setHousingId(const QString &id)
{
    currentHousingId = id;
    ui->leHousingId->setText(id);
}

void faculties::add()
{
    if(!dbconn || !dbconn->isOpen()) {
        QMessageBox::critical(this, "Ошибка", "Нет соединения с БД");
        return;
    }

    QString id = ui->leId->text().trimmed();
    QString title = ui->teTitle->toPlainText().trimmed();
    QString housingId = ui->leHousingId->text().trimmed();

    if(id.isEmpty() || title.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Заполните ID и название факультета");
        return;
    }

    if(validateFacultyId(id)) {
        QMessageBox::warning(this, "Предупреждение", "Факультет с таким ID уже существует");
        return;
    }

    QSqlQuery query(*dbconn);
    query.prepare("INSERT INTO faculties (id_faculty, title, id_housing) VALUES (?, ?, ?)");
    query.bindValue(0, id);
    query.bindValue(1, title);
    query.bindValue(2, housingId);

    if(!query.exec()) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    clearInputFields();
    loadFaculties(housingId);
}

void faculties::edit()
{
    int row = ui->twData->currentRow();
    if(row < 0) {
        QMessageBox::warning(this, "Предупреждение", "Выберите факультет для редактирования");
        return;
    }

    QString oldId = ui->twData->item(row, 0)->text();
    QString newId = ui->leId->text().trimmed();
    QString title = ui->teTitle->toPlainText().trimmed();
    QString housingId = ui->leHousingId->text().trimmed();

    if(QMessageBox::question(this, "Подтверждение", "Подтвердите редактирование факультета",
                              QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    if(newId != oldId && validateFacultyId(newId)) {
        QMessageBox::warning(this, "Предупреждение", "Факультет с таким ID уже существует");
        return;
    }

    QSqlQuery query(*dbconn);
    query.prepare("UPDATE faculties SET id_faculty=?, title=?, id_housing=? WHERE id_faculty=?");
    query.bindValue(0, newId);
    query.bindValue(1, title);
    query.bindValue(2, housingId);
    query.bindValue(3, oldId);

    if(!query.exec()) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    loadFaculties(housingId);
}

void faculties::del()
{
    int row = ui->twData->currentRow();
    if(row < 0) {
        QMessageBox::warning(this, "Предупреждение", "Выберите факультет для удаления");
        return;
    }

    QString id = ui->twData->item(row, 0)->text();

    if(QMessageBox::question(this, "Подтверждение", "Удалить выбранный факультет?",
                              QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    QSqlQuery query(*dbconn);
    query.prepare("DELETE FROM faculties WHERE id_faculty=?");
    query.bindValue(0, id);

    if(!query.exec()) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    loadFaculties(currentHousingId);
}

bool faculties::validateFacultyId(const QString &id)
{
    QSqlQuery query(*dbconn);
    query.prepare("SELECT 1 FROM faculties WHERE id_faculty=?");
    query.bindValue(0, id);
    return query.exec() && query.next();
}

void faculties::clearInputFields()
{
    ui->leId->clear();
    ui->teTitle->clear();
}

void faculties::populateFieldsFromSelectedRow()
{
    int row = ui->twData->currentRow();
    if(row >= 0) {
        ui->leId->setText(ui->twData->item(row, 0)->text());
        ui->teTitle->setPlainText(ui->twData->item(row, 1)->text());
    }
}
