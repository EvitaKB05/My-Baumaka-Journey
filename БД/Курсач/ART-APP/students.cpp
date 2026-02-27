#include "students.h"
#include "ui_students.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include "marks.h"

Students::Students(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Students)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);
    //setFixedSize(821, 402);

    dbconnect();
    setupModel();
    fillFioComboBox();
    fillFacultyComboBox();
    setupTableWidget();
    refreshFields();
    setupPermissions();

    connect(ui->le_search_st, &QLineEdit::textChanged, this, &Students::on_le_search_st_textChanged);
    connect(ui->btnStud_by_Fac, &QPushButton::clicked, this, &Students::on_btnStud_by_Fac_clicked);
    connect(ui->btn_All_Studs_by_All_Facs, &QPushButton::clicked, this, &Students::on_btn_All_Studs_by_All_Facs_clicked);

}

Students::~Students()
{
    if (dbconn.isOpen()) {
        dbconn.close();
    }
    delete ui;
}
void Students::setupTableWidget()
{
    ui->twData_st->setColumnCount(4);
    ui->twData_st->setHorizontalHeaderLabels({"ID", "ФИО", "Контакты", "Направление"});
    ui->twData_st->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twData_st->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData_st->setEditTriggers(QAbstractItemView::NoEditTriggers);
    refreshTableData();
    connect(ui->twData_st, &QTableWidget::cellClicked, this, &Students::onTableRowClicked);
    ui->twData_st->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->twData_st->setColumnHidden(0, true);
}

void Students::refreshTableData()
{
    ui->twData_st->setRowCount(0);

    for (int row = 0; row < model->rowCount(); ++row) {
        QSqlRecord record = model->record(row);
        ui->twData_st->insertRow(row);

        QTableWidgetItem *idItem = new QTableWidgetItem(record.value("id_student").toString());
        QTableWidgetItem *fioItem = new QTableWidgetItem(record.value("fio").toString());
        QTableWidgetItem *contactsItem = new QTableWidgetItem(record.value("contacts").toString());

        // Получаем название направления по ID
        QString facultyTitle = getFacultyTitleById(record.value("id_faculty").toString());
        QTableWidgetItem *facultyItem = new QTableWidgetItem(facultyTitle);

        ui->twData_st->setItem(row, 0, idItem);
        ui->twData_st->setItem(row, 1, fioItem);
        ui->twData_st->setItem(row, 2, contactsItem);
        ui->twData_st->setItem(row, 3, facultyItem);
    }
}

void Students::onTableRowClicked(int row)
{
    if (row >= 0 && row < ui->twData_st->rowCount()) {
        QString id = ui->twData_st->item(row, 0)->text();
        for (int i = 0; i < model->rowCount(); ++i) {
            if (model->record(i).value("id_student").toString() == id) {
                currentRow = i;
                refreshFields();
                break;
            }
        }
    }
}

void Students::highlightCurrentRowInTable()
{
    QString currentId = ui->le_id_st->text();
    for (int row = 0; row < ui->twData_st->rowCount(); ++row) {
        if (ui->twData_st->item(row, 0)->text() == currentId) {
            ui->twData_st->selectRow(row);
            break;
        }
    }
}
void Students::dbconnect()
{
    if (!dbconn.isOpen()) {
        dbconn = QSqlDatabase::addDatabase("QPSQL", "students_connection");
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

void Students::setupModel()
{
    model = new QSqlTableModel(this, dbconn);
    model->setTable("students");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);


    model->setSort(model->fieldIndex("id_student"), Qt::AscendingOrder);

    if (!model->select()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Ошибка загрузки данных:\n" + model->lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }

    currentRow = 0;
}

void Students::refreshFields()
{
    if(model->rowCount() == 0) {
        clearFields();
        return;
    }

    QSqlRecord record = model->record(currentRow);
    ui->le_id_st->setText(record.value("id_student").toString());

    // Установка ФИО
    QString currentFio = record.value("fio").toString();
    int fioIndex = ui->cb_fio_st->findText(currentFio, Qt::MatchFixedString);
    if(fioIndex >= 0) {
        ui->cb_fio_st->setCurrentIndex(fioIndex);
    } else {
        ui->cb_fio_st->setCurrentText(currentFio);
    }

    // Установка контактов
    ui->le_contacts_st->setText(record.value("contacts").toString());

    // Установка направления
    QString facultyId = record.value("id_faculty").toString();
    QString facultyTitle = getFacultyTitleById(facultyId);
    if(!facultyTitle.isEmpty()) {
        int facultyIndex = ui->cb_id_faculty->findText(facultyTitle, Qt::MatchFixedString);
        if(facultyIndex >= 0) {
            ui->cb_id_faculty->setCurrentIndex(facultyIndex);
        } else {
            ui->cb_id_faculty->setCurrentText(facultyTitle);
        }
    } else {
        ui->cb_id_faculty->setCurrentText("");
    }

    // Выделяем соответствующую строку в таблице
    highlightCurrentRowInTable();
}


void Students::clearFields()
{

    ui->le_id_st->clear();
    ui->le_id_st->setPlaceholderText("");


    ui->cb_fio_st->clearEditText();
    ui->le_contacts_st->clear();
    ui->cb_id_faculty->clearEditText();


    ui->cb_fio_st->setFocus();
}

int Students::getNextAvailableId()
{
    QSqlQuery query(dbconn);
    if (query.exec("SELECT MAX(id_student::integer) FROM students") && query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;
}


void Students::fillFioComboBox()
{
    ui->cb_fio_st->clear();
    QSqlQuery query(dbconn);
    if (!query.exec("SELECT DISTINCT fio FROM students ORDER BY fio")) {
        qCritical() << "Failed to query fio values:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        ui->cb_fio_st->addItem(query.value(0).toString());
    }

    ui->cb_fio_st->setEditable(true);
    ui->cb_fio_st->setInsertPolicy(QComboBox::NoInsert);

}


void Students::fillFacultyComboBox()
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



QString Students::getFacultyIdByTitle(const QString &title)
{
    if (facultyMap.contains(title)) {
        return facultyMap.value(title);
    }

    for (auto it = facultyMap.constBegin(); it != facultyMap.constEnd(); ++it) {
        if (it.key().compare(title, Qt::CaseInsensitive) == 0) {
            return it.value();
        }
    }

    return "";
}

QString Students::getFacultyTitleById(const QString &id)
{
    return facultyMap.key(id,"");
}


void Students::on_btnPrevious_clicked()
{
    if (currentRow > 0) {
        currentRow--;
        refreshFields();
    }
}



void Students::on_btnAddNew_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Добавление",
                                                              "Хотите добавить нового студента?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        clearFields();
        ui->le_id_st->setPlaceholderText("Оставьте пустым для автоназначения");
        ui->le_id_st->setEnabled(true);
        ui->cb_fio_st->setEnabled(true);
        ui->le_contacts_st->setEnabled(true);
        ui->cb_id_faculty->setEnabled(true);
        ui->cb_fio_st->setFocus();
    }
}


void Students::on_btnEditRow_clicked()
{
    if(model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Редактирование");
    msgBox.setText("Вы действительно хотите редактировать данные студента?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if(msgBox.clickedButton() == btnYes) {
        ui->le_id_st->setEnabled(false);
        ui->cb_fio_st->setEnabled(true);
        ui->le_contacts_st->setEnabled(true);
        ui->cb_id_faculty->setEnabled(true);

    }
}


void Students::on_btnDelete_clicked()
{
    if (model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Удаление");
    msgBox.setText("Вы действительно хотите удалить студента?");
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
        fillFioComboBox();

        QMessageBox infoBox(this);
        infoBox.setWindowTitle("Успех");
        infoBox.setText("Студент удален!");
        infoBox.setIcon(QMessageBox::Information);
        infoBox.exec();
    }
}


void Students::on_btnNext_clicked()
{
    if (currentRow < model->rowCount() - 1) {
        currentRow++;
        refreshFields();
    }
}


void Students::on_btnSave_clicked()
{
    QString id = ui->le_id_st->text().trimmed();
    QString fio = ui->cb_fio_st->currentText().trimmed();
    QString contacts = ui->le_contacts_st->text().trimmed();
    QString facultyTitle = ui->cb_id_faculty->currentText().trimmed();

    if (fio.isEmpty() || contacts.isEmpty() || facultyTitle.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }


    bool isNewRecord = ui->le_id_st->isEnabled();
    if (isNewRecord && id.isEmpty()) {
        // Если ID не указан - генерируем автоматически
        id = QString::number(getNextAvailableId());
    } else if (isNewRecord) {
        // Проверяем, не существует ли уже запись с таким ID
        QSqlQuery checkQuery(dbconn);
        checkQuery.prepare("SELECT 1 FROM students WHERE id_student = ?");
        checkQuery.addBindValue(id);
        if (checkQuery.exec() && checkQuery.next()) {
            QMessageBox::warning(this, "Ошибка", "Студент с таким ID уже существует!");
            return;
        }
    }


    QString facultyId = getFacultyIdByTitle(facultyTitle);
    if (facultyId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанное направление не найдено!");
        return;
    }


    QSqlQuery query(dbconn);
    if (isNewRecord) {
        query.prepare("INSERT INTO students (id_student, fio, contacts, id_faculty) VALUES (?, ?, ?, ?)");
        query.addBindValue(id);
        query.addBindValue(fio);
        query.addBindValue(contacts);
        query.addBindValue(facultyId);
    } else {
        query.prepare("UPDATE students SET fio = ?, contacts = ?, id_faculty = ? WHERE id_student = ?");
        query.addBindValue(fio);
        query.addBindValue(contacts);
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
    fillFioComboBox();
    fillFacultyComboBox();

    // Находим и выделяем добавленную/измененную запись
    for (int i = 0; i < model->rowCount(); ++i) {
        if (model->record(i).value("id_student").toString() == id) {
            currentRow = i;
            refreshFields();
            break;
        }
    }

    QMessageBox::information(this, "Успех", "Данные сохранены!");
}


void Students::on_btnLast_clicked()
{
    currentRow = model->rowCount() - 1;
    refreshFields();
}


void Students::on_btn_to_marks_clicked()
{
    Marks *marksForm = new Marks();
    marksForm->show();
    this->close();
}


void Students::on_btnHome_clicked()
{
    emit returnToMainMenu();
    this->close();
}


void Students::on_le_search_st_textChanged(const QString &text)
{
    QString filter = QString("fio ILIKE '%%1%' OR contacts ILIKE '%%1%' OR id_faculty IN "
                             "(SELECT id_faculty FROM faculties WHERE title ILIKE '%%1%')")
                         .arg(text);
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



void Students::on_btnStud_by_Fac_clicked()
{

    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Студенты по направлению"));
    dialog.setLabelText(tr("Пожалуйста, укажите направление:"));
    dialog.setComboBoxItems(facultyMap.keys());
    dialog.setComboBoxEditable(true);
    dialog.setWindowFlags(dialog.windowFlags() | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);


    dialog.setOkButtonText(tr("ОК"));
    dialog.setCancelButtonText(tr("Отмена"));

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    QString facultyTitle = dialog.textValue();
    if (facultyTitle.isEmpty()) {
        return;
    }


    QString facultyId = getFacultyIdByTitle(facultyTitle);
    if (facultyId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Указанное направление не найдено!");
        return;
    }


    QSqlQueryModel *studentsModel = new QSqlQueryModel(this);
    studentsModel->setQuery(QString("SELECT fio, contacts FROM students WHERE id_faculty = '%1' ORDER BY fio").arg(facultyId), dbconn);

    if (studentsModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить студентов:\n" + studentsModel->lastError().text());
        return;
    }


    QDialog *studentsDialog = new QDialog(this);
    studentsDialog->setWindowTitle(QString("Студенты направления: %1").arg(facultyTitle));
    studentsDialog->setMinimumSize(600, 400);

    QVBoxLayout *layout = new QVBoxLayout(studentsDialog);


    QPushButton *btnPdf = new QPushButton("Отчет .pdf", studentsDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, facultyId, facultyTitle]() {

        QSqlQueryModel pdfModel;
        pdfModel.setQuery(QString(
                              "SELECT ROW_NUMBER() OVER (ORDER BY fio) as num, fio, contacts "
                              "FROM students WHERE id_faculty = '%1' ORDER BY fio").arg(facultyId), dbconn);
        generateStudentsPdf(&pdfModel, facultyTitle);
    });
    layout->addWidget(btnPdf);


    QTableView *tableView = new QTableView(studentsDialog);
    tableView->setModel(studentsModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    studentsModel->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
    studentsModel->setHeaderData(1, Qt::Horizontal, tr("Контакты"));

    layout->addWidget(tableView);


    QPushButton *btnClose = new QPushButton("Закрыть", studentsDialog);
    connect(btnClose, &QPushButton::clicked, studentsDialog, &QDialog::close);
    layout->addWidget(btnClose);

    studentsDialog->exec();
}

void Students::generateStudentsPdf(QSqlQueryModel *model, const QString &facultyTitle)
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет как PDF",
        QString("Студенты_%1.pdf").arg(facultyTitle),
        "PDF Files (*.pdf)"
        );

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
    QFont facultyFont("Arial", 12, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont dataFont("Arial", 9);
    QFont footerFont("Arial", 8);


    const int PAGE_WIDTH = writer.width();
    const int PAGE_HEIGHT = writer.height();


    const int LEFT_MARGIN = 75;   // ~20 мм
    const int RIGHT_MARGIN = 75;
    const int TOP_MARGIN = 75;
    const int BOTTOM_MARGIN = 75;


    const int ROW_HEIGHT = 30;
    const int HEADER_HEIGHT = 35;
    const int TITLE_SPACING = 40;


    const int colWidths[] = {
        static_cast<int>(PAGE_WIDTH * 0.10),  // №
        static_cast<int>(PAGE_WIDTH * 0.50),  // ФИО
        static_cast<int>(PAGE_WIDTH * 0.40)   // Контакты
    };
    const int TABLE_WIDTH = colWidths[0] + colWidths[1] + colWidths[2];

    int currentY = TOP_MARGIN;
    int pageNumber = 1;


    auto drawHeader = [&]() {
        painter.setFont(titleFont);
        painter.drawText(LEFT_MARGIN, currentY, "Список студентов");
        currentY += TITLE_SPACING;

        painter.setFont(facultyFont);
        painter.drawText(LEFT_MARGIN, currentY, "Направление: " + facultyTitle);
        currentY += TITLE_SPACING;

        painter.setFont(dataFont);
        painter.drawText(LEFT_MARGIN, currentY,
                         "Дата формирования: " + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
        currentY += TITLE_SPACING * 2;
    };


    auto drawFooter = [&]() {
        painter.setFont(footerFont);
        painter.drawText(
            QRect(LEFT_MARGIN, PAGE_HEIGHT - BOTTOM_MARGIN + 20,
                  PAGE_WIDTH - LEFT_MARGIN - RIGHT_MARGIN, 20),
            Qt::AlignCenter,
            QString("Страница %1").arg(pageNumber)
            );
    };

    // Проверка на пустые данные
    if (model->rowCount() == 0) {
        drawHeader();
        painter.setFont(titleFont);
        painter.drawText(
            QRect(LEFT_MARGIN, currentY, TABLE_WIDTH, 100),
            Qt::AlignCenter,
            "Нет данных для отображения"
            );
        drawFooter();
        painter.end();
        QMessageBox::information(this, "Информация", "Нет данных для отчета.");
        return;
    }


    drawHeader();


    painter.setFont(headerFont);
    int xPos = LEFT_MARGIN;


    QStringList headers = {"№", "ФИО", "Контакты"};
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
        // Проверка на необходимость новой страницы
        if (currentY + ROW_HEIGHT > PAGE_HEIGHT - BOTTOM_MARGIN) {
            drawFooter();
            writer.newPage();
            pageNumber++;
            currentY = TOP_MARGIN;
            drawHeader();

            // Повторяем заголовки таблицы
            painter.setFont(headerFont);
            xPos = LEFT_MARGIN;
            for (int col = 0; col < model->columnCount(); ++col) {
                painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
                painter.drawText(
                    QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                    Qt::AlignCenter,
                    model->headerData(col, Qt::Horizontal).toString()
                    );
                xPos += colWidths[col];
            }
            currentY += HEADER_HEIGHT;
            painter.setFont(dataFont);
        }

        // Рисуем строку данных
        xPos = LEFT_MARGIN;
        for (int col = 0; col < model->columnCount(); ++col) {
            QString text = model->data(model->index(row, col)).toString();

            painter.drawRect(xPos, currentY, colWidths[col], ROW_HEIGHT);

            QTextOption textOption;
            textOption.setWrapMode(QTextOption::WordWrap);
            textOption.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

            painter.drawText(
                QRect(xPos + 5, currentY, colWidths[col] - 10, ROW_HEIGHT),
                text,
                textOption
                );

            xPos += colWidths[col];
        }
        currentY += ROW_HEIGHT;
    }


    drawFooter();

    painter.end();
    QMessageBox::information(this, "Успех", QString("Отчет успешно сохранен в файл:\n%1").arg(fileName));
}

void Students::on_btn_All_Studs_by_All_Facs_clicked()
{

    QSqlQueryModel *studentsModel = new QSqlQueryModel(this);
    studentsModel->setQuery(
        "SELECT s.fio, s.contacts, f.title as faculty "
        "FROM students s "
        "JOIN faculties f ON s.id_faculty = f.id_faculty "
        "ORDER BY f.title, s.fio",
        dbconn
        );

    if (studentsModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось загрузить студентов:\n" + studentsModel->lastError().text());
        return;
    }


    QDialog *studentsDialog = new QDialog(this);
    studentsDialog->setWindowTitle("Все студенты всех направлений");
    studentsDialog->setMinimumSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(studentsDialog);


    QPushButton *btnPdf = new QPushButton("Отчет .pdf", studentsDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this]() {
        QSqlQueryModel pdfModel;
        pdfModel.setQuery(
            "SELECT ROW_NUMBER() OVER (ORDER BY f.title, s.fio) as num, s.fio, s.contacts, f.title as faculty "
            "FROM students s "
            "JOIN faculties f ON s.id_faculty = f.id_faculty "
            "ORDER BY f.title, s.fio",
            dbconn
            );
        generateAllStudentsPdf(&pdfModel, "Все студенты всех направлений");
    });
    layout->addWidget(btnPdf);


    QTableView *tableView = new QTableView(studentsDialog);
    tableView->setModel(studentsModel);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    //studentsModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    studentsModel->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
    studentsModel->setHeaderData(1, Qt::Horizontal, tr("Контакты"));
    studentsModel->setHeaderData(2, Qt::Horizontal, tr("Направление"));

    layout->addWidget(tableView);


    QPushButton *btnClose = new QPushButton("Закрыть", studentsDialog);
    connect(btnClose, &QPushButton::clicked, studentsDialog, &QDialog::close);
    layout->addWidget(btnClose);

    studentsDialog->exec();
}

void Students::generateAllStudentsPdf(QSqlQueryModel *model, const QString &title)
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет как PDF",
        QString("Все_студенты.pdf"),
        "PDF Files (*.pdf)"
        );

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


    QFont titleFont("Arial", 14, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont dataFont("Arial", 9);

    const int PAGE_WIDTH = writer.width();
    const int LEFT_MARGIN = 20;
    const int TOP_MARGIN = 50;
    const int ROW_HEIGHT = 20;
    const int HEADER_HEIGHT = 25;

    int currentY = TOP_MARGIN;


    painter.setFont(titleFont);
    painter.drawText(LEFT_MARGIN, currentY, title);
    currentY += 30;

    painter.setFont(dataFont);
    painter.drawText(LEFT_MARGIN, currentY,
                     "Дата формирования: " + QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
    currentY += 30;

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
        for(int row = 0; row < model->rowCount(); ++row){
            QFontMetrics fm(dataFont);
            int width = fm.horizontalAdvance(model->data(model->index(row,col)).toString());
            maxColWidth = qMax(maxColWidth, width);
        }

        QFontMetrics fmHeader(headerFont);
        int headerWidth = fmHeader.horizontalAdvance(model->headerData(col, Qt::Horizontal).toString());
        colWidths[col] = qMax(maxColWidth, headerWidth) + 10;
        totalWidth += colWidths[col];
    }

    double widthScaleFactor = (double)(PAGE_WIDTH - 2 * LEFT_MARGIN)/totalWidth;
    for(int col = 0; col < colCount; col++){
        colWidths[col] = colWidths[col]*widthScaleFactor;
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

    // Данные таблицы
    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        xPos = LEFT_MARGIN;
        for (int col = 0; col < colCount; ++col) {
            QString text = model->data(model->index(row, col)).toString();
            painter.drawRect(xPos, currentY, colWidths[col], ROW_HEIGHT);
            painter.drawText(QRect(xPos + 5, currentY, colWidths[col] - 10, ROW_HEIGHT),
                             Qt::AlignLeft | Qt::AlignVCenter,
                             text);
            xPos += colWidths[col];
        }
        currentY += ROW_HEIGHT;

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
    }

    painter.end();
    QMessageBox::information(this, "Успех",
                             QString("Отчет успешно сохранен в файл:\n%1").arg(fileName));
}

void Students::setupPermissions()
{
    switch(currentUserRole) {
    case UserRole::Admin:
        // Для администратора все доступно
        ui->le_id_st->setVisible(false);
        ui->lb_id_st->setVisible(false);
        //ui->le_id_st->setEnabled(false);
        break;
    case UserRole::Teacher:
        // Для преподавателя ограничиваем редактирование
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btn_All_Studs_by_All_Facs->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_st->setVisible(false);
        ui->lb_id_st->setVisible(false);
        ui->le_id_st->setEnabled(false);
        ui->cb_fio_st->setEnabled(false);
        ui->le_contacts_st->setEnabled(false);
        ui->cb_id_faculty->setEnabled(false);
        ui->btn_All_Studs_by_All_Facs->setEnabled(false);

        break;
    case UserRole::Student:
        // Для студента только просмотр
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btn_All_Studs_by_All_Facs->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_st->setVisible(false);
        ui->lb_id_st->setVisible(false);
        ui->le_id_st->setEnabled(false);
        ui->cb_fio_st->setEnabled(false);
        ui->le_contacts_st->setEnabled(false);
        ui->cb_id_faculty->setEnabled(false);
        ui->btn_All_Studs_by_All_Facs->setEnabled(false);
    }
}

