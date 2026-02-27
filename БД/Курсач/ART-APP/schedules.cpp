#include "schedules.h"
#include "ui_schedules.h"
#include "teachers.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QCompleter>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>

Schedules::Schedules(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Schedules)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);

    dbconnect();
    setupModel();
    fillFacultyComboBox();
    fillTeacherComboBox();
    fillSubjectComboBox();
    fillHousingComboBox();
    fillWeekDayComboBox();
    fillLessonTypeComboBox();
    setupCompleters();
    setupTableWidget();
    refreshFields();
    setupPermissions();
    connect(ui->le_search_sched, &QLineEdit::textChanged, this, &Schedules::on_le_search_sched_textChanged);
    connect(ui->twData_sched, &QTableWidget::cellClicked, this, &Schedules::onTableRowClicked);
    connect(ui->btn_Sched_by_Fac, &QPushButton::clicked, this, &Schedules::on_btn_Sched_by_Fac_clicked);
    connect(ui->btnSched_by_Teach, &QPushButton::clicked, this, &Schedules::on_btnSched_by_Teach_clicked);
    connect(ui->btn_All_Scheds, &QPushButton::clicked, this, &Schedules::on_btn_All_Scheds_clicked);

}

Schedules::~Schedules()
{
    if (dbconn.isOpen()) {
        dbconn.close();
    }
    delete ui;
}

void Schedules::dbconnect()
{
    if (!dbconn.isOpen()) {
        dbconn = QSqlDatabase::addDatabase("QPSQL", "schedules_connection");
        dbconn.setDatabaseName("ART_APP");
        dbconn.setHostName("localhost");
        dbconn.setPort(5432);
        dbconn.setUserName("postgres");
        dbconn.setPassword("mrduckword532854");

        if (!dbconn.open()) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Ошибка подключения");
            msgBox.setText("Не удалось подключиться к базе данных:\n" + dbconn.lastError().text());
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
}

void Schedules::setupModel()
{
    model = new QSqlTableModel(this, dbconn);
    model->setTable("schedules");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(model->fieldIndex("id_schedule"), Qt::AscendingOrder);

    if (!model->select()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Ошибка загрузки данных:\n" + model->lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }

    currentRow = 0;
}

void Schedules::setupTableWidget()
{
    ui->twData_sched->setColumnCount(8);
    ui->twData_sched->setHorizontalHeaderLabels({"ID", "Направление", "Предмет", "Преподаватель",
                                               "День недели", "Время", "Тип занятия", "Корпус"});
    ui->twData_sched->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twData_sched->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData_sched->setEditTriggers(QAbstractItemView::NoEditTriggers);
    refreshTableData();
    ui->twData_sched->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->twData_sched->setColumnHidden(0, true);
}

void Schedules::refreshTableData()
{
    ui->twData_sched->setRowCount(0);

    for (int row = 0; row < model->rowCount(); ++row) {
        QSqlRecord record = model->record(row);
        ui->twData_sched->insertRow(row);

        QTableWidgetItem *idItem = new QTableWidgetItem(record.value("id_schedule").toString());
        QString facultyTitle = getFacultyTitleById(record.value("id_faculty").toString());
        QTableWidgetItem *facultyItem = new QTableWidgetItem(facultyTitle);
        QString subjectTitle = getSubjectTitleById(record.value("id_subject").toString());
        QTableWidgetItem *subjectItem = new QTableWidgetItem(subjectTitle);
        QString teacherName = getTeacherNameById(record.value("id_teacher").toString());
        QTableWidgetItem *teacherItem = new QTableWidgetItem(teacherName);
        QTableWidgetItem *dayItem = new QTableWidgetItem(record.value("week_day").toString());

        QString timeStr = record.value("time").toString();
        QTime time;
        if (timeStr.contains('.')) {
            time = QTime::fromString(timeStr, "HH:mm:ss.zzz");
        } else if (timeStr.count(':') == 2) {
            time = QTime::fromString(timeStr, "HH:mm:ss");
        } else {
            time = QTime::fromString(timeStr, "HH:mm");
        }
        QTableWidgetItem *timeItem = new QTableWidgetItem(time.toString("h:mm"));
        QTableWidgetItem *typeItem = new QTableWidgetItem(record.value("lesson_type").toString());
        QString housingTitle = getHousingTitleById(record.value("id_housing").toString());
        QTableWidgetItem *housingItem = new QTableWidgetItem(housingTitle);

        ui->twData_sched->setItem(row, 0, idItem);
        ui->twData_sched->setItem(row, 1, facultyItem);
        ui->twData_sched->setItem(row, 2, subjectItem);
        ui->twData_sched->setItem(row, 3, teacherItem);
        ui->twData_sched->setItem(row, 4, dayItem);
        ui->twData_sched->setItem(row, 5, timeItem);
        ui->twData_sched->setItem(row, 6, typeItem);
        ui->twData_sched->setItem(row, 7, housingItem);
    }
}

void Schedules::onTableRowClicked(int row)
{
    if (row >= 0 && row < ui->twData_sched->rowCount()) {
        QString id = ui->twData_sched->item(row, 0)->text();
        for (int i = 0; i < model->rowCount(); ++i) {
            if (model->record(i).value("id_schedule").toString() == id) {
                currentRow = i;
                refreshFields();
                break;
            }
        }
    }
}

void Schedules::refreshFields()
{
    if(model->rowCount() == 0) {
        clearFields();
        return;
    }

    QSqlRecord record = model->record(currentRow);
    ui->le_id_sched->setText(record.value("id_schedule").toString());

    // Установка направления
    QString facultyId = record.value("id_faculty").toString();
    QString facultyTitle = getFacultyTitleById(facultyId);
    int facultyIndex = ui->cb_id_faculty->findText(facultyTitle, Qt::MatchFixedString);
    if (facultyIndex != -1) {
        ui->cb_id_faculty->setCurrentIndex(facultyIndex);
    } else {
        ui->cb_id_faculty->setCurrentText(facultyTitle);
    }

    // Установка предмета
    QString subjectId = record.value("id_subject").toString();
    QString subjectTitle = getSubjectTitleById(subjectId);
    int subjectIndex = ui->cb_id_subject->findText(subjectTitle, Qt::MatchFixedString);
    if (subjectIndex != -1) {
        ui->cb_id_subject->setCurrentIndex(subjectIndex);
    } else {
        ui->cb_id_subject->setCurrentText(subjectTitle);
    }

    // Установка преподавателя
    QString teacherId = record.value("id_teacher").toString();
    QString teacherName = getTeacherNameById(teacherId);
    int teacherIndex = ui->cb_id_teacher->findText(teacherName, Qt::MatchFixedString);
    if (teacherIndex != -1) {
        ui->cb_id_teacher->setCurrentIndex(teacherIndex);
    } else {
        ui->cb_id_teacher->setCurrentText(teacherName);
    }

    // Установка дня недели
    QString weekDay = record.value("week_day").toString();
    int dayIndex = ui->cb_week_day->findText(weekDay, Qt::MatchFixedString);
    if (dayIndex != -1) {
        ui->cb_week_day->setCurrentIndex(dayIndex);
    } else {
        ui->cb_week_day->setCurrentText(weekDay);
    }

    // Установка времени
    QString timeStr = record.value("time").toString().trimmed();
    QTime time;
    if (timeStr.contains('.')) {
        time = QTime::fromString(timeStr, "HH:mm:ss.zzz");
    } else if (timeStr.count(':') == 2) {
        time = QTime::fromString(timeStr, "HH:mm:ss");
    } else {
        time = QTime::fromString(timeStr, "HH:mm");
    }

    if (!time.isValid()) {
        qDebug() << "Invalid time format:" << timeStr;
        time = QTime(0, 0);
    }

    ui->time_edit_time->setTime(time);
    ui->time_edit_time->setDisplayFormat("h:mm");




    //
   // ui->time_edit_time->setTime(time);
    // Установка типа занятия
    QString lessonType = record.value("lesson_type").toString();
    int typeIndex = ui->cb_lesson_type->findText(lessonType, Qt::MatchFixedString);
    if (typeIndex != -1) {
        ui->cb_lesson_type->setCurrentIndex(typeIndex);
    } else {
        ui->cb_lesson_type->setCurrentText(lessonType);
    }

    // Установка корпуса
    QString housingId = record.value("id_housing").toString();
    QString housingTitle = getHousingTitleById(housingId);
    int housingIndex = ui->cb_id_housing->findText(housingTitle, Qt::MatchFixedString);
    if (housingIndex != -1) {
        ui->cb_id_housing->setCurrentIndex(housingIndex);
    } else {
        ui->cb_id_housing->setCurrentText(housingTitle);
    }

    highlightCurrentRowInTable();
}

void Schedules::clearFields()
{
    ui->le_id_sched->clear();
    ui->le_id_sched->setPlaceholderText("");
    ui->cb_id_faculty->clearEditText();
    ui->cb_id_subject->clearEditText();
    ui->cb_id_teacher->clearEditText();
    ui->cb_week_day->clearEditText();
    ui->time_edit_time->clear();
    ui->cb_lesson_type->clearEditText();
    ui->cb_id_housing->clearEditText();
}


int Schedules::getNextAvailableId()
{
    QSqlQuery query(dbconn);
    if (query.exec("SELECT MAX(id_schedule::integer) FROM schedules") && query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;
}


void Schedules::highlightCurrentRowInTable()
{
    QString currentId = ui->le_id_sched->text();
    for (int row = 0; row < ui->twData_sched->rowCount(); ++row) {
        if (ui->twData_sched->item(row, 0)->text() == currentId) {
            ui->twData_sched->selectRow(row);
            break;
        }
    }
}

void Schedules::fillFacultyComboBox()
{
    ui->cb_id_faculty->clear();
    facultyMap.clear();
    QSqlQuery query(dbconn);

    if(!query.exec("SELECT id_faculty, title FROM faculties ORDER BY title")) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Не удалось загрузить список направлений:\n" + query.lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    while(query.next()) {
        QString id = query.value(0).toString();
        QString title = query.value(1).toString();
        facultyMap.insert(title, id);
        ui->cb_id_faculty->addItem(title);
    }

    ui->cb_id_faculty->setEditable(true);
    ui->cb_id_faculty->setInsertPolicy(QComboBox::NoInsert);
}

void Schedules::fillTeacherComboBox()
{
    ui->cb_id_teacher->clear();
    teacherMap.clear();
    QSqlQuery query(dbconn);

    if(!query.exec("SELECT id_teacher, fio FROM teachers ORDER BY fio")) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Не удалось загрузить список преподавателей:\n" + query.lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    while(query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        teacherMap.insert(name, id);
        ui->cb_id_teacher->addItem(name);
    }

    ui->cb_id_teacher->setEditable(true);
    ui->cb_id_teacher->setInsertPolicy(QComboBox::NoInsert);
}

void Schedules::fillSubjectComboBox()
{
    ui->cb_id_subject->clear();
    subjectMap.clear();
    QSqlQuery query(dbconn);

    if(!query.exec("SELECT id_subject, title FROM subjects ORDER BY title")) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Не удалось загрузить список предметов:\n" + query.lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    while(query.next()) {
        QString id = query.value(0).toString();
        QString title = query.value(1).toString();
        subjectMap.insert(title, id);
        ui->cb_id_subject->addItem(title);
    }

    ui->cb_id_subject->setEditable(true);
    ui->cb_id_subject->setInsertPolicy(QComboBox::NoInsert);
}

void Schedules::fillHousingComboBox()
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

void Schedules::fillWeekDayComboBox()
{
    ui->cb_week_day->clear();
    QStringList days = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};
    ui->cb_week_day->addItems(days);
    ui->cb_week_day->setEditable(true);
    ui->cb_week_day->setInsertPolicy(QComboBox::NoInsert);
}

void Schedules::fillLessonTypeComboBox()
{
    ui->cb_lesson_type->clear();
    QStringList types = {"Лекция", "Практика", "Семинар", "Выходной день"};
    ui->cb_lesson_type->addItems(types);
    ui->cb_lesson_type->setEditable(true);
    ui->cb_lesson_type->setInsertPolicy(QComboBox::NoInsert);
}

void Schedules::setupCompleters()
{

    QCompleter *facultyCompleter = new QCompleter(facultyMap.keys(), this);
    facultyCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    facultyCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_faculty->setCompleter(facultyCompleter);


    QCompleter *teacherCompleter = new QCompleter(teacherMap.keys(), this);
    teacherCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    teacherCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_teacher->setCompleter(teacherCompleter);


    QCompleter *subjectCompleter = new QCompleter(subjectMap.keys(), this);
    subjectCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    subjectCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_subject->setCompleter(subjectCompleter);


    QCompleter *housingCompleter = new QCompleter(housingMap.keys(), this);
    housingCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    housingCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_housing->setCompleter(housingCompleter);
}

QString Schedules::getFacultyTitleById(const QString &id)
{
    return facultyMap.key(id, "");
}

QString Schedules::getFacultyIdByTitle(const QString &title)
{
    return facultyMap.value(title, "");
}

QString Schedules::getTeacherNameById(const QString &id)
{
    return teacherMap.key(id, "");
}

QString Schedules::getTeacherIdByName(const QString &name)
{
    return teacherMap.value(name, "");
}

QString Schedules::getSubjectTitleById(const QString &id)
{
    return subjectMap.key(id, "");
}

QString Schedules::getSubjectIdByTitle(const QString &title)
{
    return subjectMap.value(title, "");
}

QString Schedules::getHousingTitleById(const QString &id)
{
    return housingMap.key(id, "");
}

QString Schedules::getHousingIdByTitle(const QString &title)
{
    return housingMap.value(title, "");
}

void Schedules::on_btnPrevious_clicked()
{
    if (currentRow > 0) {
        currentRow--;
        refreshFields();
    }
}

void Schedules::on_btnNext_clicked()
{
    if (currentRow < model->rowCount() - 1) {
        currentRow++;
        refreshFields();
    }
}

void Schedules::on_btnLast_clicked()
{
    currentRow = model->rowCount() - 1;
    refreshFields();
}

void Schedules::on_btnAddNew_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Добавление");
    msgBox.setText("Хотите добавить новое расписание?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if (msgBox.clickedButton() == btnYes) {
        clearFields();
        ui->le_id_sched->setPlaceholderText("Оставьте пустым для автоназначения");
        ui->le_id_sched->setEnabled(true);
        ui->cb_id_faculty->setEnabled(true);
        ui->cb_id_subject->setEnabled(true);
        ui->cb_id_teacher->setEnabled(true);
        ui->cb_week_day->setEnabled(true);
        ui->time_edit_time->setEnabled(true);
        ui->cb_lesson_type->setEnabled(true);
        ui->cb_id_housing->setEnabled(true);
        ui->cb_id_faculty->setFocus();
    }
}

void Schedules::on_btnEditRow_clicked()
{
    if(model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Редактирование");
    msgBox.setText("Вы действительно хотите редактировать данные расписания?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if(msgBox.clickedButton() == btnYes) {
        ui->le_id_sched->setEnabled(false);
        ui->cb_id_faculty->setEnabled(true);
        ui->cb_id_subject->setEnabled(true);
        ui->cb_id_teacher->setEnabled(true);
        ui->cb_week_day->setEnabled(true);
        ui->time_edit_time->setEnabled(true);
        ui->cb_lesson_type->setEnabled(true);
        ui->cb_id_housing->setEnabled(true);
    }
}

void Schedules::on_btnDelete_clicked()
{
    if (model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Удаление");
    msgBox.setText("Вы действительно хотите удалить расписание?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if (msgBox.clickedButton() == btnYes) {
        model->removeRow(currentRow);
        if (!model->submitAll()) {
            QMessageBox errorBox(this);
            errorBox.setWindowTitle("Ошибка");
            errorBox.setText("Не удалось удалить запись:\n" + model->lastError().text());
            errorBox.setIcon(QMessageBox::Critical);
            errorBox.exec();
            model->revertAll();
            return;
        }

        if (currentRow > 0) currentRow--;
        model->select();
        refreshTableData();
        refreshFields();

        QMessageBox infoBox(this);
        infoBox.setWindowTitle("Успех");
        infoBox.setText("Расписание удалено!");
        infoBox.setIcon(QMessageBox::Information);
        infoBox.exec();
    }
}

void Schedules::on_btnSave_clicked()
{
    QString id = ui->le_id_sched->text().trimmed();
    QString facultyTitle = ui->cb_id_faculty->currentText().trimmed();
    QString subjectTitle = ui->cb_id_subject->currentText().trimmed();
    QString teacherName = ui->cb_id_teacher->currentText().trimmed();
    QString weekDay = ui->cb_week_day->currentText().trimmed();
    QString time = ui->time_edit_time->time().toString("h:mm");
    QString lessonType = ui->cb_lesson_type->currentText().trimmed();
    QString housingTitle = ui->cb_id_housing->currentText().trimmed();

    // Проверка заполненности полей
    if (facultyTitle.isEmpty() || subjectTitle.isEmpty() || teacherName.isEmpty() ||
        weekDay.isEmpty() || time.isEmpty() || lessonType.isEmpty() || housingTitle.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }


    bool isNewRecord = ui->le_id_sched->isEnabled();
    if (isNewRecord && id.isEmpty()) {
        // Если ID не указан - генерируем автоматически
        id = QString::number(getNextAvailableId());
    } else if (isNewRecord) {
        // Проверяем, не существует ли уже записи с таким ID
        QSqlQuery checkQuery(dbconn);
        checkQuery.prepare("SELECT 1 FROM schedules WHERE id_schedule = ?");
        checkQuery.addBindValue(id);
        if (checkQuery.exec() && checkQuery.next()) {
            QMessageBox::warning(this, "Ошибка", "Расписание с таким ID уже существует!");
            return;
        }
    }


    QString facultyId = getFacultyIdByTitle(facultyTitle);
    if (facultyId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанное направление не найдено!");
        return;
    }

    QString subjectId = getSubjectIdByTitle(subjectTitle);
    if (subjectId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанный предмет не найден!");
        return;
    }

    QString teacherId = getTeacherIdByName(teacherName);
    if (teacherId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанный преподаватель не найден!");
        return;
    }

    QString housingId = getHousingIdByTitle(housingTitle);
    if (housingId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанный корпус не найден!");
        return;
    }

    // Сохранение данных
    QSqlQuery query(dbconn);
    if (isNewRecord) {
        query.prepare("INSERT INTO schedules (id_schedule, id_faculty, id_subject, id_teacher, "
                      "week_day, time, lesson_type, id_housing) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(id);
        query.addBindValue(facultyId);
        query.addBindValue(subjectId);
        query.addBindValue(teacherId);
        query.addBindValue(weekDay);
        query.addBindValue(time);
        query.addBindValue(lessonType);
        query.addBindValue(housingId);
    } else {
        query.prepare("UPDATE schedules SET id_faculty = ?, id_subject = ?, id_teacher = ?, "
                      "week_day = ?, time = ?, lesson_type = ?, id_housing = ? WHERE id_schedule = ?");
        query.addBindValue(facultyId);
        query.addBindValue(subjectId);
        query.addBindValue(teacherId);
        query.addBindValue(weekDay);
        query.addBindValue(time);
        query.addBindValue(lessonType);
        query.addBindValue(housingId);
        query.addBindValue(id);
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка",
                              isNewRecord ? "Не удалось добавить запись: " + query.lastError().text()
                                          : "Не удалось обновить запись: " + query.lastError().text());
        return;
    }


    model->select();
    refreshTableData();

    // Находим и выделяем добавленную/измененную запись
    for (int i = 0; i < model->rowCount(); ++i) {
        if (model->record(i).value("id_schedule").toString() == id) {
            currentRow = i;
            refreshFields();
            break;
        }
    }

    QMessageBox::information(this, "Успех", "Данные сохранены!");
}

void Schedules::on_btn_to_Teachers_clicked()
{
    Teachers *teachersForm = new Teachers();
    teachersForm->show();
    this->close();
}

void Schedules::on_le_search_sched_textChanged(const QString &text)
{
    QString filter = QString("id_faculty IN (SELECT id_faculty FROM faculties WHERE title ILIKE '%%1%') OR "
                            "id_teacher IN (SELECT id_teacher FROM teachers WHERE fio ILIKE '%%1%') OR "
                            "id_subject IN (SELECT id_subject FROM subjects WHERE title ILIKE '%%1%')").arg(text);
    model->setFilter(filter);
    if (!model->select()) {
        qDebug() << "Filter error:" << model->lastError().text();
    }
    refreshTableData();
    currentRow = 0;
    if (model->rowCount() > 0) {
        refreshFields();
    }
}

void Schedules::on_btn_Sched_by_Fac_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Расписание по направлению"));
    dialog.setLabelText(tr("Пожалуйста, укажите направление:"));
    dialog.setComboBoxItems(facultyMap.keys());
    dialog.setComboBoxEditable(true);
    dialog.setWindowFlags(dialog.windowFlags() | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    dialog.setOkButtonText(tr("ОК"));
    dialog.setCancelButtonText(tr("Отмена"));

    if (dialog.exec() != QDialog::Accepted) return;

    QString facultyTitle = dialog.textValue();
    if (facultyTitle.isEmpty()) return;

    QString facultyId = getFacultyIdByTitle(facultyTitle);
    if (facultyId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанное направление не найдено!");
        return;
    }

    QSqlQueryModel *scheduleModel = getScheduleByFaculty(facultyId);

    if (scheduleModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить расписание:\n" + scheduleModel->lastError().text());
        return;
    }

    QDialog *scheduleDialog = new QDialog(this);
    scheduleDialog->setWindowTitle(QString("Расписание направления: %1").arg(facultyTitle));
    scheduleDialog->setMinimumSize(900, 600);

    QVBoxLayout *layout = new QVBoxLayout(scheduleDialog);


    QPushButton *btnPdf = new QPushButton("Отчет .pdf", scheduleDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, scheduleModel, facultyTitle]() {
        generateReportPdf(scheduleModel, QString("Расписание направления %1").arg(facultyTitle));
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(scheduleDialog);
    tableView->setModel(scheduleModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableView->setColumnWidth(0, 40);
    for (int col = 1; col < scheduleModel->columnCount(); ++col) {
        tableView->setColumnWidth(col, 150);
    }

    layout->addWidget(tableView);
    tableView->setColumnHidden(0, true);
    QPushButton *btnClose = new QPushButton("Закрыть", scheduleDialog);
    connect(btnClose, &QPushButton::clicked, scheduleDialog, &QDialog::close);
    layout->addWidget(btnClose);

    scheduleDialog->exec();
}

void Schedules::on_btnSched_by_Teach_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Расписание по преподавателю"));
    dialog.setLabelText(tr("Пожалуйста, укажите преподавателя:"));
    dialog.setComboBoxItems(teacherMap.keys());
    dialog.setComboBoxEditable(true);
    dialog.setWindowFlags(dialog.windowFlags() | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    dialog.setOkButtonText(tr("ОК"));
    dialog.setCancelButtonText(tr("Отмена"));

    if (dialog.exec() != QDialog::Accepted) return;

    QString teacherName = dialog.textValue();
    if (teacherName.isEmpty()) return;

    QString teacherId = getTeacherIdByName(teacherName);
    if (teacherId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанный преподаватель не найден!");
        return;
    }

    QSqlQueryModel *scheduleModel = getScheduleByTeacher(teacherId);

    if (scheduleModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить расписание:\n" + scheduleModel->lastError().text());
        return;
    }

    QDialog *scheduleDialog = new QDialog(this);
    scheduleDialog->setWindowTitle(QString("Расписание преподавателя: %1").arg(teacherName));
    scheduleDialog->setMinimumSize(900, 600);

    QVBoxLayout *layout = new QVBoxLayout(scheduleDialog);

    QPushButton *btnPdf = new QPushButton("Отчет .pdf", scheduleDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, scheduleModel, teacherName]() {
        generateReportPdf(scheduleModel, QString("Расписание преподавателя %1").arg(teacherName));
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(scheduleDialog);
    tableView->setModel(scheduleModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableView->setColumnWidth(0, 40);
    for (int col = 1; col < scheduleModel->columnCount(); ++col) {
        tableView->setColumnWidth(col, 150);
    }
    tableView->setColumnHidden(0, true);
    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", scheduleDialog);
    connect(btnClose, &QPushButton::clicked, scheduleDialog, &QDialog::close);
    layout->addWidget(btnClose);

    scheduleDialog->exec();
}

void Schedules::on_btn_All_Scheds_clicked()
{
    QSqlQueryModel *schedulesModel = getAllSchedules();

    if (schedulesModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить расписания:\n" + schedulesModel->lastError().text());
        return;
    }

    QDialog *schedulesDialog = new QDialog(this);
    schedulesDialog->setWindowTitle("Все расписания направлений");
    schedulesDialog->setMinimumSize(1100, 700);

    QVBoxLayout *layout = new QVBoxLayout(schedulesDialog);

    QPushButton *btnPdf = new QPushButton("Отчет .pdf", schedulesDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, schedulesModel]() {
        generateReportPdf(schedulesModel, "Все расписания направлений");
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(schedulesDialog);
    tableView->setModel(schedulesModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableView->setColumnWidth(0, 40);
    for (int col = 1; col < schedulesModel->columnCount(); ++col) {
        tableView->setColumnWidth(col, 150);
    }
    tableView->setColumnHidden(0, true);
    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", schedulesDialog);
    connect(btnClose, &QPushButton::clicked, schedulesDialog, &QDialog::close);
    layout->addWidget(btnClose);

    schedulesDialog->exec();
}
QSqlQueryModel* Schedules::getScheduleByFaculty(const QString &facultyId)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString(
                        "SELECT ROW_NUMBER() OVER (ORDER BY "
                        "CASE s.week_day "
                        "WHEN 'Понедельник' THEN 1 "
                        "WHEN 'Вторник' THEN 2 "
                        "WHEN 'Среда' THEN 3 "
                        "WHEN 'Четверг' THEN 4 "
                        "WHEN 'Пятница' THEN 5 "
                        "WHEN 'Суббота' THEN 6 "
                        "ELSE 7 END, s.time) as num, "
                        "s.week_day, "

                        "TO_CHAR(s.time::time, 'HH24:MI') as time, "
                        "sub.title, t.fio, s.lesson_type, h.title "
                        "FROM schedules s "
                        "JOIN subjects sub ON s.id_subject = sub.id_subject "
                        "JOIN teachers t ON s.id_teacher = t.id_teacher "
                        "JOIN housings h ON s.id_housing = h.id_housing "
                        "WHERE s.id_faculty = '%1' "
                        "ORDER BY "
                        "CASE s.week_day "
                        "WHEN 'Понедельник' THEN 1 "
                        "WHEN 'Вторник' THEN 2 "
                        "WHEN 'Среда' THEN 3 "
                        "WHEN 'Четверг' THEN 4 "
                        "WHEN 'Пятница' THEN 5 "
                        "WHEN 'Суббота' THEN 6 "
                        "ELSE 7 END, s.time"
                        ).arg(facultyId), dbconn);


    model->setHeaderData(0, Qt::Horizontal, tr("№"));
    model->setHeaderData(1, Qt::Horizontal, tr("День недели"));
    model->setHeaderData(2, Qt::Horizontal, tr("Время"));
    model->setHeaderData(3, Qt::Horizontal, tr("Предмет"));
    model->setHeaderData(4, Qt::Horizontal, tr("Преподаватель"));
    model->setHeaderData(5, Qt::Horizontal, tr("Тип занятия"));
    model->setHeaderData(6, Qt::Horizontal, tr("Корпус"));

    return model;
}

QSqlQueryModel* Schedules::getScheduleByTeacher(const QString &teacherId)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString(
                        "SELECT ROW_NUMBER() OVER (ORDER BY "
                        "CASE s.week_day "
                        "WHEN 'Понедельник' THEN 1 "
                        "WHEN 'Вторник' THEN 2 "
                        "WHEN 'Среда' THEN 3 "
                        "WHEN 'Четверг' THEN 4 "
                        "WHEN 'Пятница' THEN 5 "
                        "WHEN 'Суббота' THEN 6 "
                        "ELSE 7 END, s.time) as num, "
                        "s.week_day, "
                        "TO_CHAR(s.time::time, 'HH24:MI') as time, "
                        "sub.title, f.title, s.lesson_type, h.title "
                        "FROM schedules s "
                        "JOIN subjects sub ON s.id_subject = sub.id_subject "
                        "JOIN faculties f ON s.id_faculty = f.id_faculty "
                        "JOIN housings h ON s.id_housing = h.id_housing "
                        "WHERE s.id_teacher = '%1' "
                        "ORDER BY "
                        "CASE s.week_day "
                        "WHEN 'Понедельник' THEN 1 "
                        "WHEN 'Вторник' THEN 2 "
                        "WHEN 'Среда' THEN 3 "
                        "WHEN 'Четверг' THEN 4 "
                        "WHEN 'Пятница' THEN 5 "
                        "WHEN 'Суббота' THEN 6 "
                        "ELSE 7 END, s.time"
                        ).arg(teacherId), dbconn);


    model->setHeaderData(0, Qt::Horizontal, tr("№"));
    model->setHeaderData(1, Qt::Horizontal, tr("День недели"));
    model->setHeaderData(2, Qt::Horizontal, tr("Время"));
    model->setHeaderData(3, Qt::Horizontal, tr("Предмет"));
    model->setHeaderData(4, Qt::Horizontal, tr("Направление"));
    model->setHeaderData(5, Qt::Horizontal, tr("Тип занятия"));
    model->setHeaderData(6, Qt::Horizontal, tr("Корпус"));

    return model;
}

QSqlQueryModel* Schedules::getAllSchedules()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(
        "SELECT ROW_NUMBER() OVER (ORDER BY f.title, "
        "CASE s.week_day "
        "WHEN 'Понедельник' THEN 1 "
        "WHEN 'Вторник' THEN 2 "
        "WHEN 'Среда' THEN 3 "
        "WHEN 'Четверг' THEN 4 "
        "WHEN 'Пятница' THEN 5 "
        "WHEN 'Суббота' THEN 6 "
        "ELSE 7 END, s.time) as num, "
        "f.title, s.week_day, "
        "TO_CHAR(s.time::time, 'HH24:MI') as time, "
        "sub.title, t.fio, s.lesson_type, h.title "
        "FROM schedules s "
        "JOIN faculties f ON s.id_faculty = f.id_faculty "
        "JOIN subjects sub ON s.id_subject = sub.id_subject "
        "JOIN teachers t ON s.id_teacher = t.id_teacher "
        "JOIN housings h ON s.id_housing = h.id_housing "
        "ORDER BY f.title, "
        "CASE s.week_day "
        "WHEN 'Понедельник' THEN 1 "
        "WHEN 'Вторник' THEN 2 "
        "WHEN 'Среда' THEN 3 "
        "WHEN 'Четверг' THEN 4 "
        "WHEN 'Пятница' THEN 5 "
        "WHEN 'Суббота' THEN 6 "
        "ELSE 7 END, s.time",
        dbconn
        );


    model->setHeaderData(0, Qt::Horizontal, tr("№"));
    model->setHeaderData(1, Qt::Horizontal, tr("Направление"));
    model->setHeaderData(2, Qt::Horizontal, tr("День недели"));
    model->setHeaderData(3, Qt::Horizontal, tr("Время"));
    model->setHeaderData(4, Qt::Horizontal, tr("Предмет"));
    model->setHeaderData(5, Qt::Horizontal, tr("Преподаватель"));
    model->setHeaderData(6, Qt::Horizontal, tr("Тип занятия"));
    model->setHeaderData(7, Qt::Horizontal, tr("Корпус"));

    return model;
}


void Schedules::generateReportPdf(QSqlQueryModel *model, const QString &title)
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет как PDF",
        QString("%1.pdf").arg(title),
        "PDF Files (*.pdf)");

    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));
    writer.setResolution(96);

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось инициализировать QPainter");
        return;
    }

    // Настройки шрифтов
    QFont titleFont("Arial", 14, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont dataFont("Arial", 9);

    const int PAGE_WIDTH = writer.width();
    const int LEFT_MARGIN = 20;
    const int TOP_MARGIN = 75;
    const int ROW_HEIGHT = 20;
    const int HEADER_HEIGHT = 25;
    const int TITLE_SPACING = 30;

    int currentY = TOP_MARGIN;
    // Определяем индекс колонки с временем
    int timeColumn = -1;
    for (int i = 0; i < model->columnCount(); ++i) {
        if (model->headerData(i, Qt::Horizontal).toString() == "Время") {
            timeColumn = i;
            break;
        }
    }

    // Заголовок отчета
    painter.setFont(titleFont);
    painter.drawText(LEFT_MARGIN, currentY, title);
    currentY += TITLE_SPACING;

    painter.setFont(dataFont);
    painter.drawText(LEFT_MARGIN, currentY,
                     "Дата формирования: " + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
    currentY += TITLE_SPACING;

    if (model->rowCount() == 0) {
        painter.setFont(titleFont);
        painter.drawText(LEFT_MARGIN, currentY, "Нет данных для отображения");
        painter.end();
        QMessageBox::information(this, "Информация", "Нет данных для отчета.");
        return;
    }


    int colCount = model->columnCount();
    QVector<int> colWidths(colCount);
    int totalWidth = 0;


    for (int col = 0; col < colCount; ++col) {
        int maxColWidth = 0;


        for(int row = 0; row < model->rowCount(); ++row) {
            QFontMetrics fm(dataFont);
            int width = fm.horizontalAdvance(model->data(model->index(row, col)).toString());
            maxColWidth = qMax(maxColWidth, width);
        }


        QFontMetrics fmHeader(headerFont);
        int headerWidth = fmHeader.horizontalAdvance(model->headerData(col, Qt::Horizontal).toString());
        maxColWidth = qMax(maxColWidth, headerWidth) + 10; // Добавляем отступ


        if (col == 0) {
            maxColWidth = qMax(maxColWidth, 30);
        }

        colWidths[col] = maxColWidth;
        totalWidth += maxColWidth;
    }


    double widthScaleFactor = (double)(PAGE_WIDTH - 2 * LEFT_MARGIN) / totalWidth;
    for(int col = 0; col < colCount; col++) {
        colWidths[col] = colWidths[col] * widthScaleFactor;
    }


    painter.setFont(headerFont);
    int xPos = LEFT_MARGIN;
    for (int col = 0; col < colCount; ++col) {
        painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
        painter.drawText(QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                         Qt::AlignCenter,
                         model->headerData(col, Qt::Horizontal).toString());
        xPos += colWidths[col];
    }
    currentY += HEADER_HEIGHT;


    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        // Проверка на необходимость новой страницы
        if (currentY + ROW_HEIGHT > writer.height() - TOP_MARGIN) {
            writer.newPage();
            currentY = TOP_MARGIN;

            // Повторяем заголовки на новой странице
            xPos = LEFT_MARGIN;
            painter.setFont(headerFont);
            for (int col = 0; col < colCount; ++col) {
                painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
                painter.drawText(QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                                 Qt::AlignCenter,
                                 model->headerData(col, Qt::Horizontal).toString());
                xPos += colWidths[col];
            }
            currentY += HEADER_HEIGHT;
            painter.setFont(dataFont);
        }

        xPos = LEFT_MARGIN;
        for (int col = 0; col < colCount; ++col) {
            QString text = model->data(model->index(row, col)).toString();

            if (col == timeColumn) {
                QTime time = QTime::fromString(text, "HH:mm:ss");
                if (time.isValid()) {
                    text = time.toString("h:mm");
                }
            }

            painter.drawRect(xPos, currentY, colWidths[col], ROW_HEIGHT);
            painter.drawText(QRect(xPos + 5, currentY, colWidths[col] - 10, ROW_HEIGHT),
                             (col == 0) ? Qt::AlignCenter : (Qt::AlignLeft | Qt::AlignVCenter),
                             text);
            xPos += colWidths[col];
        }
        currentY += ROW_HEIGHT;
    }

    painter.end();
    QMessageBox::information(this, "Успех", QString("Отчет успешно сохранен в файл:\n%1").arg(fileName));
}

void Schedules::on_btnHome_clicked()
{
    emit returnToMainMenu();
    this->close();
}

void Schedules::setupPermissions()
{
    switch(currentUserRole) {
    case UserRole::Admin:
        // Для администратора все доступно
        ui->le_id_sched->setVisible(false);
        ui->lb_id_sched->setVisible(false);
        //ui->le_id_sched->setEnabled(false);
        break;
    case UserRole::Teacher:
        // Для преподавателя ограничиваем редактирование
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btn_All_Scheds->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_sched->setVisible(false);
        ui->lb_id_sched->setVisible(false);
        ui->le_id_sched->setEnabled(false);
        ui->cb_id_faculty->setEnabled(false);
        ui->cb_id_subject->setEnabled(false);
        ui->cb_week_day->setEnabled(false);
        ui->time_edit_time->setEnabled(false);
        ui->cb_lesson_type->setEnabled(false);
        ui->cb_id_teacher->setEnabled(false);
        ui->cb_id_housing->setEnabled(false);



        break;
    case UserRole::Student:
        // Для студента только просмотр
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btn_All_Scheds->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_sched->setVisible(false);
        ui->lb_id_sched->setVisible(false);
        ui->le_id_sched->setEnabled(false);
        ui->cb_id_faculty->setEnabled(false);
        ui->cb_id_subject->setEnabled(false);
        ui->cb_week_day->setEnabled(false);
        ui->time_edit_time->setEnabled(false);
        ui->cb_lesson_type->setEnabled(false);
        ui->cb_id_teacher->setEnabled(false);
        ui->cb_id_housing->setEnabled(false);
    }
}
