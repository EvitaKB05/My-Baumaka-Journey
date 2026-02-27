#include "subjects.h"
#include "ui_subjects.h"
#include "schedules.h"


Subjects::Subjects(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Subjects)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);

    dbconnect();
    setupModel();
    fillFacultyComboBox();
    fillSubjectsComboBox();
    setupCompleters();
    setupTableWidget();
    refreshFields();
    setupPermissions();

    connect(ui->le_search_sub, &QLineEdit::textChanged, this, &Subjects::on_le_search_sub_textChanged);
    connect(ui->twData_sub, &QTableWidget::cellClicked, this, &Subjects::onTableRowClicked);
    connect(ui->btnStud_by_Sub, &QPushButton::clicked, this, &Subjects::on_btnStud_by_Sub_clicked);
    connect(ui->btnSub_by_Fac, &QPushButton::clicked, this, &Subjects::on_btnSub_by_Fac_clicked);
    connect(ui->btnTeach_by_Sub, &QPushButton::clicked, this, &Subjects::on_btnTeach_by_Sub_clicked);

}

Subjects::~Subjects()
{
    if (dbconn.isOpen()) {
        dbconn.close();
    }
    delete ui;
}

void Subjects::dbconnect()
{
    if (!dbconn.isOpen()) {
        dbconn = QSqlDatabase::addDatabase("QPSQL", "subjects_connection");
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

void Subjects::setupModel()
{
    model = new QSqlTableModel(this, dbconn);
    model->setTable("subjects");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(model->fieldIndex("id_subject"), Qt::AscendingOrder);

    if (!model->select()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Ошибка загрузки данных:\n" + model->lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }

    currentRow = 0;
}

void Subjects::setupTableWidget()
{
    ui->twData_sub->setColumnCount(4);
    ui->twData_sub->setHorizontalHeaderLabels({"ID", "Название", "Часы обучения", "Направление"});
    ui->twData_sub->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twData_sub->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData_sub->setEditTriggers(QAbstractItemView::NoEditTriggers);
    refreshTableData();
    ui->twData_sub->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->twData_sub->setColumnHidden(0, true);
}

void Subjects::refreshTableData()
{
    ui->twData_sub->setRowCount(0);

    for (int row = 0; row < model->rowCount(); ++row) {
        QSqlRecord record = model->record(row);
        ui->twData_sub->insertRow(row);

        QTableWidgetItem *idItem = new QTableWidgetItem(record.value("id_subject").toString());
        QTableWidgetItem *titleItem = new QTableWidgetItem(record.value("title").toString());
        QTableWidgetItem *hoursItem = new QTableWidgetItem(record.value("learning_hours").toString());

        QString facultyTitle = getFacultyTitleById(record.value("id_faculty").toString());
        QTableWidgetItem *facultyItem = new QTableWidgetItem(facultyTitle);

        ui->twData_sub->setItem(row, 0, idItem);
        ui->twData_sub->setItem(row, 1, titleItem);
        ui->twData_sub->setItem(row, 2, hoursItem);
        ui->twData_sub->setItem(row, 3, facultyItem);
    }
}

void Subjects::onTableRowClicked(int row)
{
    if (row >= 0 && row < ui->twData_sub->rowCount()) {
        QString id = ui->twData_sub->item(row, 0)->text();
        for (int i = 0; i < model->rowCount(); ++i) {
            if (model->record(i).value("id_subject").toString() == id) {
                currentRow = i;
                refreshFields();
                break;
            }
        }
    }
}

void Subjects::refreshFields()
{
    if(model->rowCount() == 0) {
        clearFields();
        return;
    }

    QSqlRecord record = model->record(currentRow);
    ui->le_id_sub->setText(record.value("id_subject").toString());

    // Установка названия предмета
    QString currentTitle = record.value("title").toString();
    int titleIndex = ui->cb_title_sub->findText(currentTitle, Qt::MatchFixedString);
    if(titleIndex >= 0) {
        ui->cb_title_sub->setCurrentIndex(titleIndex);
    } else {
        ui->cb_title_sub->setCurrentText(currentTitle);
    }

    ui->le_learning_hours->setText(record.value("learning_hours").toString());

    // Установка направления
    QString facultyId = record.value("id_faculty").toString();
    QString facultyTitle = getFacultyTitleById(facultyId);
    int facultyIndex = ui->cb_id_faculty->findText(facultyTitle, Qt::MatchFixedString);
    if (facultyIndex != -1) {
        ui->cb_id_faculty->setCurrentIndex(facultyIndex);
    } else {
        ui->cb_id_faculty->setCurrentText(facultyTitle);
    }

    highlightCurrentRowInTable();
}

void Subjects::clearFields()
{
    ui->le_id_sub->clear();
    ui->le_id_sub->setPlaceholderText("");
    ui->cb_title_sub->clearEditText();
    ui->le_learning_hours->clear();
    ui->cb_id_faculty->clearEditText();
}


int Subjects::getNextAvailableId()
{
    QSqlQuery query(dbconn);
    if (query.exec("SELECT MAX(id_subject::integer) FROM subjects") && query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;
}




void Subjects::highlightCurrentRowInTable()
{
    QString currentId = ui->le_id_sub->text();
    for (int row = 0; row < ui->twData_sub->rowCount(); ++row) {
        if (ui->twData_sub->item(row, 0)->text() == currentId) {
            ui->twData_sub->selectRow(row);
            break;
        }
    }
}

void Subjects::fillFacultyComboBox()
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

void Subjects::fillSubjectsComboBox()
{
    ui->cb_title_sub->clear();
    QSqlQuery query(dbconn);
    if (!query.exec("SELECT DISTINCT title FROM subjects ORDER BY title")) {
        qCritical() << "Failed to query subject titles:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        ui->cb_title_sub->addItem(query.value(0).toString());
    }

    ui->cb_title_sub->setEditable(true);
    ui->cb_title_sub->setInsertPolicy(QComboBox::NoInsert);
}

void Subjects::setupCompleters()
{

    QStringList subjectsList;
    for (int i = 0; i < ui->cb_title_sub->count(); ++i) {
        subjectsList << ui->cb_title_sub->itemText(i);
    }
    QCompleter *subjectCompleter = new QCompleter(subjectsList, this);
    subjectCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    subjectCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_title_sub->setCompleter(subjectCompleter);


    QStringList facultiesList;
    for (int i = 0; i < ui->cb_id_faculty->count(); ++i) {
        facultiesList << ui->cb_id_faculty->itemText(i);
    }
    QCompleter *facultyCompleter = new QCompleter(facultiesList, this);
    facultyCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    facultyCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_faculty->setCompleter(facultyCompleter);
}

QString Subjects::getFacultyTitleById(const QString &id)
{
    return facultyMap.key(id, "");
}

QString Subjects::getFacultyIdByTitle(const QString &title)
{
    return facultyMap.value(title, "");
}

QString Subjects::getTeachersForSubject(const QString& subjectId)
{
    QSqlQuery query(dbconn);
    query.prepare("SELECT t.fio FROM teachers t "
                  "JOIN sub_teachers st ON t.id_teacher = st.id_teacher "
                  "WHERE st.id_subject = :subjectId "
                  "ORDER BY t.fio");
    query.bindValue(":subjectId", subjectId);

    if (!query.exec()) {
        qDebug() << "Failed to get teachers for subject:" << query.lastError().text();
        return "";
    }

    QStringList teachers;
    while (query.next()) {
        teachers << query.value(0).toString();
    }

    return teachers.join(", ");
}

void Subjects::on_btnPrevious_clicked()
{
    if (currentRow > 0) {
        currentRow--;
        refreshFields();
    }
}

void Subjects::on_btnNext_clicked()
{
    if (currentRow < model->rowCount() - 1) {
        currentRow++;
        refreshFields();
    }
}

void Subjects::on_btnLast_clicked()
{
    currentRow = model->rowCount() - 1;
    refreshFields();
}

void Subjects::on_btnAddNew_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Добавление",
                                                              "Хотите добавить новый предмет?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        clearFields();
        ui->le_id_sub->setPlaceholderText("Оставьте пустым для автоназначения");
        ui->le_id_sub->setEnabled(true);
        ui->cb_title_sub->setEnabled(true);
        ui->le_learning_hours->setEnabled(true);
        ui->cb_id_faculty->setEnabled(true);
        ui->cb_title_sub->setFocus();
    }
}

void Subjects::on_btnEditRow_clicked()
{
    if(model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Редактирование");
    msgBox.setText("Вы действительно хотите редактировать данные предмета?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if(msgBox.clickedButton() == btnYes) {
        ui->le_id_sub->setEnabled(false);
        ui->cb_title_sub->setEnabled(true);
        ui->le_learning_hours->setEnabled(true);
        ui->cb_id_faculty->setEnabled(true);
    }
}

void Subjects::on_btnDelete_clicked()
{
    if (model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Удаление");
    msgBox.setText("Вы действительно хотите удалить предмет?");
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
        fillSubjectsComboBox();

        QMessageBox infoBox(this);
        infoBox.setWindowTitle("Успех");
        infoBox.setText("Предмет удален!");
        infoBox.setIcon(QMessageBox::Information);
        infoBox.exec();
    }
}

void Subjects::on_btnSave_clicked()
{
    QString id = ui->le_id_sub->text().trimmed();
    QString title = ui->cb_title_sub->currentText().trimmed();
    QString hours = ui->le_learning_hours->text().trimmed();
    QString facultyTitle = ui->cb_id_faculty->currentText().trimmed();

    if (title.isEmpty() || hours.isEmpty() || facultyTitle.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }


    bool isNewRecord = ui->le_id_sub->isEnabled();
    if (isNewRecord && id.isEmpty()) {
        // Если ID не указан - генерируем автоматически
        id = QString::number(getNextAvailableId());
    } else if (isNewRecord) {
        // Проверяем, не существует ли уже запись с таким ID
        QSqlQuery checkQuery(dbconn);
        checkQuery.prepare("SELECT 1 FROM subjects WHERE id_subject = ?");
        checkQuery.addBindValue(id);
        if (checkQuery.exec() && checkQuery.next()) {
            QMessageBox::warning(this, "Ошибка", "Предмет с таким ID уже существует!");
            return;
        }
    }

    // Проверяем валидность часов обучения
    bool ok;
    int hoursInt = hours.toInt(&ok);
    if (!ok || hoursInt <= 0) {
        QMessageBox::warning(this, "Ошибка", "Часы обучения должны быть положительным числом!");
        return;
    }


    QString facultyId = getFacultyIdByTitle(facultyTitle);
    if (facultyId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанное направление не найдено!");
        return;
    }


    QSqlQuery query(dbconn);
    if (isNewRecord) {
        query.prepare("INSERT INTO subjects (id_subject, title, learning_hours, id_faculty) VALUES (?, ?, ?, ?)");
        query.addBindValue(id);
        query.addBindValue(title);
        query.addBindValue(hoursInt);
        query.addBindValue(facultyId);
    } else {
        query.prepare("UPDATE subjects SET title = ?, learning_hours = ?, id_faculty = ? WHERE id_subject = ?");
        query.addBindValue(title);
        query.addBindValue(hoursInt);
        query.addBindValue(facultyId);
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
    fillSubjectsComboBox();


    for (int i = 0; i < model->rowCount(); ++i) {
        if (model->record(i).value("id_subject").toString() == id) {
            currentRow = i;
            refreshFields();
            break;
        }
    }

    QMessageBox::information(this, "Успех", "Данные сохранены!");
}


void Subjects::on_btn_to_schedules_clicked()
{
    Schedules *schedulesForm = new Schedules();
    schedulesForm->show();
    this->close();
}


void Subjects::on_le_search_sub_textChanged(const QString &text)
{
    QString filter = QString("title ILIKE '%%1%'").arg(text);
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

void Subjects::on_btnTeach_by_Sub_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Преподаватели по предмету"));
    dialog.setLabelText(tr("Пожалуйста, укажите предмет:"));

    QStringList subjectTitles;
    QSqlQuery query("SELECT title FROM subjects ORDER BY title", dbconn);
    while (query.next()) {
        subjectTitles << query.value(0).toString();
    }

    dialog.setComboBoxItems(subjectTitles);
    dialog.setComboBoxEditable(true);
    dialog.setWindowFlags(dialog.windowFlags() | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    dialog.setOkButtonText(tr("ОК"));
    dialog.setCancelButtonText(tr("Отмена"));

    if (dialog.exec() != QDialog::Accepted) return;

    QString subjectTitle = dialog.textValue();
    if (subjectTitle.isEmpty()) return;

    // Получаем ID предмета
    QString subjectId;
    QSqlQuery idQuery(dbconn);
    idQuery.prepare("SELECT id_subject FROM subjects WHERE title = :title");
    idQuery.bindValue(":title", subjectTitle);
    if (!idQuery.exec() || !idQuery.next()) {
        QMessageBox::warning(this, "Ошибка", "Указанный предмет не найден!");
        return;
    }
    subjectId = idQuery.value(0).toString();


    QSqlQueryModel *teachersModel = new QSqlQueryModel(this);
    teachersModel->setQuery(QString(
                                "SELECT t.fio, t.contacts, t.post, f.title AS faculty_title "
                                "FROM teachers t "
                                "JOIN sub_teachers st ON t.id_teacher = st.id_teacher "
                                "LEFT JOIN faculties f ON t.id_faculty = f.id_faculty "
                                "WHERE st.id_subject = '%1' "
                                "ORDER BY t.fio").arg(subjectId), dbconn);

    if (teachersModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить преподавателей:\n" + teachersModel->lastError().text());
        return;
    }

    QDialog *teachersDialog = new QDialog(this);
    teachersDialog->setWindowTitle(QString("Преподаватели предмета: %1").arg(subjectTitle));
    teachersDialog->setMinimumSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(teachersDialog);


    QPushButton *btnPdf = new QPushButton("Отчет .pdf", teachersDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, subjectId, subjectTitle]() {
        QSqlQueryModel pdfModel;
        pdfModel.setQuery(QString(
                              "SELECT ROW_NUMBER() OVER (ORDER BY t.fio) as num, "
                              "t.fio, t.contacts, t.post, f.title AS faculty_title "
                              "FROM teachers t "
                              "JOIN sub_teachers st ON t.id_teacher = st.id_teacher "
                              "LEFT JOIN faculties f ON t.id_faculty = f.id_faculty "
                              "WHERE st.id_subject = '%1' "
                              "ORDER BY t.fio").arg(subjectId), dbconn);
        generateTeachersPdf(&pdfModel, QString("Преподаватели предмета %1").arg(subjectTitle));
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(teachersDialog);
    tableView->setModel(teachersModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    teachersModel->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
    teachersModel->setHeaderData(1, Qt::Horizontal, tr("Контакты"));
    teachersModel->setHeaderData(2, Qt::Horizontal, tr("Должность"));
    teachersModel->setHeaderData(3, Qt::Horizontal, tr("Направление"));

    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", teachersDialog);
    connect(btnClose, &QPushButton::clicked, teachersDialog, &QDialog::close);
    layout->addWidget(btnClose);

    teachersDialog->exec();
}

void Subjects::generateTeachersPdf(QSqlQueryModel *model, const QString &title)
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет как PDF",
        QString("Преподаватели_%1.pdf").arg(title),
        "PDF Files (*.pdf)");

    if (fileName.isEmpty()) return;

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
    const int LEFT_MARGIN = 75;
    const int TOP_MARGIN = 75;
    const int ROW_HEIGHT = 30;
    const int HEADER_HEIGHT = 35;
    const int TITLE_SPACING = 40;


    const int colWidths[] = {
        static_cast<int>(PAGE_WIDTH * 0.08),  // №
        static_cast<int>(PAGE_WIDTH * 0.30),  // ФИО
        static_cast<int>(PAGE_WIDTH * 0.22),  // Контакты
        static_cast<int>(PAGE_WIDTH * 0.20),  // Должность
        static_cast<int>(PAGE_WIDTH * 0.20)   // Направление
    };

    int currentY = TOP_MARGIN;
    int pageNumber = 1;


    painter.setFont(titleFont);
    painter.drawText(LEFT_MARGIN, currentY, title);
    currentY += TITLE_SPACING;

    painter.setFont(dataFont);
    painter.drawText(LEFT_MARGIN, currentY,
                     "Дата формирования: " + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
    currentY += TITLE_SPACING * 2;

    if (model->rowCount() == 0) {
        painter.setFont(titleFont);
        painter.drawText(LEFT_MARGIN, currentY, "Нет данных для отображения");
        painter.end();
        QMessageBox::information(this, "Информация", "Нет данных для отчета.");
        return;
    }


    painter.setFont(headerFont);
    int xPos = LEFT_MARGIN;
    QStringList headers = {"№", "ФИО", "Контакты", "Должность", "Направление"};
    for (int col = 0; col < headers.size(); ++col) {
        painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
        painter.drawText(
            QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
            Qt::AlignCenter,
            headers[col]
            );
        xPos += colWidths[col];
    }
    currentY += HEADER_HEIGHT;


    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        if (currentY + ROW_HEIGHT > writer.height() - TOP_MARGIN) {
            writer.newPage();
            currentY = TOP_MARGIN;
            pageNumber++;

            // Повторяем заголовки
            xPos = LEFT_MARGIN;
            painter.setFont(headerFont);
            for (int col = 0; col < headers.size(); ++col) {
                painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
                painter.drawText(
                    QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                    Qt::AlignCenter,
                    headers[col]
                    );
                xPos += colWidths[col];
            }
            currentY += HEADER_HEIGHT;
            painter.setFont(dataFont);
        }

        xPos = LEFT_MARGIN;
        for (int col = 0; col < model->columnCount(); ++col) {
            QString text = model->data(model->index(row, col)).toString();
            painter.drawRect(xPos, currentY, colWidths[col], ROW_HEIGHT);
            painter.drawText(
                QRect(xPos + 5, currentY, colWidths[col] - 10, ROW_HEIGHT),
                Qt::AlignLeft | Qt::AlignVCenter,
                text
                );
            xPos += colWidths[col];
        }
        currentY += ROW_HEIGHT;
    }

    painter.end();
    QMessageBox::information(this, "Успех", QString("Отчет успешно сохранен в файл:\n%1").arg(fileName));
}



void Subjects::on_btnStud_by_Sub_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Студенты по предмету"));
    dialog.setLabelText(tr("Пожалуйста, укажите предмет:"));

    QStringList subjectTitles;
    QSqlQuery query("SELECT title FROM subjects ORDER BY title", dbconn);
    while (query.next()) {
        subjectTitles << query.value(0).toString();
    }

    dialog.setComboBoxItems(subjectTitles);
    dialog.setComboBoxEditable(true);
    dialog.setWindowFlags(dialog.windowFlags() | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    dialog.setOkButtonText(tr("ОК"));
    dialog.setCancelButtonText(tr("Отмена"));

    if (dialog.exec() != QDialog::Accepted) return;

    QString subjectTitle = dialog.textValue();
    if (subjectTitle.isEmpty()) return;


    QString subjectId;
    QSqlQuery idQuery(dbconn);
    idQuery.prepare("SELECT id_subject FROM subjects WHERE title = :title");
    idQuery.bindValue(":title", subjectTitle);
    if (!idQuery.exec() || !idQuery.next()) {
        QMessageBox::warning(this, "Ошибка", "Указанный предмет не найден!");
        return;
    }
    subjectId = idQuery.value(0).toString();


    QSqlQueryModel *studentsModel = new QSqlQueryModel(this);
    studentsModel->setQuery(QString(
                                "SELECT s.fio, s.contacts, f.title as faculty "
                                "FROM students s "
                                "JOIN sub_students ss ON s.id_student = ss.id_student "
                                "JOIN faculties f ON s.id_faculty = f.id_faculty "
                                "WHERE ss.id_subject = '%1' "
                                "ORDER BY s.fio").arg(subjectId), dbconn);

    if (studentsModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить студентов:\n" + studentsModel->lastError().text());
        return;
    }

    QDialog *studentsDialog = new QDialog(this);
    studentsDialog->setWindowTitle(QString("Студенты предмета: %1").arg(subjectTitle));
    studentsDialog->setMinimumSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(studentsDialog);


    QPushButton *btnPdf = new QPushButton("Отчет .pdf", studentsDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, subjectId, subjectTitle]() {
        QSqlQueryModel pdfModel;
        pdfModel.setQuery(QString(
                              "SELECT ROW_NUMBER() OVER (ORDER BY s.fio) as num, "
                              "s.fio, s.contacts, f.title as faculty "
                              "FROM students s "
                              "JOIN sub_students ss ON s.id_student = ss.id_student "
                              "JOIN faculties f ON s.id_faculty = f.id_faculty "
                              "WHERE ss.id_subject = '%1' "
                              "ORDER BY s.fio").arg(subjectId), dbconn);
        generateStudentsPdf(&pdfModel, QString("Студенты предмета %1").arg(subjectTitle));
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(studentsDialog);
    tableView->setModel(studentsModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    studentsModel->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
    studentsModel->setHeaderData(1, Qt::Horizontal, tr("Контакты"));
    studentsModel->setHeaderData(2, Qt::Horizontal, tr("Направление"));

    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", studentsDialog);
    connect(btnClose, &QPushButton::clicked, studentsDialog, &QDialog::close);
    layout->addWidget(btnClose);

    studentsDialog->exec();
}

void Subjects::generateStudentsPdf(QSqlQueryModel *model, const QString &title)
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет как PDF",
        QString("Студенты_%1.pdf").arg(title),
        "PDF Files (*.pdf)");

    if (fileName.isEmpty()) return;

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));
    writer.setResolution(96);

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось инициализировать QPainter");
        return;
    }


    QFont titleFont("Arial", 14, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont dataFont("Arial", 9);

    const int PAGE_WIDTH = writer.width();
    const int LEFT_MARGIN = 75;
    const int TOP_MARGIN = 75;
    const int ROW_HEIGHT = 30;
    const int HEADER_HEIGHT = 35;
    const int TITLE_SPACING = 40;


    const int colWidths[] = {
        static_cast<int>(PAGE_WIDTH * 0.10),  // №
        static_cast<int>(PAGE_WIDTH * 0.40),  // ФИО
        static_cast<int>(PAGE_WIDTH * 0.25),  // Контакты
        static_cast<int>(PAGE_WIDTH * 0.25)   // Направление
    };

    int currentY = TOP_MARGIN;
    int pageNumber = 1;


    painter.setFont(titleFont);
    painter.drawText(LEFT_MARGIN, currentY, title);
    currentY += TITLE_SPACING;

    painter.setFont(dataFont);
    painter.drawText(LEFT_MARGIN, currentY,
                     "Дата формирования: " + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
    currentY += TITLE_SPACING * 2;

    if (model->rowCount() == 0) {
        painter.setFont(titleFont);
        painter.drawText(LEFT_MARGIN, currentY, "Нет данных для отображения");
        painter.end();
        QMessageBox::information(this, "Информация", "Нет данных для отчета.");
        return;
    }


    painter.setFont(headerFont);
    int xPos = LEFT_MARGIN;
    QStringList headers = {"№", "ФИО", "Контакты", "Направление"};
    for (int col = 0; col < headers.size(); ++col) {
        painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
        painter.drawText(
            QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
            Qt::AlignCenter,
            headers[col]
            );
        xPos += colWidths[col];
    }
    currentY += HEADER_HEIGHT;


    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        if (currentY + ROW_HEIGHT > writer.height() - TOP_MARGIN) {
            writer.newPage();
            currentY = TOP_MARGIN;
            pageNumber++;


            xPos = LEFT_MARGIN;
            painter.setFont(headerFont);
            for (int col = 0; col < headers.size(); ++col) {
                painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
                painter.drawText(
                    QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                    Qt::AlignCenter,
                    headers[col]
                    );
                xPos += colWidths[col];
            }
            currentY += HEADER_HEIGHT;
            painter.setFont(dataFont);
        }

        xPos = LEFT_MARGIN;
        for (int col = 0; col < model->columnCount(); ++col) {
            QString text = model->data(model->index(row, col)).toString();
            painter.drawRect(xPos, currentY, colWidths[col], ROW_HEIGHT);
            painter.drawText(
                QRect(xPos + 5, currentY, colWidths[col] - 10, ROW_HEIGHT),
                Qt::AlignLeft | Qt::AlignVCenter,
                text
                );
            xPos += colWidths[col];
        }
        currentY += ROW_HEIGHT;
    }

    painter.end();
    QMessageBox::information(this, "Успех", QString("Отчет успешно сохранен в файл:\n%1").arg(fileName));
}



void Subjects::on_btnSub_by_Fac_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Предметы по направлению"));
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


    QSqlQueryModel *subjectsModel = new QSqlQueryModel(this);
    subjectsModel->setQuery(QString(
                                "SELECT s.title, s.learning_hours, s.id_subject " // Добавляем id_subject для получения преподавателей
                                "FROM subjects s "
                                "WHERE s.id_faculty = '%1' "
                                "ORDER BY s.title").arg(facultyId), dbconn);

    if (subjectsModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить предметы:\n" + subjectsModel->lastError().text());
        return;
    }


    class SubjectsWithTeachersModel : public QAbstractTableModel {
        QSqlQueryModel* sourceModel;
        Subjects* parent;
    public:
        SubjectsWithTeachersModel(QSqlQueryModel* model, Subjects* p) :
            sourceModel(model), parent(p) {}

        int rowCount(const QModelIndex& = QModelIndex()) const override {
            return sourceModel->rowCount();
        }

        int columnCount(const QModelIndex& = QModelIndex()) const override {
            return 3; // Название, Часы, Преподаватель
        }

        QVariant data(const QModelIndex &index, int role) const override {
            if (!index.isValid() || role != Qt::DisplayRole)
                return QVariant();

            if (index.column() < 2) {
                return sourceModel->data(sourceModel->index(index.row(), index.column()));
            }
            else {
                QString subjectId = sourceModel->data(sourceModel->index(index.row(), 2)).toString();
                return parent->getTeachersForSubject(subjectId);
            }
        }

        QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
            if (role != Qt::DisplayRole)
                return QVariant();

            if (orientation == Qt::Horizontal) {
                switch(section) {
                case 0: return "Название";
                case 1: return "Часы обучения";
                case 2: return "Преподаватель";
                }
            }
            else if (orientation == Qt::Vertical) {
                // Возвращаем номер строки + 1 (нумерация с 1)
                return section + 1;
            }
            return QVariant();
        }
    };
    SubjectsWithTeachersModel* customModel = new SubjectsWithTeachersModel(subjectsModel, this);

    QDialog *subjectsDialog = new QDialog(this);
    subjectsDialog->setWindowTitle(QString("Предметы направления: %1").arg(facultyTitle));
    subjectsDialog->setMinimumSize(900, 600);

    QVBoxLayout *layout = new QVBoxLayout(subjectsDialog);

    QPushButton *btnPdf = new QPushButton("Отчет .pdf", subjectsDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, facultyId, facultyTitle]() {
        QSqlQueryModel pdfModel;
        pdfModel.setQuery(QString(
                              "SELECT ROW_NUMBER() OVER (ORDER BY s.title) as num, "
                              "s.title, s.learning_hours, s.id_subject "
                              "FROM subjects s "
                              "WHERE s.id_faculty = '%1' "
                              "ORDER BY s.title").arg(facultyId), dbconn);
        generateSubjectsPdf(&pdfModel, QString("Предметы направления %1").arg(facultyTitle));
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(subjectsDialog);
    tableView->setModel(customModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableView->setColumnWidth(0, 300); // Название
    tableView->setColumnWidth(1, 150); // Часы
    tableView->setColumnWidth(2, 350); // Преподаватель

    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", subjectsDialog);
    connect(btnClose, &QPushButton::clicked, subjectsDialog, &QDialog::close);
    layout->addWidget(btnClose);

    subjectsDialog->exec();
}

void Subjects::generateSubjectsPdf(QSqlQueryModel *model, const QString &title)
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет как PDF",
        QString("Предметы_%1.pdf").arg(title),
        "PDF Files (*.pdf)");

    if (fileName.isEmpty()) return;

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));
    writer.setResolution(96);

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось инициализировать QPainter");
        return;
    }


    QFont titleFont("Arial", 14, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont dataFont("Arial", 9);

    const int PAGE_WIDTH = writer.width();
    const int LEFT_MARGIN = 75;
    const int TOP_MARGIN = 75;
    const int ROW_HEIGHT = 30;
    const int HEADER_HEIGHT = 35;
    const int TITLE_SPACING = 40;


    const int colWidths[] = {
        static_cast<int>(PAGE_WIDTH * 0.08),  // №
        static_cast<int>(PAGE_WIDTH * 0.32),  // Название
        static_cast<int>(PAGE_WIDTH * 0.15),  // Часы обучения
        static_cast<int>(PAGE_WIDTH * 0.45)   // Преподаватель
    };

    int currentY = TOP_MARGIN;
    int pageNumber = 1;


    painter.setFont(titleFont);
    painter.drawText(LEFT_MARGIN, currentY, title);
    currentY += TITLE_SPACING;

    painter.setFont(dataFont);
    painter.drawText(LEFT_MARGIN, currentY,
                     "Дата формирования: " + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
    currentY += TITLE_SPACING * 2;

    if (model->rowCount() == 0) {
        painter.setFont(titleFont);
        painter.drawText(LEFT_MARGIN, currentY, "Нет данных для отображения");
        painter.end();
        QMessageBox::information(this, "Информация", "Нет данных для отчета.");
        return;
    }


    painter.setFont(headerFont);
    int xPos = LEFT_MARGIN;
    QStringList headers = {"№", "Название", "Часы обучения", "Преподаватель"};
    for (int col = 0; col < headers.size(); ++col) {
        painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
        painter.drawText(
            QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
            Qt::AlignCenter,
            headers[col]
            );
        xPos += colWidths[col];
    }
    currentY += HEADER_HEIGHT;


    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        if (currentY + ROW_HEIGHT > writer.height() - TOP_MARGIN) {
            writer.newPage();
            currentY = TOP_MARGIN;
            pageNumber++;


            xPos = LEFT_MARGIN;
            painter.setFont(headerFont);
            for (int col = 0; col < headers.size(); ++col) {
                painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
                painter.drawText(
                    QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                    Qt::AlignCenter,
                    headers[col]
                    );
                xPos += colWidths[col];
            }
            currentY += HEADER_HEIGHT;
            painter.setFont(dataFont);
        }

        xPos = LEFT_MARGIN;
        for (int col = 0; col < 3; ++col) { // Первые 3 колонки из модели
            QString text = model->data(model->index(row, col)).toString();
            painter.drawRect(xPos, currentY, colWidths[col], ROW_HEIGHT);
            painter.drawText(
                QRect(xPos + 5, currentY, colWidths[col] - 10, ROW_HEIGHT),
                Qt::AlignLeft | Qt::AlignVCenter,
                text
                );
            xPos += colWidths[col];
        }


        QString subjectId = model->data(model->index(row, 3)).toString();
        QString teachers = getTeachersForSubject(subjectId);
        painter.drawRect(xPos, currentY, colWidths[3], ROW_HEIGHT);
        painter.drawText(
            QRect(xPos + 5, currentY, colWidths[3] - 10, ROW_HEIGHT),
            Qt::AlignLeft | Qt::AlignVCenter,
            teachers
            );
        xPos += colWidths[3];

        currentY += ROW_HEIGHT;
    }

    painter.end();
    QMessageBox::information(this, "Успех", QString("Отчет успешно сохранен в файл:\n%1").arg(fileName));
}

void Subjects::on_btnAllSubs_clicked()
{

    QSqlQueryModel *subjectsModel = new QSqlQueryModel(this);
    subjectsModel->setQuery(
        "SELECT s.title, s.learning_hours, s.id_subject, f.title as faculty_title "
        "FROM subjects s "
        "JOIN faculties f ON s.id_faculty = f.id_faculty "
        "ORDER BY s.title", dbconn);

    if (subjectsModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить предметы:\n" + subjectsModel->lastError().text());
        return;
    }


    class SubjectsWithTeachersModel : public QAbstractTableModel {
        QSqlQueryModel* sourceModel;
        Subjects* parent;
    public:
        SubjectsWithTeachersModel(QSqlQueryModel* model, Subjects* p) :
            sourceModel(model), parent(p) {}

        int rowCount(const QModelIndex& = QModelIndex()) const override {
            return sourceModel->rowCount();
        }

        int columnCount(const QModelIndex& = QModelIndex()) const override {
            return 4; // Название, Часы, Направление, Преподаватель
        }

        QVariant data(const QModelIndex &index, int role) const override {
            if (!index.isValid() || role != Qt::DisplayRole)
                return QVariant();

            switch(index.column()) {
            case 0: return sourceModel->data(sourceModel->index(index.row(), 0)); // Название
            case 1: return sourceModel->data(sourceModel->index(index.row(), 1)); // Часы
            case 2: return sourceModel->data(sourceModel->index(index.row(), 3)); // Направление
            case 3: {
                QString subjectId = sourceModel->data(sourceModel->index(index.row(), 2)).toString();
                return parent->getTeachersForSubject(subjectId);
            }
            default: return QVariant();
            }
        }

        QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
            if (role != Qt::DisplayRole)
                return QVariant();

            if (orientation == Qt::Horizontal) {
                switch(section) {
                case 0: return "Название";
                case 1: return "Часы обучения";
                case 2: return "Направление";
                case 3: return "Преподаватель";
                }
            }
            else if (orientation == Qt::Vertical) {
                return section + 1; // Нумерация строк с 1
            }
            return QVariant();
        }
    };
    SubjectsWithTeachersModel* customModel = new SubjectsWithTeachersModel(subjectsModel, this);

    QDialog *subjectsDialog = new QDialog(this);
    subjectsDialog->setWindowTitle("Все предметы");
    subjectsDialog->setMinimumSize(1000, 600);

    QVBoxLayout *layout = new QVBoxLayout(subjectsDialog);

    QPushButton *btnPdf = new QPushButton("Отчет .pdf", subjectsDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this]() {
        QSqlQueryModel pdfModel;
        pdfModel.setQuery(
            "SELECT ROW_NUMBER() OVER (ORDER BY s.title) as num, "
            "s.title, s.learning_hours, f.title as faculty_title, s.id_subject "
            "FROM subjects s "
            "JOIN faculties f ON s.id_faculty = f.id_faculty "
            "ORDER BY s.title", dbconn);
        generateAllSubjectsPdf(&pdfModel, "Все предметы");
    });
    layout->addWidget(btnPdf);

    QTableView *tableView = new QTableView(subjectsDialog);
    tableView->setModel(customModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Настройка ширины колонок
    tableView->setColumnWidth(0, 250); // Название
    tableView->setColumnWidth(1, 120); // Часы
    tableView->setColumnWidth(2, 200); // Направление
    tableView->setColumnWidth(3, 350); // Преподаватель

    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", subjectsDialog);
    connect(btnClose, &QPushButton::clicked, subjectsDialog, &QDialog::close);
    layout->addWidget(btnClose);

    subjectsDialog->exec();
}

void Subjects::generateAllSubjectsPdf(QSqlQueryModel *model, const QString &title)
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет как PDF",
        QString("Все_предметы.pdf"),
        "PDF Files (*.pdf)");

    if (fileName.isEmpty()) return;

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
    const int LEFT_MARGIN = 50;
    const int TOP_MARGIN = 50;
    const int ROW_HEIGHT = 30;
    const int HEADER_HEIGHT = 35;
    const int TITLE_SPACING = 40;

    // Ширина колонок (№, Название, Часы, Направление, Преподаватель)
    const int colWidths[] = {
        static_cast<int>(PAGE_WIDTH * 0.07),  // №
        static_cast<int>(PAGE_WIDTH * 0.25),  // Название
        static_cast<int>(PAGE_WIDTH * 0.12),  // Часы
        static_cast<int>(PAGE_WIDTH * 0.20), // Направление
        static_cast<int>(PAGE_WIDTH * 0.36)   // Преподаватель
    };

    int currentY = TOP_MARGIN;
    int pageNumber = 1;

    // Заголовок отчета
    painter.setFont(titleFont);
    painter.drawText(LEFT_MARGIN, currentY, title);
    currentY += TITLE_SPACING;

    painter.setFont(dataFont);
    painter.drawText(LEFT_MARGIN, currentY,
                     "Дата формирования: " + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
    currentY += TITLE_SPACING * 2;

    if (model->rowCount() == 0) {
        painter.setFont(titleFont);
        painter.drawText(LEFT_MARGIN, currentY, "Нет данных для отображения");
        painter.end();
        QMessageBox::information(this, "Информация", "Нет данных для отчета.");
        return;
    }

    // Заголовки таблицы
    painter.setFont(headerFont);
    int xPos = LEFT_MARGIN;
    QStringList headers = {"№", "Название", "Часы", "Направление", "Преподаватель"};
    for (int col = 0; col < headers.size(); ++col) {
        painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
        painter.drawText(
            QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
            Qt::AlignCenter,
            headers[col]
            );
        xPos += colWidths[col];
    }
    currentY += HEADER_HEIGHT;

    // Данные таблицы
    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        if (currentY + ROW_HEIGHT > writer.height() - TOP_MARGIN) {
            writer.newPage();
            currentY = TOP_MARGIN;
            pageNumber++;

            // Повторяем заголовки
            xPos = LEFT_MARGIN;
            painter.setFont(headerFont);
            for (int col = 0; col < headers.size(); ++col) {
                painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
                painter.drawText(
                    QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                    Qt::AlignCenter,
                    headers[col]
                    );
                xPos += colWidths[col];
            }
            currentY += HEADER_HEIGHT;
            painter.setFont(dataFont);
        }

        xPos = LEFT_MARGIN;
        for (int col = 0; col < 4; ++col) { // Первые 4 колонки из модели
            QString text = model->data(model->index(row, col)).toString();
            painter.drawRect(xPos, currentY, colWidths[col], ROW_HEIGHT);
            painter.drawText(
                QRect(xPos + 5, currentY, colWidths[col] - 10, ROW_HEIGHT),
                Qt::AlignLeft | Qt::AlignVCenter,
                text
                );
            xPos += colWidths[col];
        }

        // Колонка с преподавателями
        QString subjectId = model->data(model->index(row, 4)).toString();
        QString teachers = getTeachersForSubject(subjectId);
        painter.drawRect(xPos, currentY, colWidths[4], ROW_HEIGHT);
        painter.drawText(
            QRect(xPos + 5, currentY, colWidths[4] - 10, ROW_HEIGHT),
            Qt::AlignLeft | Qt::AlignVCenter,
            teachers
            );
        xPos += colWidths[4];

        currentY += ROW_HEIGHT;
    }

    painter.end();
    QMessageBox::information(this, "Успех", QString("Отчет успешно сохранен в файл:\n%1").arg(fileName));
}


void Subjects::on_btnHome_clicked()
{
    emit returnToMainMenu();
    this->close();
}

void Subjects::setupPermissions()
{
    switch(currentUserRole) {
    case UserRole::Admin:
        // Для администратора все доступно
        ui->le_id_sub->setVisible(false);
        ui->lb_id_sub->setVisible(false);
        //ui->le_id_sub->setEnabled(false);
        break;
    case UserRole::Teacher:
        // Для преподавателя ограничиваем редактирование
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btnStud_by_Sub->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_sub->setVisible(false);
        ui->lb_id_sub->setVisible(false);
        ui->le_id_sub->setEnabled(false);
        ui->cb_title_sub->setEnabled(false);
        ui->le_learning_hours->setEnabled(false);
        ui->cb_id_faculty->setEnabled(false);
        ui->btnStud_by_Sub->setEnabled(false);
        ui->btnAllSubs->setVisible(false);
        ui->btnAllSubs->setEnabled(false);

        break;
    case UserRole::Student:
        // Для студента только просмотр
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btnTeach_by_Sub->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_sub->setVisible(false);
        ui->lb_id_sub->setVisible(false);
        ui->le_id_sub->setEnabled(false);
        ui->cb_title_sub->setEnabled(false);
        ui->le_learning_hours->setEnabled(false);
        ui->cb_id_faculty->setEnabled(false);
        ui->btnTeach_by_Sub->setEnabled(false);
        ui->btnAllSubs->setVisible(false);
        ui->btnAllSubs->setEnabled(false);
    }
}


