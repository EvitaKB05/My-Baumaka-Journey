#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация подключений
    connect(ui->btnConnect, &QPushButton::clicked, this, &MainWindow::dbconnect);
    connect(ui->btnSelectAll, &QPushButton::clicked, this, &MainWindow::selectAll);
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::add);
    connect(ui->btnDel, &QPushButton::clicked, this, &MainWindow::del);
    connect(ui->btnEdit, &QPushButton::clicked, this, &MainWindow::edit);
    connect(ui->twData, &QTableWidget::itemDoubleClicked, this, &MainWindow::showFaculties);
    connect(ui->twData, &QTableWidget::itemSelectionChanged, this, &MainWindow::populateFieldsFromSelectedRow);

    // Настройка таблицы
    ui->twData->setColumnCount(3);
    ui->twData->setHorizontalHeaderLabels({"ID", "Название", "Адрес"});
    ui->twData->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twData->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->twData->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    if(dbconn.isOpen())
        dbconn.close();
    delete ui;
}

void MainWindow::dbconnect()
{
    if(!dbconn.isOpen()) {
        ui->teResult->append("Доступные драйверы SQL:");
        ui->teResult->append(QSqlDatabase::drivers().join(", "));

        dbconn = QSqlDatabase::addDatabase("QPSQL");
        dbconn.setDatabaseName("ART-APP");
        dbconn.setHostName("localhost");
        dbconn.setPort(5432);
        dbconn.setUserName("postgres");
        dbconn.setPassword("mrduckword532854");

        if(dbconn.open()) {
            ui->teResult->append("Соединение установлено успешно");
            selectAll();
        } else {
            ui->teResult->append("Ошибка подключения:");
            ui->teResult->append(dbconn.lastError().text());
        }
    } else {
        ui->teResult->append("Соединение уже установлено");
    }
}

void MainWindow::selectAll()
{
    ui->twData->clearContents();

    if(!dbconn.isOpen()) {
        dbconnect();
        if(!dbconn.isOpen()) {
            QMessageBox::critical(this, "Ошибка", dbconn.lastError().text());
            return;
        }
    }

    QSqlQuery query(dbconn);
    if(!query.exec("SELECT id_housing, title, address FROM housings ORDER BY id_housing")) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    ui->twData->setRowCount(query.size());
    int row = 0;
    while(query.next()) {
        for(int col = 0; col < 3; ++col) {
            ui->twData->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }
    ui->teResult->append(QString("Загружено %1 записей").arg(row));
}

void MainWindow::add()
{
    if(!dbconn.isOpen() && !dbconnect()) {
        QMessageBox::critical(this, "Ошибка", "Нет соединения с БД");
        return;
    }

    if(QMessageBox::question(this, "Подтверждение", "Хотите добавить новый корпус?",
                              QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    QString id = ui->leId->text().trimmed();
    QString title = ui->teTitle->toPlainText().trimmed();
    QString address = ui->leAddress->text().trimmed();

    if(id.isEmpty() || title.isEmpty() || address.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Все поля должны быть заполнены");
        return;
    }

    if(validateHousingId(id)) {
        QMessageBox::warning(this, "Предупреждение", "Корпус с таким ID уже существует!");
        return;
    }

    QSqlQuery query(dbconn);
    query.prepare("INSERT INTO housings (id_housing, title, address) VALUES (?, ?, ?)");
    query.bindValue(0, id);
    query.bindValue(1, title);
    query.bindValue(2, address);

    if(!query.exec()) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    ui->teResult->append(QString("Добавлен корпус: ID=%1, %2").arg(id).arg(title));
    clearInputFields();
    selectAll();
}

void MainWindow::edit()
{
    int row = ui->twData->currentRow();
    if(row < 0) {
        QMessageBox::warning(this, "Предупреждение", "Выберите корпус для редактирования");
        return;
    }

    QString oldId = ui->twData->item(row, 0)->text();
    QString newId = ui->leId->text().trimmed();
    QString title = ui->teTitle->toPlainText().trimmed();
    QString address = ui->leAddress->text().trimmed();

    if(QMessageBox::question(this, "Подтверждение", "Вы действительно хотите изменить данные корпуса?",
                              QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    if(newId != oldId && validateHousingId(newId)) {
        QMessageBox::warning(this, "Предупреждение", "Корпус с таким ID уже существует!");
        return;
    }

    QSqlQuery query(dbconn);
    query.prepare("UPDATE housings SET id_housing=?, title=?, address=? WHERE id_housing=?");
    query.bindValue(0, newId);
    query.bindValue(1, title);
    query.bindValue(2, address);
    query.bindValue(3, oldId);

    if(!query.exec()) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    ui->teResult->append(QString("Обновлен корпус: ID=%1").arg(newId));
    selectAll();
}

void MainWindow::del()
{
    int row = ui->twData->currentRow();
    if(row < 0) {
        QMessageBox::warning(this, "Предупреждение", "Выберите корпус для удаления");
        return;
    }

    QString id = ui->twData->item(row, 0)->text();

    if(QMessageBox::question(this, "Подтверждение", "Вы действительно хотите удалить этот корпус?",
                              QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    QSqlQuery query(dbconn);
    query.prepare("DELETE FROM housings WHERE id_housing=?");
    query.bindValue(0, id);

    if(!query.exec()) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    ui->teResult->append(QString("Удален корпус: ID=%1").arg(id));
    selectAll();
}

void MainWindow::showFaculties()
{
    int row = ui->twData->currentRow();
    if(row < 0) return;

    QString housingId = ui->twData->item(row, 0)->text();

    if(!m_faculties) {
        m_faculties = new faculties(this, &dbconn);
    }

    m_faculties->setHousingId(housingId);
    m_faculties->loadFaculties(housingId);
    m_faculties->show();
    m_faculties->raise();
    m_faculties->activateWindow();
}

bool MainWindow::validateHousingId(const QString &id)
{
    QSqlQuery query(dbconn);
    query.prepare("SELECT 1 FROM housings WHERE id_housing=?");
    query.bindValue(0, id);
    return query.exec() && query.next();
}

void MainWindow::clearInputFields()
{
    ui->leId->clear();
    ui->teTitle->clear();
    ui->leAddress->clear();
}

void MainWindow::populateFieldsFromSelectedRow()
{
    int row = ui->twData->currentRow();
    if(row >= 0) {
        ui->leId->setText(ui->twData->item(row, 0)->text());
        ui->teTitle->setPlainText(ui->twData->item(row, 1)->text());
        ui->leAddress->setText(ui->twData->item(row, 2)->text());
    }
}
