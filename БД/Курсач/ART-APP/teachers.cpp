#include "teachers.h"
#include "ui_teachers.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include "schedules.h"
#include <QInputDialog>
#include <QDialog>
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QDateTime>
#include "schedules.h"

Teachers::Teachers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Teachers)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::ApplicationModal);

    dbconnect();
    setupModel();
    fillFioComboBox();
    fillFacultyComboBox();
    fillPostComboBox();
    setupTableWidget();
    refreshFields();
    setupPermissions();

    setupPostCompleter();
    setupFacultyCompleter();


    connect(ui->le_search_te, &QLineEdit::textChanged, this, &Teachers::on_le_search_te_textChanged);

}

Teachers::~Teachers()
{
    if (dbconn.isOpen()) {
        dbconn.close();
    }
    delete ui;
}

void Teachers::setupTableWidget()
{
    ui->twData_te->setColumnCount(5);
    ui->twData_te->setHorizontalHeaderLabels({"ID", "ФИО", "Контакты", "Должность", "Направление"});
    ui->twData_te->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twData_te->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData_te->setEditTriggers(QAbstractItemView::NoEditTriggers);
    refreshTableData();
    connect(ui->twData_te, &QTableWidget::cellClicked, this, &Teachers::onTableRowClicked);
    ui->twData_te->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->twData_te->setColumnHidden(0, true);
}

void Teachers::refreshTableData()
{
    ui->twData_te->setRowCount(0);

    for (int row = 0; row < model->rowCount(); ++row) {
        QSqlRecord record = model->record(row);
        ui->twData_te->insertRow(row);

        ui->twData_te->setItem(row, 0, new QTableWidgetItem(record.value("id_teacher").toString()));
        ui->twData_te->setItem(row, 1, new QTableWidgetItem(record.value("fio").toString()));
        ui->twData_te->setItem(row, 2, new QTableWidgetItem(record.value("contacts").toString()));
        ui->twData_te->setItem(row, 3, new QTableWidgetItem(record.value("post").toString()));
        ui->twData_te->setItem(row, 4, new QTableWidgetItem(getFacultyTitleById(record.value("id_faculty").toString())));
    }


    ui->twData_te->resizeColumnsToContents();
}

void Teachers::onTableRowClicked(int row)
{
    if (row >= 0 && row < ui->twData_te->rowCount()) {
        QString id = ui->twData_te->item(row, 0)->text();
        for (int i = 0; i < model->rowCount(); ++i) {
            if (model->record(i).value("id_teacher").toString() == id) {
                currentRow = i;
                refreshFields();
                break;
            }
        }
    }
}


void Teachers::highlightCurrentRowInTable()
{
    QString currentId = ui->le_id_te->text();
    for (int row = 0; row < ui->twData_te->rowCount(); ++row) {
        if (ui->twData_te->item(row, 0)->text() == currentId) {
            ui->twData_te->selectRow(row);
            break;
        }
    }
}

void Teachers::dbconnect()
{
    if (!dbconn.isOpen()) {
        dbconn = QSqlDatabase::addDatabase("QPSQL", "teachers_connection");
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

void Teachers::setupModel()
{
    model = new QSqlTableModel(this, dbconn);
    model->setTable("teachers");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(model->fieldIndex("id_teacher"), Qt::AscendingOrder);

    if (!model->select()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка");
        msgBox.setText("Ошибка загрузки данных:\n" + model->lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }

    currentRow = 0;
}

void Teachers::refreshFields()
{
    if(model->rowCount() == 0) {
        clearFields();
        return;
    }

    QSqlRecord record = model->record(currentRow);
    ui->le_id_te->setText(record.value("id_teacher").toString());


    QString currentFio = record.value("fio").toString();
    int fioIndex = ui->cb_fio_te->findText(currentFio, Qt::MatchFixedString);
    if(fioIndex >= 0) {
        ui->cb_fio_te->setCurrentIndex(fioIndex);
    } else {
        ui->cb_fio_te->setCurrentText(record.value("fio").toString());
    }

    ui->le_contacts_te->setText(record.value("contacts").toString());
    int postIndex = ui->cb_post->findText(record.value("post").toString());
    if (postIndex != -1) {
        ui->cb_post->setCurrentIndex(postIndex);
    } else {
        ui->cb_post->addItem(record.value("post").toString());
        ui->cb_post->setCurrentIndex(ui->cb_post->count() - 1);

    }

    QString facultyId = record.value("id_faculty").toString();
    QString facultyTitle = getFacultyTitleById(facultyId);


    if (!facultyTitle.isEmpty()) {
        int facultyIndex = ui->cb_id_faculty->findText(facultyTitle, Qt::MatchFixedString);
        if (facultyIndex >= 0) {
            ui->cb_id_faculty->setCurrentIndex(facultyIndex);
        } else {
            ui->cb_id_faculty->setCurrentText(facultyTitle);
        }
    } else {
        ui->cb_id_faculty->setCurrentText(facultyTitle);
    }
    highlightCurrentRowInTable();


    highlightCurrentRowInTable();
}

void Teachers::clearFields()
{
    ui->le_id_te->clear();
    ui->le_id_te->setPlaceholderText("");
    ui->cb_fio_te->clearEditText();
    ui->le_contacts_te->clear();
    ui->cb_post->clearEditText();
    ui->cb_id_faculty->clearEditText();
}


int Teachers::getNextAvailableId()
{
    QSqlQuery query(dbconn);
    if (query.exec("SELECT MAX(id_teacher::integer) FROM teachers") && query.next()) {
        return query.value(0).toInt() + 1;
    }
    return 1;
}



void Teachers::fillFioComboBox()
{
    ui->cb_fio_te->clear();
    QSqlQuery query(dbconn);
    if (!query.exec("SELECT DISTINCT fio FROM teachers ORDER BY fio")) {
        qCritical() << "Failed to query fio values:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        ui->cb_fio_te->addItem(query.value(0).toString());
    }

    ui->cb_fio_te->setEditable(true);
    ui->cb_fio_te->setInsertPolicy(QComboBox::NoInsert);
}

void Teachers::fillFacultyComboBox()
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

    ui->cb_id_faculty->completer()->setCompletionMode(QCompleter::PopupCompletion);
    ui->cb_id_faculty->completer()->setMaxVisibleItems(5);
}

void Teachers::fillPostComboBox()
{
    ui->cb_post->clear();
    QSqlQuery query(dbconn);
    if (!query.exec("SELECT DISTINCT post FROM teachers ORDER BY post")) {
        qCritical() << "Failed to query post values:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        ui->cb_post->addItem(query.value(0).toString());
    }

    ui->cb_post->setEditable(true);
    ui->cb_post->setInsertPolicy(QComboBox::NoInsert);

    ui->cb_post->completer()->setCompletionMode(QCompleter::PopupCompletion);
    ui->cb_post->completer()->setMaxVisibleItems(3);
}

QString Teachers::getFacultyIdByTitle(const QString &title)
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

QString Teachers::getFacultyTitleById(const QString &id)
{
    return facultyMap.key(id, "");
}

/*QString Teachers::getPostIdByTitle(const QString &title)
{
    if (postMap.contains(title)) {
        return postMap.value(title);
    }

    for (auto it = postMap.constBegin(); it != postMap.constEnd(); ++it) {
        if (it.key().compare(title, Qt::CaseInsensitive) == 0) {
            return it.value();
        }
    }

    return "";
}

QString Teachers::getPostTitleById(const QString &id)
{
    return postMap.key(id, "");
}
*/

void Teachers::setupPostCompleter()
{
    QSqlQuery query(dbconn);
    if (!query.exec("SELECT DISTINCT post FROM teachers ORDER BY post")) {
        qCritical() << "Failed to query post values:" << query.lastError().text();
        return;
    }

    QStringList postList;
    while (query.next()) {
        postList << query.value(0).toString();
    }

    QCompleter* postCompleter = new QCompleter(postList, this);
    postCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    postCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_post->setCompleter(postCompleter);
}

void Teachers::setupFacultyCompleter()
{
    QSqlQuery query(dbconn);
    if (!query.exec("SELECT title FROM faculties ORDER BY title")) {
        qCritical() << "Failed to query faculty values:" << query.lastError().text();
        return;
    }

    QStringList facultyList;
    while (query.next()) {
        facultyList << query.value(0).toString();
    }

    QCompleter* facultyCompleter = new QCompleter(facultyList, this);
    facultyCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    facultyCompleter->setFilterMode(Qt::MatchContains);
    ui->cb_id_faculty->setCompleter(facultyCompleter);
}

void Teachers::on_btnPrevious_clicked()
{
    if (currentRow > 0) {
        currentRow--;
        refreshFields();
    }
}

void Teachers::on_btnAddNew_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Добавление",
                                                              "Хотите добавить нового преподавателя?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        clearFields();
        ui->le_id_te->setPlaceholderText("Оставьте пустым для автоназначения");
        ui->le_id_te->setEnabled(true);
        ui->cb_fio_te->setEnabled(true);
        ui->le_contacts_te->setEnabled(true);
        ui->cb_post->setEnabled(true);
        ui->cb_id_faculty->setEnabled(true);
        ui->cb_fio_te->setFocus();
    }
}

void Teachers::on_btnEditRow_clicked()
{
    if(model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Редактирование");
    msgBox.setText("Вы действительно хотите редактировать данные преподавателя?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if(msgBox.clickedButton() == btnYes) {
        ui->le_id_te->setEnabled(false);
        ui->cb_fio_te->setEnabled(true);
        ui->le_contacts_te->setEnabled(true);
        ui->cb_post->setEnabled(true);
        ui->cb_id_faculty->setEnabled(true);
    }
}

void Teachers::on_btnDelete_clicked()
{
    if (model->rowCount() == 0) return;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Удаление");
    msgBox.setText("Вы действительно хотите удалить преподавателя?");
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
        infoBox.setText("Преподаватель удален!");
        infoBox.setIcon(QMessageBox::Information);
        infoBox.exec();
    }
}

void Teachers::on_btnNext_clicked()
{
    if (currentRow < model->rowCount() - 1) {
        currentRow++;
        refreshFields();
    }
}

void Teachers::on_btnSave_clicked()
{
    QString id = ui->le_id_te->text().trimmed();
    QString fio = ui->cb_fio_te->currentText().trimmed();
    QString contacts = ui->le_contacts_te->text().trimmed();
    QString post = ui->cb_post->currentText().trimmed();
    QString facultyTitle = ui->cb_id_faculty->currentText().trimmed();

    if (fio.isEmpty() || contacts.isEmpty() || post.isEmpty() || facultyTitle.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }


    bool isNewRecord = ui->le_id_te->isEnabled();
    if (isNewRecord && id.isEmpty()) {

        id = QString::number(getNextAvailableId());
    } else if (isNewRecord) {
        // Проверяем, не существует ли уже запись с таким ID
        QSqlQuery checkQuery(dbconn);
        checkQuery.prepare("SELECT 1 FROM teachers WHERE id_teacher = ?");
        checkQuery.addBindValue(id);
        if (checkQuery.exec() && checkQuery.next()) {
            QMessageBox::warning(this, "Ошибка", "Преподаватель с таким ID уже существует!");
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
        query.prepare("INSERT INTO teachers (id_teacher, fio, contacts, post, id_faculty) VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(id);
        query.addBindValue(fio);
        query.addBindValue(contacts);
        query.addBindValue(post);
        query.addBindValue(facultyId);
    } else {
        query.prepare("UPDATE teachers SET fio = ?, contacts = ?, post = ?, id_faculty = ? WHERE id_teacher = ?");
        query.addBindValue(fio);
        query.addBindValue(contacts);
        query.addBindValue(post);
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
    fillPostComboBox();


    for (int i = 0; i < model->rowCount(); ++i) {
        if (model->record(i).value("id_teacher").toString() == id) {
            currentRow = i;
            refreshFields();
            break;
        }
    }

    QMessageBox::information(this, "Успех", "Данные сохранены!");
}

void Teachers::on_btnLast_clicked()
{
    currentRow = model->rowCount() - 1;
    refreshFields();
}

void Teachers::on_btn_to_schedules_clicked()
{
    Schedules *schedulesForm = new Schedules();
    schedulesForm->show();
    this->close();
}

void Teachers::on_btnHome_clicked()
{
    emit returnToMainMenu();
    this->close();
}

void Teachers::on_le_search_te_textChanged(const QString &text)
{
    QString filter = QString("fio ILIKE '%%1%' OR contacts ILIKE '%%1%' OR "
                             "id_faculty IN (SELECT id_faculty FROM faculties WHERE title ILIKE '%%1%')")
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

void Teachers::on_btnTeach_by_Fac_clicked()
{
    QInputDialog dialog(this);
    dialog.setWindowTitle(tr("Преподаватели по направлению"));
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


    QSqlQueryModel *teachersModel = new QSqlQueryModel(this);
    teachersModel->setQuery(QString(
                                "SELECT fio, contacts, post "
                                "FROM teachers "
                                "WHERE id_faculty = '%1' "
                                "ORDER BY fio").arg(facultyId), dbconn);

    if (teachersModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить преподавателей:\n" + teachersModel->lastError().text());
        return;
    }

    QDialog *teachersDialog = new QDialog(this);
    teachersDialog->setWindowTitle(QString("Преподаватели направления: %1").arg(facultyTitle));
    teachersDialog->setMinimumSize(600, 400);

    QVBoxLayout *layout = new QVBoxLayout(teachersDialog);


    QPushButton *btnPdf = new QPushButton("Отчет .pdf", teachersDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this, facultyId, facultyTitle]() {
        QSqlQueryModel pdfModel;
        pdfModel.setQuery(QString(
                              "SELECT ROW_NUMBER() OVER (ORDER BY fio) as num, fio, contacts, post "
                              "FROM teachers WHERE id_faculty = '%1' ORDER BY fio").arg(facultyId), dbconn);
        generateTeachersPdf(&pdfModel, facultyTitle);
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

    layout->addWidget(tableView);

    QPushButton *btnClose = new QPushButton("Закрыть", teachersDialog);
    connect(btnClose, &QPushButton::clicked, teachersDialog, &QDialog::close);
    layout->addWidget(btnClose);

    teachersDialog->exec();
}

void Teachers::generateTeachersPdf(QSqlQueryModel *model, const QString &facultyTitle)
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет как PDF",
        QString("Преподаватели_%1.pdf").arg(facultyTitle),
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
    QFont facultyFont("Arial", 12, QFont::Bold);
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont dataFont("Arial", 9);
    QFont footerFont("Arial", 8);

    const int PAGE_WIDTH = writer.width();
    const int PAGE_HEIGHT = writer.height();
    const int LEFT_MARGIN = 75;
    const int RIGHT_MARGIN = 75;
    const int TOP_MARGIN = 75;
    const int BOTTOM_MARGIN = 75;
    const int ROW_HEIGHT = 30;
    const int HEADER_HEIGHT = 35;
    const int TITLE_SPACING = 40;


    const int colWidths[] = {
        static_cast<int>(PAGE_WIDTH * 0.10),  // №
        static_cast<int>(PAGE_WIDTH * 0.35),  // ФИО
        static_cast<int>(PAGE_WIDTH * 0.25),  // Контакты
        static_cast<int>(PAGE_WIDTH * 0.30)   // Должность
    };
    const int TABLE_WIDTH = colWidths[0] + colWidths[1] + colWidths[2] + colWidths[3];

    int currentY = TOP_MARGIN;
    int pageNumber = 1;


    auto drawHeader = [&]() {
        painter.setFont(titleFont);
        painter.drawText(LEFT_MARGIN, currentY, "Список преподавателей");
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
    QStringList headers = {"№", "ФИО", "Контакты", "Должность"};
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
        if (currentY + ROW_HEIGHT > PAGE_HEIGHT - BOTTOM_MARGIN) {
            drawFooter();
            writer.newPage();
            pageNumber++;
            currentY = TOP_MARGIN;
            drawHeader();

            painter.setFont(headerFont);
            xPos = LEFT_MARGIN;
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


void Teachers::on_btn_All_Teach_by_All_Facs_clicked()
{

    QSqlQueryModel *teachersModel = new QSqlQueryModel(this);
    teachersModel->setQuery(
        "SELECT t.fio, t.contacts, t.post, f.title as faculty "
        "FROM teachers t "
        "JOIN faculties f ON t.id_faculty = f.id_faculty "
        "ORDER BY f.title, t.fio",
        dbconn
        );

    if (teachersModel->lastError().isValid()) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось загрузить преподавателей:\n" + teachersModel->lastError().text());
        return;
    }

    QDialog *teachersDialog = new QDialog(this);
    teachersDialog->setWindowTitle("Все преподаватели всех направлений");
    teachersDialog->setMinimumSize(800, 600);

    QVBoxLayout *layout = new QVBoxLayout(teachersDialog);


    QPushButton *btnPdf = new QPushButton("Отчет .pdf", teachersDialog);
    connect(btnPdf, &QPushButton::clicked, this, [this]() {
        QSqlQueryModel pdfModel;
        pdfModel.setQuery(
            "SELECT ROW_NUMBER() OVER (ORDER BY f.title, t.fio) as num, "
            "t.fio, t.contacts, t.post, f.title as faculty "
            "FROM teachers t "
            "JOIN faculties f ON t.id_faculty = f.id_faculty "
            "ORDER BY f.title, t.fio",
            dbconn
            );
        generateAllTeachersPdf(&pdfModel, "Все преподаватели всех направлений");
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

void Teachers::generateAllTeachersPdf(QSqlQueryModel *model, const QString &title)
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить отчет как PDF",
        QString("Все_преподаватели.pdf"),
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


    colWidths[0] = PAGE_WIDTH * 0.08;  // №
    colWidths[1] = PAGE_WIDTH * 0.30;  // ФИО
    colWidths[2] = PAGE_WIDTH * 0.20;  // Контакты
    colWidths[3] = PAGE_WIDTH * 0.22;  // Должность
    colWidths[4] = PAGE_WIDTH * 0.20;  // Направление


    painter.setFont(headerFont);
    int xPos = LEFT_MARGIN;
    QStringList headers = {"№", "ФИО", "Контакты", "Должность", "Направление"};
    for (int col = 0; col < headers.size(); ++col) {
        painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
        painter.drawText(QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                         Qt::AlignCenter,
                         headers[col]);
        xPos += colWidths[col];
    }
    currentY += HEADER_HEIGHT;

    // Данные таблицы
    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        xPos = LEFT_MARGIN;
        for (int col = 0; col < model->columnCount(); ++col) {
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
            for (int col = 0; col < headers.size(); ++col) {
                painter.drawRect(xPos, currentY, colWidths[col], HEADER_HEIGHT);
                painter.drawText(QRect(xPos, currentY, colWidths[col], HEADER_HEIGHT),
                                 Qt::AlignCenter,
                                 headers[col]);
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



void Teachers::setupPermissions()
{
    switch(currentUserRole) {
    case UserRole::Admin:
        // Для администратора все доступно
        ui->le_id_te->setVisible(false);
        ui->lb_id_te->setVisible(false);
        //ui->le_id_te->setEnabled(false);
        break;
    case UserRole::Teacher:
        // Для преподавателя ограничиваем редактирование
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btn_All_Teach_by_All_Facs->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_te->setVisible(false);
        ui->lb_id_te->setVisible(false);
        ui->le_id_te->setEnabled(false);
        ui->cb_fio_te->setEnabled(false);
        ui->le_contacts_te->setEnabled(false);
        ui->cb_post->setEnabled(false);
        ui->cb_id_faculty->setEnabled(false);
        ui->btn_All_Teach_by_All_Facs->setEnabled(false);

        break;
    case UserRole::Student:
        // Для студента только просмотр
        ui->btnAddNew->setVisible(false);
        ui->btnEditRow->setVisible(false);
        ui->btnDelete->setVisible(false);
        ui->btnSave->setVisible(false);
        ui->btn_All_Teach_by_All_Facs->setVisible(false);
        ui->btnAddNew->setEnabled(false);
        ui->btnEditRow->setEnabled(false);
        ui->btnDelete->setEnabled(false);
        ui->btnSave->setEnabled(false);
        ui->le_id_te->setVisible(false);
        ui->lb_id_te->setVisible(false);
        ui->le_id_te->setEnabled(false);
        ui->cb_fio_te->setEnabled(false);
        ui->le_contacts_te->setEnabled(false);
        ui->cb_post->setEnabled(false);
        ui->cb_id_faculty->setEnabled(false);
        ui->btn_All_Teach_by_All_Facs->setEnabled(false);
    }
}
