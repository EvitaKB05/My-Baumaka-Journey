#include "faculties.h"
#include "ui_faculties.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include "housings.h"

Faculties::Faculties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Faculties)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);

    dbconnect();
    setupModel();
    fillTitleComboBox();
    fillHousingComboBox();
    setupTableWidget();
    setupPermissions();
    refreshFields();
}

Faculties::~Faculties()
{
    if(dbconn.isOpen()) {
        dbconn.close();
    }
    delete ui;
}

void Faculties::setupTableWidget()
{
    ui->twData_f->setColumnCount(3);
    ui->twData_f->setHorizontalHeaderLabels({"ID", "Название", "Корпус"});
    ui->twData_f->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twData_f->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData_f->setEditTriggers(QAbstractItemView::NoEditTriggers);
    refreshTableData();
    connect(ui->twData_f, &QTableWidget::cellClicked, this, &Faculties::onTableRowClicked);
    ui->twData_f->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twData_f->setColumnHidden(0, true);
}

void Faculties::refreshTableData()
{
    ui->twData_f->setRowCount(0);

    for (int row = 0; row < model->rowCount(); ++row) {
        QSqlRecord record = model->record(row);
        ui->twData_f->insertRow(row);

        QTableWidgetItem *idItem = new QTableWidgetItem(record.value("id_faculty").toString());
        QTableWidgetItem *titleItem = new QTableWidgetItem(record.value("title").toString());
        QString housingTitle = getHousingTitleById(record.value("id_housing").toString());
        QTableWidgetItem *housingItem = new QTableWidgetItem(housingTitle);

        ui->twData_f->setItem(row, 0, idItem);
        ui->twData_f->setItem(row, 1, titleItem);
        ui->twData_f->setItem(row, 2, housingItem);
    }
}


void Faculties::onTableRowClicked(int row)
{
    QString id = ui->twData_f->item(row, 0)->text();
    for (int i = 0; i < model->rowCount(); ++i) {
        if (model->record(i).value("id_faculty").toString() == id) {
            currentRow = i;
            refreshFields();
            break;
        }
    }
}

void Faculties::highlightCurrentRowInTable()
{
    QString currentId = ui->le_id_f->text();
    for (int row = 0; row < ui->twData_f->rowCount(); ++row) {
        if (ui->twData_f->item(row, 0)->text() == currentId) {
            ui->twData_f->selectRow(row);
            break;
        }
    }
}

void Faculties::dbconnect()
{
    if(!dbconn.isOpen()) {
        dbconn = QSqlDatabase::addDatabase("QPSQL", "faculties_connection");
        dbconn.setDatabaseName("ART_APP");
        dbconn.setHostName("localhost");
        dbconn.setPort(5432);
        dbconn.setUserName("postgres");
        dbconn.setPassword("mrduckword532854");

        if(!dbconn.open()) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка подключения");
            msgBox.setText("Не удалось подключиться к базе данных:\n" + dbconn.lastError().text());
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
}

void Faculties::setupModel()
{
    model = new QSqlTableModel(this, dbconn);
    model->setTable("faculties");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if(!model->select()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Ошибка загрузки данных:\n" + model->lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }

    currentRow = 0;
}

void Faculties::refreshFields()
{
    if(model->rowCount() == 0) {
        clearFields();
        return;
    }

    QSqlRecord record = model->record(currentRow);
    ui->le_id_f->setText(record.value("id_faculty").toString());

    // Установка названия направления
    QString currentTitle = record.value("title").toString();
    int titleIndex = ui->cb_title_f->findText(currentTitle, Qt::MatchFixedString);
    if(titleIndex >= 0) {
        ui->cb_title_f->setCurrentIndex(titleIndex);
    } else {
        ui->cb_title_f->setCurrentText(currentTitle);
    }

    // Установка корпуса
    QString housingId = record.value("id_housing").toString();
    QString housingTitle = getHousingTitleById(housingId);
    if(!housingTitle.isEmpty()) {
        int housingIndex = ui->cb_id_housing->findText(housingTitle, Qt::MatchFixedString);
        if(housingIndex >= 0) {
            ui->cb_id_housing->setCurrentIndex(housingIndex);
        } else {
            ui->cb_id_housing->setCurrentText(housingTitle);
        }
    } else {
        ui->cb_id_housing->setCurrentText("");
    }

    // Выделяем соответствующую строку в таблице
    highlightCurrentRowInTable();
}

void Faculties::clearFields()
{
    ui->le_id_f->clear();
    ui->le_id_f->setPlaceholderText("");
    ui->cb_title_f->clearEditText();
    ui->cb_id_housing->clearEditText();
}


int Faculties::getNextAvailableId()
{
    QSqlQuery query(dbconn);
    if (query.exec("SELECT MAX(id_faculty::integer) FROM faculties") && query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;
}

void Faculties::fillTitleComboBox()
{
    ui->cb_title_f->clear();
    QSqlQuery query(dbconn);

    if(!query.exec("SELECT DISTINCT title FROM faculties ORDER BY title")) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Не удалось загрузить список направлений:\n" + query.lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    while(query.next()) {
        ui->cb_title_f->addItem(query.value(0).toString());
    }

    ui->cb_title_f->setEditable(true);
    ui->cb_title_f->setInsertPolicy(QComboBox::NoInsert);
}

void Faculties::fillHousingComboBox()
{
    ui->cb_id_housing->clear();
    housingMap.clear();
    QSqlQuery query(dbconn);

    if(!query.exec("SELECT id_housing, title FROM housings ORDER BY title")) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Не удалось загрузить список корпусов:\n" + query.lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    while(query.next()) {
        QString id = query.value(0).toString();
        QString title = query.value(1).toString();
        housingMap.insert(title, id);
        ui->cb_id_housing->addItem(title);
    }

    ui->cb_id_housing->setEditable(true);
    ui->cb_id_housing->setInsertPolicy(QComboBox::NoInsert);
}

QString Faculties::getHousingIdByTitle(const QString &title)
{
    // Сначала проверяем точное совпадение
    if(housingMap.contains(title)) {
        return housingMap.value(title);
    }

    // Если нет, ищем без учета регистра
    for(auto it = housingMap.constBegin(); it != housingMap.constEnd(); ++it) {
        if(it.key().compare(title, Qt::CaseInsensitive) == 0) {
            return it.value();
        }
    }

    return ""; // Не найдено
}

QString Faculties::getHousingTitleById(const QString &id)
{
    return housingMap.key(id, "");
}

void Faculties::on_btnPrevious_clicked()
{
    if(currentRow > 0) {
        currentRow--;
        refreshFields();
    }
}

void Faculties::on_btnNext_clicked()
{
    if(currentRow < model->rowCount() - 1) {
        currentRow++;
        refreshFields();
    }
}

void Faculties::on_btnLast_clicked()
{
    currentRow = model->rowCount() - 1;
    refreshFields();
}

void Faculties::on_btnAddNew_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Добавление",
                                                              "Хотите добавить новое направление?", QMessageBox::Yes|QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        clearFields();
        ui->le_id_f->setPlaceholderText("Оставьте пустым для автоназначения");
        ui->le_id_f->setEnabled(true);
        ui->cb_title_f->setEnabled(true);
        ui->cb_id_housing->setEnabled(true);
        ui->cb_title_f->setFocus();
    }
}

void Faculties::on_btnEditRow_clicked()
{
    if(model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Редактирование");
    msgBox.setText("Вы действительно хотите редактировать направление?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if(msgBox.clickedButton() == btnYes) {
        ui->le_id_f->setEnabled(false);
        ui->cb_title_f->setEnabled(true);
        ui->cb_id_housing->setEnabled(true);
    }
}

void Faculties::on_btnDelete_clicked()
{
    if(model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Удаление");
    msgBox.setText("Вы действительно хотите удалить направление?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if(msgBox.clickedButton() == btnYes) {
        model->removeRow(currentRow);
        if(!model->submitAll()) {
            QMessageBox errorBox(this);
            errorBox.setWindowTitle("Ошибка");
            errorBox.setText("Не удалось удалить запись:\n" + model->lastError().text());
            errorBox.setIcon(QMessageBox::Critical);
            errorBox.exec();
            model->revertAll();
            return;
        }

        if(currentRow > 0) currentRow--;
        model->select();
        refreshTableData(); // Обновляем таблицу после удаления
        refreshFields();
        fillTitleComboBox();

        QMessageBox infoBox(this);
        infoBox.setWindowTitle("Успех");
        infoBox.setText("Направление удалено!");
        infoBox.setIcon(QMessageBox::Information);
        infoBox.exec();
    }
}

void Faculties::on_btnSave_clicked()
{
    QString id = ui->le_id_f->text().trimmed();
    QString title = ui->cb_title_f->currentText().trimmed();
    QString housingTitle = ui->cb_id_housing->currentText().trimmed();

    if(title.isEmpty() || housingTitle.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    // Обработка ID
    bool isNewRecord = ui->le_id_f->isEnabled();
    if (isNewRecord && id.isEmpty()) {
        // Если ID не указан - генерируем автоматически
        id = QString::number(getNextAvailableId());
    } else if (isNewRecord) {
        // Проверяем, не существует ли уже запись с таким ID
        QSqlQuery checkQuery(dbconn);
        checkQuery.prepare("SELECT 1 FROM faculties WHERE id_faculty = ?");
        checkQuery.addBindValue(id);
        if (checkQuery.exec() && checkQuery.next()) {
            QMessageBox::warning(this, "Ошибка", "Запись с таким ID уже существует!");
            return;
        }
    }

    // Обработка корпуса
    QString housingId = getHousingIdByTitle(housingTitle);
    if (housingId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанный корпус не найден!");
        return;
    }

    // Сохранение данных
    QSqlQuery query(dbconn);
    if (isNewRecord) {
        query.prepare("INSERT INTO faculties (id_faculty, title, id_housing) VALUES (?, ?, ?)");
    } else {
        query.prepare("UPDATE faculties SET title = ?, id_housing = ? WHERE id_faculty = ?");
    }

    if (isNewRecord) {
        query.addBindValue(id);
        query.addBindValue(title);
        query.addBindValue(housingId);
    } else {
        query.addBindValue(title);
        query.addBindValue(housingId);
        query.addBindValue(id);
    }

    if(!query.exec()) {
        QMessageBox::critical(this, "Ошибка",
                              isNewRecord ? "Не удалось добавить запись: " + query.lastError().text()
                                          : "Не удалось обновить запись: " + query.lastError().text());
        return;
    }

    // Обновление интерфейса
    model->select();
    refreshTableData();
    fillTitleComboBox();

    // Находим и выделяем добавленную/измененную запись
    for(int i = 0; i < model->rowCount(); ++i) {
        if(model->record(i).value("id_faculty").toString() == id) {
            currentRow = i;
            refreshFields();
            break;
        }
    }

    QMessageBox::information(this, "Успех", "Данные сохранены!");
}

void Faculties::on_btn_to_housings_clicked()
{
    Housings *housingsForm = new Housings();
    housingsForm->show();
    this->close();
}

void Faculties::on_btnHome_clicked()
{
    emit returnToMainMenu();
    this->close();
}

void Faculties::on_le_search_f_textChanged(const QString &text)
{
    QString filter = QString("title ILIKE '%%1%' OR id_housing IN (SELECT id_housing FROM housings WHERE title ILIKE '%%1%')")
    .arg(text);
    model->setFilter(filter);
    model->select();
    refreshTableData();
    currentRow = 0;
    refreshFields();
}

void Faculties::setupPermissions()
{
    switch(currentUserRole) {
    case UserRole::Admin:
        // Для администратора все доступно
        ui->le_id_f->setVisible(false);
        ui->lb_id_f->setVisible(false);
        //ui->le_id_f->setEnabled(false);
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
        ui->le_id_f->setVisible(false);
        ui->lb_id_f->setVisible(false);
        ui->le_id_f->setEnabled(false);
        ui->cb_title_f->setEnabled(false);
        ui->cb_id_housing->setEnabled(false);

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
        ui->le_id_f->setVisible(false);
        ui->lb_id_f->setVisible(false);
        ui->le_id_f->setEnabled(false);
        ui->cb_title_f->setEnabled(false);
        ui->cb_id_housing->setEnabled(false);
        break;
    }
}
