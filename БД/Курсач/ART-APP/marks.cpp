#include "marks.h"
#include "ui_marks.h"
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

Marks::Marks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Marks)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);

    dbconnect();
    setupModel();
    fillStudentComboBox();
    fillTeacherComboBox();
    fillSubjectComboBox();
    fillScheduleComboBox();
    fillMarkTypeComboBox();
    fillMarkComboBox();
    setupCompleters();
    setupTableWidget();
    refreshFields();
    setupPermissions();

    connect(ui->le_search_mark, &QLineEdit::textChanged, this, &Marks::on_le_search_mark_textChanged);
    connect(ui->twData_mark, &QTableWidget::cellClicked, this, &Marks::onTableRowClicked);
    connect(ui->btn_Marks_by_Stud, &QPushButton::clicked, this, &Marks::on_btn_Marks_by_Stud_clicked);
    connect(ui->btn_Marks_by_Teach, &QPushButton::clicked, this, &Marks::on_btn_Marks_by_Teach_clicked);
    connect(ui->btnMarks_by_Fac, &QPushButton::clicked, this, &Marks::on_btnMarks_by_Fac_clicked);
    connect(ui->btn_Avg_Marks_by_All_Facs, &QPushButton::clicked, this, &Marks::on_btn_Avg_Marks_by_All_Facs_clicked);
}

Marks::~Marks()
{
    if (dbconn.isOpen()) {
        dbconn.close();
    }
    delete ui;
}

void Marks::dbconnect()
{
    if (!dbconn.isOpen()) {
        dbconn = QSqlDatabase::addDatabase("QPSQL", "marks_connection");
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

void Marks::setupModel()
{
    model = new QSqlTableModel(this, dbconn);
    model->setTable("marks");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(model->fieldIndex("id_mark"), Qt::AscendingOrder);

    if (!model->select()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Ошибка загрузки данных:\n" + model->lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }

    currentRow = 0;
}

void Marks::setupTableWidget()
{
    ui->twData_mark->setColumnCount(8);
    ui->twData_mark->setHorizontalHeaderLabels({"ID", "Студент", "Предмет", "Преподаватель",
                                                "Тип оценки", "Оценка", "Дата", "День недели"});
    ui->twData_mark->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twData_mark->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData_mark->setEditTriggers(QAbstractItemView::NoEditTriggers);
    refreshTableData();
    ui->twData_mark->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->twData_mark->setColumnHidden(0, true);
}

void Marks::refreshTableData()
{
    ui->twData_mark->setRowCount(0);

    for (int row = 0; row < model->rowCount(); ++row) {
        QSqlRecord record = model->record(row);
        ui->twData_mark->insertRow(row);

        QTableWidgetItem *idItem = new QTableWidgetItem(record.value("id_mark").toString());
        QString studentName = getStudentNameById(record.value("id_student").toString());
        QTableWidgetItem *studentItem = new QTableWidgetItem(studentName);
        QString subjectTitle = getSubjectTitleById(record.value("id_subject").toString());
        QTableWidgetItem *subjectItem = new QTableWidgetItem(subjectTitle);
        QString teacherName = getTeacherNameById(record.value("id_teacher").toString());
        QTableWidgetItem *teacherItem = new QTableWidgetItem(teacherName);
        QTableWidgetItem *typeItem = new QTableWidgetItem(record.value("mark_type").toString());
        QTableWidgetItem *markItem = new QTableWidgetItem(record.value("mark").toString());
        QTableWidgetItem *dateItem = new QTableWidgetItem(record.value("date_m").toDate().toString("dd.MM.yyyy"));
        QString scheduleDay = getScheduleDayById(record.value("id_schedule").toString());
        QTableWidgetItem *scheduleItem = new QTableWidgetItem(scheduleDay);

        ui->twData_mark->setItem(row, 0, idItem);
        ui->twData_mark->setItem(row, 1, studentItem);
        ui->twData_mark->setItem(row, 2, subjectItem);
        ui->twData_mark->setItem(row, 3, teacherItem);
        ui->twData_mark->setItem(row, 4, typeItem);
        ui->twData_mark->setItem(row, 5, markItem);
        ui->twData_mark->setItem(row, 6, dateItem);
        ui->twData_mark->setItem(row, 7, scheduleItem);
    }
}

void Marks::onTableRowClicked(int row)
{
    if (row >= 0 && row < ui->twData_mark->rowCount()) {
        QString id = ui->twData_mark->item(row, 0)->text();
        for (int i = 0; i < model->rowCount(); ++i) {
            if (model->record(i).value("id_mark").toString() == id) {
                currentRow = i;
                refreshFields();
                break;
            }
        }
    }
}

void Marks::refreshFields()
{
    if(model->rowCount() == 0) {
        clearFields();
        return;
    }

    QSqlRecord record = model->record(currentRow);
    ui->le_id_mark->setText(record.value("id_mark").toString());

    // Установка студента
    QString studentId = record.value("id_student").toString();
    QString studentName = getStudentNameById(studentId);
    int studentIndex = ui->cb_id_student->findText(studentName, Qt::MatchFixedString);
    if (studentIndex != -1) {
        ui->cb_id_student->setCurrentIndex(studentIndex);
    } else {
        ui->cb_id_student->setCurrentText(studentName);
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

    // Установка типа оценки
    QString markType = record.value("mark_type").toString();
    int typeIndex = ui->cb_mark_type->findText(markType, Qt::MatchFixedString);
    if (typeIndex != -1) {
        ui->cb_mark_type->setCurrentIndex(typeIndex);
    } else {
        ui->cb_mark_type->setCurrentText(markType);
    }

    // Установка оценки
    QString mark = record.value("mark").toString();
    int markIndex = ui->cb_mark->findText(mark, Qt::MatchFixedString);
    if (markIndex != -1) {
        ui->cb_mark->setCurrentIndex(markIndex);
    } else {
        ui->cb_mark->setCurrentText(mark);
    }

    // Установка даты
    QDate date = record.value("date_m").toDate();
    ui->de_date_m->setDate(date);

    // Установка расписания
    QString scheduleId = record.value("id_schedule").toString();
    QString scheduleDay = getScheduleDayById(scheduleId);
    int scheduleIndex = ui->cb_id_schedule->findText(scheduleDay, Qt::MatchFixedString);
    if (scheduleIndex != -1) {
        ui->cb_id_schedule->setCurrentIndex(scheduleIndex);
    } else {
        ui->cb_id_schedule->setCurrentText(scheduleDay);
    }

    highlightCurrentRowInTable();
}

void Marks::clearFields()
{
    ui->le_id_mark->clear();
    ui->le_id_mark->setPlaceholderText("");
    ui->cb_id_student->clearEditText();
    ui->cb_id_subject->clearEditText();
    ui->cb_id_teacher->clearEditText();
    ui->cb_mark_type->clearEditText();
    ui->cb_mark->clearEditText();
    ui->de_date_m->clear();
    ui->cb_id_schedule->clearEditText();
}


int Marks::getNextAvailableId()
{
    QSqlQuery query(dbconn);
    if (query.exec("SELECT MAX(id_mark::integer) FROM marks") && query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;
}



void Marks::highlightCurrentRowInTable()
{
    QString currentId = ui->le_id_mark->text();
    for (int row = 0; row < ui->twData_mark->rowCount(); ++row) {
        if (ui->twData_mark->item(row, 0)->text() == currentId) {
            ui->twData_mark->selectRow(row);
            break;
        }
    }
}

void Marks::fillStudentComboBox()
{
    ui->cb_id_student->clear();
    studentMap.clear();
    QSqlQuery query(dbconn);

    if(!query.exec("SELECT id_student, fio FROM students ORDER BY fio")) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Не удалось загрузить список студентов:\n" + query.lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    while(query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        studentMap.insert(name, id);
        ui->cb_id_student->addItem(name);
    }

    ui->cb_id_student->setEditable(true);
    ui->cb_id_student->setInsertPolicy(QComboBox::NoInsert);
}

void Marks::fillTeacherComboBox()
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

void Marks::fillSubjectComboBox()
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

void Marks::fillScheduleComboBox()
{
    ui->cb_id_schedule->clear();
    scheduleMap.clear();

    // Выбираем первое расписание для каждого дня
    QSqlQuery query(dbconn);
    if(!query.exec("SELECT MIN(id_schedule), week_day FROM schedules "
                    "GROUP BY week_day ORDER BY "
                    "CASE week_day "
                    "WHEN 'Понедельник' THEN 1 "
                    "WHEN 'Вторник' THEN 2 "
                    "WHEN 'Среда' THEN 3 "
                    "WHEN 'Четверг' THEN 4 "
                    "WHEN 'Пятница' THEN 5 "
                    "WHEN 'Суббота' THEN 6 "
                    "ELSE 7 END")) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось загрузить расписание:\n" + query.lastError().text());
        return;
    }

    while(query.next()) {
        QString id = query.value(0).toString();
        QString day = query.value(1).toString();
        scheduleMap.insert(day, id);
        ui->cb_id_schedule->addItem(day);
    }

    ui->cb_id_schedule->setEditable(true);
    ui->cb_id_schedule->setInsertPolicy(QComboBox::NoInsert);
}

void Marks::fillMarkTypeComboBox()
{
    ui->cb_mark_type->clear();
    QStringList types = {"Экзамен", "Зачет"};
    ui->cb_mark_type->addItems(types);
    ui->cb_mark_type->setEditable(true);
    ui->cb_mark_type->setInsertPolicy(QComboBox::NoInsert);
}

void Marks::fillMarkComboBox()
{
    ui->cb_mark->clear();
    QStringList marks = {"2", "3", "4", "5"};
    ui->cb_mark->addItems(marks);
    ui->cb_mark->setEditable(false);
    ui->cb_mark->setInsertPolicy(QComboBox::NoInsert);
}

void Marks::setupCompleters()
{
    // студики
    QCompleter *studentCompleter = new QCompleter(studentMap.keys(), this);
    studentCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    studentCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_student->setCompleter(studentCompleter);

    // преподы
    QCompleter *teacherCompleter = new QCompleter(teacherMap.keys(), this);
    teacherCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    teacherCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_teacher->setCompleter(teacherCompleter);

    // предметы
    QCompleter *subjectCompleter = new QCompleter(subjectMap.keys(), this);
    subjectCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    subjectCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_subject->setCompleter(subjectCompleter);

    // расписания
    QCompleter *scheduleCompleter = new QCompleter(scheduleMap.keys(), this);
    scheduleCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    scheduleCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_schedule->setCompleter(scheduleCompleter);
}

QString Marks::getStudentNameById(const QString &id)
{
    return studentMap.key(id, "");
}

QString Marks::getStudentIdByName(const QString &name)
{
    return studentMap.value(name, "");
}

QString Marks::getTeacherNameById(const QString &id)
{
    return teacherMap.key(id, "");
}

QString Marks::getTeacherIdByName(const QString &name)
{
    return teacherMap.value(name, "");
}

QString Marks::getSubjectTitleById(const QString &id)
{
    return subjectMap.key(id, "");
}

QString Marks::getSubjectIdByTitle(const QString &title)
{
    return subjectMap.value(title, "");
}

QString Marks::getScheduleDayById(const QString &id)
{
    return scheduleMap.key(id, "");
}

QString Marks::getScheduleIdByDay(const QString &day)
{
    return scheduleMap.value(day, "");
}

void Marks::on_btnPrevious_clicked()
{
    if (currentRow > 0) {
        currentRow--;
        refreshFields();
    }
}

void Marks::on_btnNext_clicked()
{
    if (currentRow < model->rowCount() - 1) {
        currentRow++;
        refreshFields();
    }
}

void Marks::on_btnLast_clicked()
{
    currentRow = model->rowCount() - 1;
    refreshFields();
}

void Marks::on_btnAddNew_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Добавление");
    msgBox.setText("Хотите добавить новую оценку?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if (msgBox.clickedButton() == btnYes) {
        clearFields();
        ui->le_id_mark->setPlaceholderText("Оставьте пустым для автоназначения");
        ui->le_id_mark->setEnabled(true);
        ui->cb_id_student->setEnabled(true);
        ui->cb_id_subject->setEnabled(true);
        ui->cb_id_teacher->setEnabled(true);
        ui->cb_mark_type->setEnabled(true);
        ui->cb_mark->setEnabled(true);
        ui->de_date_m->setEnabled(true);
        ui->cb_id_schedule->setEnabled(true);
        ui->cb_id_student->setFocus();
    }
}

void Marks::on_btnEditRow_clicked()
{
    if(model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Редактирование");
    msgBox.setText("Вы действительно хотите редактировать данные оценки?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if(msgBox.clickedButton() == btnYes) {
        ui->le_id_mark->setEnabled(false);
        ui->cb_id_student->setEnabled(true);
        ui->cb_id_subject->setEnabled(true);
        ui->cb_id_teacher->setEnabled(true);
        ui->cb_mark_type->setEnabled(true);
        ui->cb_mark->setEnabled(true);
        ui->de_date_m->setEnabled(true);
        ui->cb_id_schedule->setEnabled(true);
    }
}

void Marks::on_btnDelete_clicked()
{
    if (model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Удаление");
    msgBox.setText("Вы действительно хотите удалить оценку?");
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
        infoBox.setText("Оценка удалена!");
        infoBox.setIcon(QMessageBox::Information);
        infoBox.exec();
    }
}

void Marks::on_btnSave_clicked()
{
    QString id = ui->le_id_mark->text().trimmed();
    QString studentName = ui->cb_id_student->currentText().trimmed();
    QString subjectTitle = ui->cb_id_subject->currentText().trimmed();
    QString teacherName = ui->cb_id_teacher->currentText().trimmed();
    QString markType = ui->cb_mark_type->currentText().trimmed();
    QString mark = ui->cb_mark->currentText();
    QDate date = ui->de_date_m->date();
    QString scheduleDay = ui->cb_id_schedule->currentText().trimmed();

    // Проверка заполненности полей
    if (studentName.isEmpty() || subjectTitle.isEmpty() || teacherName.isEmpty() ||
        markType.isEmpty() || mark.isEmpty() || !date.isValid() || scheduleDay.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }


    bool isNewRecord = ui->le_id_mark->isEnabled();
    if (isNewRecord && id.isEmpty()) {
        // Если ID не указан - генерируем автоматически
        id = QString::number(getNextAvailableId());
    } else if (isNewRecord) {
        // Проверяем, не существует ли уже записи с таким ID
        QSqlQuery checkQuery(dbconn);
        checkQuery.prepare("SELECT 1 FROM marks WHERE id_mark = ?");
        checkQuery.addBindValue(id);
        if (checkQuery.exec() && checkQuery.next()) {
            QMessageBox::warning(this, "Ошибка", "Оценка с таким ID уже существует!");
            return;
        }
    }


    QString studentId = getStudentIdByName(studentName);
    if (studentId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанный студент не найден!");
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

    QString scheduleId = getScheduleIdByDay(scheduleDay);
    if (scheduleId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанный день расписания не найден!");
        return;
    }

    // Сохранение данных
    QSqlQuery query(dbconn);
    if (isNewRecord) {
        query.prepare("INSERT INTO marks (id_mark, id_student, id_subject, id_teacher, "
                      "mark_type, mark, date_m, id_schedule) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(id);
        query.addBindValue(studentId);
        query.addBindValue(subjectId);
        query.addBindValue(teacherId);
        query.addBindValue(markType);
        query.addBindValue(mark);
        query.addBindValue(date);
        query.addBindValue(scheduleId);
    } else {
        query.prepare("UPDATE marks SET id_student = ?, id_subject = ?, id_teacher = ?, "
                      "mark_type = ?, mark = ?, date_m = ?, id_schedule = ? WHERE id_mark = ?");
        query.addBindValue(studentId);
        query.addBindValue(subjectId);
        query.addBindValue(teacherId);
        query.addBindValue(markType);
        query.addBindValue(mark);
        query.addBindValue(date);
        query.addBindValue(scheduleId);
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


    for (int i = 0; i < model->rowCount(); ++i) {
        if (model->record(i).value("id_mark").toString() == id) {
            currentRow = i;
            refreshFields();
            break;
        }
    }

    QMessageBox::information(this, "Успех", "Данные сохранены!");
}

void Marks::on_btn_to_Teachers_clicked()
{
    Teachers *teachersForm = new Teachers();
    teachersForm->show();
    this->close();
}

void Marks::on_le_search_mark_textChanged(const QString &text)
{
    QString filter = QString("id_student IN (SELECT id_student FROM students WHERE fio ILIKE '%%1%') OR "
                             "id_teacher IN (SELECT id_teacher FROM teachers WHERE fio ILIKE '%%1%')").arg(text);
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

void Marks::on_btn_Marks_by_Stud_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Оценки по студенту"));
    dialog.setLabelText(tr("Пожалуйста, укажите студента:"));
    dialog.setComboBoxItems(studentMap.keys());
    dialog.setComboBoxEditable(true);
    dialog.setWindowFlags(dialog.windowFlags() | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    dialog.setOkButtonText(tr("ОК"));
    dialog.setCancelButtonText(tr("Отмена"));

    if (dialog.exec() != QDialog::Accepted) return;

    QString studentName = dialog.textValue();
    if (studentName.isEmpty()) return;

    QString studentId = getStudentIdByName(studentName);
    if (studentId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанный студент не найден!");
        return;
    }

    QSqlQueryModel *marksModel = getMarksByStudent(studentId);

    if (marksModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить оценки:\n" + marksModel->lastError().text());
        return;
    }

    QDialog *marksDialog = new QDialog(this);
    marksDialog->setWindowTitle(QString("Оценки студента: %1").arg(studentName));
    marksDialog->setMinimumSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(marksDialog);

    QPushButton *btnPdf = new QPushButton("Отчет .pdf", marksDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, marksModel, studentName]() {
        generateReportPdf(marksModel, QString("Оценки студента %1").arg(studentName));
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(marksDialog);
    tableView->setModel(marksModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableView->setColumnHidden(0, true);


    marksModel->setHeaderData(1, Qt::Horizontal, tr("Предмет"));
    marksModel->setHeaderData(2, Qt::Horizontal, tr("Преподаватель"));
    marksModel->setHeaderData(3, Qt::Horizontal, tr("Тип оценки"));
    marksModel->setHeaderData(4, Qt::Horizontal, tr("Оценка"));
    marksModel->setHeaderData(5, Qt::Horizontal, tr("Дата"));
    marksModel->setHeaderData(6, Qt::Horizontal, tr("День недели"));

    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", marksDialog);
    connect(btnClose, &QPushButton::clicked, marksDialog, &QDialog::close);
    layout->addWidget(btnClose);

    marksDialog->exec();
}

void Marks::on_btn_Marks_by_Teach_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Оценки по преподавателю"));
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

    QSqlQueryModel *marksModel = getMarksByTeacher(teacherId);

    if (marksModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить оценки:\n" + marksModel->lastError().text());
        return;
    }

    QDialog *marksDialog = new QDialog(this);
    marksDialog->setWindowTitle(QString("Оценки преподавателя: %1").arg(teacherName));
    marksDialog->setMinimumSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(marksDialog);

    QPushButton *btnPdf = new QPushButton("Отчет .pdf", marksDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, marksModel, teacherName]() {
        generateReportPdf(marksModel, QString("Оценки преподавателя %1").arg(teacherName));
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(marksDialog);
    tableView->setModel(marksModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableView->setColumnHidden(0, true);


    marksModel->setHeaderData(1, Qt::Horizontal, tr("Студент"));
    marksModel->setHeaderData(2, Qt::Horizontal, tr("Предмет"));
    marksModel->setHeaderData(3, Qt::Horizontal, tr("Тип оценки"));
    marksModel->setHeaderData(4, Qt::Horizontal, tr("Оценка"));
    marksModel->setHeaderData(5, Qt::Horizontal, tr("Дата"));
    marksModel->setHeaderData(6, Qt::Horizontal, tr("День недели"));

    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", marksDialog);
    connect(btnClose, &QPushButton::clicked, marksDialog, &QDialog::close);
    layout->addWidget(btnClose);

    marksDialog->exec();
}

void Marks::on_btnMarks_by_Fac_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Оценки по направлению"));
    dialog.setLabelText(tr("Пожалуйста, укажите направление:"));

    QMap<QString, QString> facultyMap;
    QSqlQuery query(dbconn);
    if(query.exec("SELECT id_faculty, title FROM faculties ORDER BY title")) {
        while(query.next()) {
            facultyMap.insert(query.value(1).toString(), query.value(0).toString());
        }
    }

    dialog.setComboBoxItems(facultyMap.keys());
    dialog.setComboBoxEditable(true);
    dialog.setWindowFlags(dialog.windowFlags() | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    dialog.setOkButtonText(tr("ОК"));
    dialog.setCancelButtonText(tr("Отмена"));

    if (dialog.exec() != QDialog::Accepted) return;

    QString facultyTitle = dialog.textValue();
    if (facultyTitle.isEmpty()) return;

    QString facultyId = facultyMap.value(facultyTitle, "");
    if (facultyId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанное направление не найдено!");
        return;
    }

    QSqlQueryModel *marksModel = getMarksByFaculty(facultyId);

    if (marksModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить оценки:\n" + marksModel->lastError().text());
        return;
    }

    QDialog *marksDialog = new QDialog(this);
    marksDialog->setWindowTitle(QString("Оценки направления: %1").arg(facultyTitle));
    marksDialog->setMinimumSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(marksDialog);

    QPushButton *btnPdf = new QPushButton("Отчет .pdf", marksDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, marksModel, facultyTitle]() {
        generateReportPdf(marksModel, QString("Оценки направления %1").arg(facultyTitle));
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(marksDialog);
    tableView->setModel(marksModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableView->setColumnHidden(0, true);


    marksModel->setHeaderData(1, Qt::Horizontal, tr("Студент"));
    marksModel->setHeaderData(2, Qt::Horizontal, tr("Предмет"));
    marksModel->setHeaderData(3, Qt::Horizontal, tr("Преподаватель"));
    marksModel->setHeaderData(4, Qt::Horizontal, tr("Тип оценки"));
    marksModel->setHeaderData(5, Qt::Horizontal, tr("Оценка"));
    marksModel->setHeaderData(6, Qt::Horizontal, tr("Дата"));
    marksModel->setHeaderData(7, Qt::Horizontal, tr("День недели"));

    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", marksDialog);
    connect(btnClose, &QPushButton::clicked, marksDialog, &QDialog::close);
    layout->addWidget(btnClose);

    marksDialog->exec();
}

void Marks::on_btn_Avg_Marks_by_All_Facs_clicked()
{
    QSqlQueryModel *avgMarksModel = getAvgMarksByAllFaculties();

    if (avgMarksModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить средние оценки:\n" + avgMarksModel->lastError().text());
        return;
    }

    QDialog *avgMarksDialog = new QDialog(this);
    avgMarksDialog->setWindowTitle("Средние оценки по направлениям");
    avgMarksDialog->setMinimumSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(avgMarksDialog);

    QPushButton *btnPdf = new QPushButton("Отчет .pdf", avgMarksDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, avgMarksModel]() {
        generateReportPdf(avgMarksModel, "Средние оценки по направлениям");
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(avgMarksDialog);
    tableView->setModel(avgMarksModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableView->setColumnHidden(0, true);


    avgMarksModel->setHeaderData(1, Qt::Horizontal, tr("Направление"));
    avgMarksModel->setHeaderData(2, Qt::Horizontal, tr("Средняя оценка"));

    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", avgMarksDialog);
    connect(btnClose, &QPushButton::clicked, avgMarksDialog, &QDialog::close);
    layout->addWidget(btnClose);

    avgMarksDialog->exec();
}

QSqlQueryModel* Marks::getMarksByStudent(const QString &studentId)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString(
                        "SELECT ROW_NUMBER() OVER (ORDER BY m.date_m DESC) as num, "
                        "s.title, t.fio, m.mark_type, m.mark, m.date_m, sch.week_day "
                        "FROM marks m "
                        "JOIN subjects s ON m.id_subject = s.id_subject "
                        "JOIN teachers t ON m.id_teacher = t.id_teacher "
                        "JOIN schedules sch ON m.id_schedule = sch.id_schedule "
                        "WHERE m.id_student = '%1' "
                        "ORDER BY m.date_m DESC"
                        ).arg(studentId), dbconn);

    return model;
}

QSqlQueryModel* Marks::getMarksByTeacher(const QString &teacherId)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString(
                        "SELECT ROW_NUMBER() OVER (ORDER BY m.date_m DESC) as num, "
                        "st.fio, s.title, m.mark_type, m.mark, m.date_m, sch.week_day "
                        "FROM marks m "
                        "JOIN students st ON m.id_student = st.id_student "
                        "JOIN subjects s ON m.id_subject = s.id_subject "
                        "JOIN schedules sch ON m.id_schedule = sch.id_schedule "
                        "WHERE m.id_teacher = '%1' "
                        "ORDER BY m.date_m DESC"
                        ).arg(teacherId), dbconn);

    return model;
}

QSqlQueryModel* Marks::getMarksByFaculty(const QString &facultyId)
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(QString(
                        "SELECT ROW_NUMBER() OVER (ORDER BY m.date_m DESC) as num, "
                        "st.fio, s.title, t.fio, m.mark_type, m.mark, m.date_m, sch.week_day "
                        "FROM marks m "
                        "JOIN students st ON m.id_student = st.id_student "
                        "JOIN subjects s ON m.id_subject = s.id_subject "
                        "JOIN teachers t ON m.id_teacher = t.id_teacher "
                        "JOIN schedules sch ON m.id_schedule = sch.id_schedule "
                        "WHERE st.id_faculty = '%1' "
                        "ORDER BY m.date_m DESC"
                        ).arg(facultyId), dbconn);

    return model;
}

QSqlQueryModel* Marks::getAvgMarksByAllFaculties()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(
        "SELECT ROW_NUMBER() OVER (ORDER BY ROUND(AVG(m.mark::numeric), 2) DESC) as num, "
        "f.title, ROUND(AVG(m.mark::numeric), 2) as avg_mark "
        "FROM marks m "
        "JOIN students s ON m.id_student = s.id_student "
        "JOIN faculties f ON s.id_faculty = f.id_faculty "
        "GROUP BY f.title "
        "ORDER BY avg_mark DESC",
        dbconn
        );
    return model;
}

void Marks::generateReportPdf(QSqlQueryModel *model, const QString &title)
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


        QString headerText = (col == 0) ? "№" : model->headerData(col, Qt::Horizontal).toString();
        QFontMetrics fmHeader(headerFont);
        int headerWidth = fmHeader.horizontalAdvance(headerText);
        maxColWidth = qMax(maxColWidth, headerWidth) + 10;

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
        QString headerText = (col == 0) ? "№" : model->headerData(col, Qt::Horizontal).toString();
        painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
        painter.drawText(QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                         Qt::AlignCenter,
                         headerText);
        xPos += colWidths[col];
    }
    currentY += HEADER_HEIGHT;

    // Данные таблицы
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
                QString headerText = (col == 0) ? "№" : model->headerData(col, Qt::Horizontal).toString();
                painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
                painter.drawText(QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                                 Qt::AlignCenter,
                                 headerText);
                xPos += colWidths[col];
            }
            currentY += HEADER_HEIGHT;
            painter.setFont(dataFont);
        }

        xPos = LEFT_MARGIN;
        for (int col = 0; col < colCount; ++col) {
            QString text = model->data(model->index(row, col)).toString();
            painter.drawRect(xPos, currentY, colWidths[col], ROW_HEIGHT);


            Qt::Alignment alignment = (col == 0) ? Qt::AlignCenter : (Qt::AlignLeft | Qt::AlignVCenter);

            painter.drawText(QRect(xPos + 5, currentY, colWidths[col] - 10, ROW_HEIGHT),
                             alignment,
                             text);
            xPos += colWidths[col];
        }
        currentY += ROW_HEIGHT;
    }

    painter.end();
    QMessageBox::information(this, "Успех", QString("Отчет успешно сохранен в файл:\n%1").arg(fileName));
}
void Marks::on_btnHome_clicked()
{
    emit returnToMainMenu();
    this->close();
}

void Marks::setupPermissions()
{
    switch(currentUserRole) {
    case UserRole::Admin:
        // Для администратора все недоступно
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btn_Marks_by_Stud->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_mark->setVisible(false);
        ui->lb_id_mark->setVisible(false);
        ui->le_id_mark->setEnabled(false);
        ui->cb_mark_type->setEnabled(false);
        ui->cb_id_subject->setEnabled(false);
        ui->cb_id_student->setEnabled(false);
        ui->cb_mark->setEnabled(false);
        ui->cb_id_teacher->setEnabled(false);
        ui->de_date_m->setEnabled(false);
        ui->cb_id_schedule->setEnabled(false);
        ui->btn_Marks_by_Stud->setEnabled(false);

        break;
    case UserRole::Teacher:
        // Для преподавателя всё редактирование
        ui->btn_Avg_Marks_by_All_Facs->setVisible(false);
        ui->btn_Avg_Marks_by_All_Facs->setEnabled(false);
        ui->le_id_mark->setVisible(false);
        ui->lb_id_mark->setVisible(false);
        //ui->le_id_mark->setEnabled(false);


        break;
    case UserRole::Student:
        // Для студента только просмотр
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btn_Marks_by_Teach->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_mark->setVisible(false);
        ui->lb_id_mark->setVisible(false);
        ui->le_id_mark->setEnabled(false);
        ui->cb_mark_type->setEnabled(false);
        ui->cb_id_subject->setEnabled(false);
        ui->cb_id_student->setEnabled(false);
        ui->cb_mark->setEnabled(false);
        ui->cb_id_teacher->setEnabled(false);
        ui->de_date_m->setEnabled(false);
        ui->cb_id_schedule->setEnabled(false);
        ui->btn_Marks_by_Teach->setEnabled(false);
        ui->btn_Avg_Marks_by_All_Facs->setVisible(false);
        ui->btn_Avg_Marks_by_All_Facs->setEnabled(false);
    }
}
