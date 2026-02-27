#include "housings.h"
#include "ui_housings.h"
#include "faculties.h"


Housings::Housings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Housings)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal); // Блокирует родительское окно

    //setFixedSize(856, 479);

    dbconnect();

    model = new QSqlTableModel(this, dbconn);
    model->setTable("housings");
    model->select();

    // Настройка таблицы twData_h
    setupTableWidget();
    setupPermissions();
    currentRow = 0;
    refreshFields();
    fillTitleComboBox();
}

Housings::~Housings()
{
    delete ui;
}

void Housings::setupTableWidget()
{
    // Настройка заголовков таблицы
    ui->twData_h->setColumnCount(3);
    ui->twData_h->setHorizontalHeaderLabels({"ID", "Название", "Адрес"});

     ui->twData_h->setColumnHidden(0, true);


    ui->twData_h->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twData_h->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData_h->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Заполнение таблицы данными
    refreshTableData();

    // Подключение сигнала выбора строки
    connect(ui->twData_h, &QTableWidget::cellClicked, this, &Housings::onTableRowClicked);

    // Настройка ширины столбцов
    ui->twData_h->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void Housings::refreshTableData()
{
    ui->twData_h->setRowCount(0); // Очищаем

    QSqlQuery query("SELECT id_housing, title, address FROM housings ORDER BY id_housing");
    int row = 0;

    while (query.next()) {
        ui->twData_h->insertRow(row);

        for (int col = 0; col < 3; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->twData_h->setItem(row, col, item);
        }

        row++;
    }
}

void Housings::onTableRowClicked(int row)
{
    // Получаем ID из выбранной строки таблицы
    QString id = ui->twData_h->item(row, 0)->text();

    // Находим соответствующую запись в модели
    for (int i = 0; i < model->rowCount(); ++i) {
        if (model->record(i).value("id_housing").toString() == id) {
            currentRow = i;
            refreshFields();
            break;
        }
    }
}

void Housings::dbconnect()
{
    if(!dbconn.isOpen())
    {
        dbconn = QSqlDatabase::addDatabase("QPSQL");
        dbconn.setDatabaseName("ART_APP");
        dbconn.setHostName("localhost");
        dbconn.setPort(5432);
        dbconn.setUserName("postgres");
        dbconn.setPassword("mrduckword532854");

        if(!dbconn.open())
        {
            QMessageBox::critical(this, "Ошибка подключения", dbconn.lastError().text());
        }
    }
}

void Housings::refreshFields()
{
    if (model->rowCount() == 0) {
        clearFields();
        return;
    }

    QSqlRecord record = model->record(currentRow);
    ui->le_id_h->setText(record.value("id_housing").toString());
    ui->cb_title_h->setCurrentText(record.value("title").toString());
    ui->le_address_h->setText(record.value("address").toString());

    // Выделяем соответствующую строку в таблице
    highlightCurrentRowInTable();
}

void Housings::highlightCurrentRowInTable()
{
    QString currentId = ui->le_id_h->text();

    for (int row = 0; row < ui->twData_h->rowCount(); ++row) {
        if (ui->twData_h->item(row, 0)->text() == currentId) {
            ui->twData_h->selectRow(row);
            break;
        }
    }
}

int Housings::getNextAvailableId()
{
    QSqlQuery query("SELECT MAX(id_housing::integer) FROM housings");
    if (query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1; // Если таблица пуста
}
void Housings::clearFields()
{
    ui->le_id_h->clear();
    ui->le_id_h->setPlaceholderText("");
    ui->cb_title_h->clearEditText();
    ui->le_address_h->clear();
}

void Housings::fillTitleComboBox()
{
    ui->cb_title_h->clear();
    QSqlQuery query("SELECT title FROM housings");
    while (query.next()) {
        ui->cb_title_h->addItem(query.value(0).toString());
    }
}

void Housings::on_btnPrevious_clicked()
{
    if (currentRow > 0)
        currentRow--;
    refreshFields();
}

void Housings::on_btnAddNew_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText("Хотите добавить новый корпус?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if (msgBox.clickedButton() == btnYes) {
        clearFields();
        // Устанавливаем подсказку для ID
        ui->le_id_h->setPlaceholderText("Оставьте пустым для автоназначения");
        ui->le_id_h->setEnabled(true);
        ui->cb_title_h->setEnabled(true);
        ui->le_address_h->setEnabled(true);
        ui->cb_title_h->setFocus();
    }
}

void Housings::on_btnEditRow_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText("Вы действительно хотите редактировать корпус?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if (msgBox.clickedButton() == btnYes) {
        ui->le_id_h->setEnabled(false);
        ui->cb_title_h->setEnabled(true);
    }
}

void Housings::on_btnDelete_clicked()
{
    if (model->rowCount() == 0)
        return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText("Вы действительно хотите удалить корпус?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if (msgBox.clickedButton() == btnYes) {
        model->removeRow(currentRow);
        if (model->submitAll()) {
            model->select();
            refreshTableData(); // Обновляем таблицу после удаления

            if (currentRow > 0)
                currentRow--;
            refreshFields();
            fillTitleComboBox();
            QMessageBox::information(this, "Удаление", "Корпус удалён!");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить запись: " + model->lastError().text());
        }
    }
}

void Housings::on_btnNext_clicked()
{
    if (currentRow < model->rowCount() - 1)
        currentRow++;
    refreshFields();
}

void Housings::on_btnSave_clicked()
{
    QString title = ui->cb_title_h->currentText();
    QString address = ui->le_address_h->text();

    if (title.isEmpty() || address.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все обязательные поля!");
        return;
    }

    QString id = ui->le_id_h->text();
    bool isNewRecord = ui->le_id_h->isEnabled();

    if (isNewRecord) {
        // Добавление новой записи
        if (id.isEmpty()) {
            // Если ID не указан - генерируем автоматически
            id = QString::number(getNextAvailableId());
        } else {
            // Проверяем, не существует ли уже запись с таким ID
            QSqlQuery checkQuery;
            checkQuery.prepare("SELECT 1 FROM housings WHERE id_housing = ?");
            checkQuery.addBindValue(id);
            if (checkQuery.exec() && checkQuery.next()) {
                QMessageBox::warning(this, "Ошибка", "Запись с таким ID уже существует!");
                return;
            }
        }

        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO housings (id_housing, title, address) VALUES (?, ?, ?)");
        insertQuery.addBindValue(id);
        insertQuery.addBindValue(title);
        insertQuery.addBindValue(address);

        if (insertQuery.exec()) {
            model->select();
            refreshTableData();
            fillTitleComboBox();
            QMessageBox::information(this, "Успех", "Данные сохранены!");

            // Находим и выделяем добавленную запись
            for (int i = 0; i < model->rowCount(); ++i) {
                if (model->record(i).value("id_housing").toString() == id) {
                    currentRow = i;
                    refreshFields();
                    break;
                }
            }
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить запись: " + insertQuery.lastError().text());
        }
    } else {
        // Редактирование существующей записи
        QString currentId = ui->le_id_h->text();
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE housings SET title = ?, address = ? WHERE id_housing = ?");
        updateQuery.addBindValue(title);
        updateQuery.addBindValue(address);
        updateQuery.addBindValue(currentId);

        if (updateQuery.exec()) {
            model->select();
            refreshTableData();
            fillTitleComboBox();
            QMessageBox::information(this, "Успех", "Данные сохранены!");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось обновить запись: " + updateQuery.lastError().text());
        }
    }
}
void Housings::on_btnLast_clicked()
{
    currentRow = model->rowCount() - 1;
    refreshFields();
}

void Housings::on_btn_to_faculties_clicked()
{
    Faculties *facultiesForm = new Faculties();
    facultiesForm->show();
    this->close();
}

void Housings::on_btnHome_clicked()
{
    emit returnToMainMenu();
    this->close();
}

void Housings::on_le_search_h_textChanged(const QString &text)
{
    // Очищаем таблицу
    ui->twData_h->setRowCount(0);

    // Создаем SQL-запрос с фильтром
    QSqlQuery query;
    query.prepare("SELECT id_housing, title, address FROM housings "
                  "WHERE title ILIKE :search OR address ILIKE :search "
                  "ORDER BY id_housing");
    query.bindValue(":search", "%" + text + "%");

    if (!query.exec()) {
        qDebug() << "Ошибка поиска:" << query.lastError().text();
        return;
    }

    // Заполняем таблицу найденными записями
    int row = 0;
    while (query.next()) {
        ui->twData_h->insertRow(row);

        for (int col = 0; col < 3; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->twData_h->setItem(row, col, item);
        }

        row++;
    }

    // Обновляем текущую позицию
    currentRow = 0;
    if (ui->twData_h->rowCount() > 0) {
        ui->twData_h->selectRow(0);
        refreshFields();
    } else {
        clearFields();
    }
}


void Housings::setupPermissions()
{
    switch(currentUserRole) {
    case UserRole::Admin:
        // Для администратора все доступно
        ui->le_id_h->setVisible(false);
        ui->lb_id_h->setVisible(false);
        //ui->le_id_h->setEnabled(false);
        break;
    case UserRole::Teacher:
        // Для преподавателя ограничиваем редактирование
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_h->setVisible(false);
        ui->lb_id_h->setVisible(false);
        ui->le_id_h->setEnabled(false);
        ui->cb_title_h->setEnabled(false);
        ui->le_address_h->setEnabled(false);

        break;
    case UserRole::Student:
        // Для студента только просмотр
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_h->setVisible(false);
        ui->lb_id_h->setVisible(false);
        ui->le_id_h->setEnabled(false);
        ui->cb_title_h->setEnabled(false);
        ui->le_address_h->setEnabled(false);
        break;
    }
}
