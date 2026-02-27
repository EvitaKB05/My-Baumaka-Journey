#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include "QMessageBox"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_patientVisits(new patientvisits(this))
{
    ui->setupUi(this);
    ui->twPatient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->twPatient->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->twMed->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->twMed->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->btnConnect,SIGNAL(clicked(bool)),this, SLOT(dbconnect()));
    connect(ui->btnSelectAll,SIGNAL(clicked(bool)),this, SLOT(selectAll()));
    connect(ui->btnAdd, SIGNAL(clicked(bool)),this,SLOT(add()));
    connect(ui->btnDel, SIGNAL(clicked(bool)),this,SLOT(del()));
    connect(ui->btnEdit, SIGNAL(clicked(bool)),this,SLOT(edit()));
    connect(ui->twPatient, &QTableWidget::itemDoubleClicked,this, &MainWindow::showPatientVisits);
    connect(ui->twPatient, &QTableWidget::itemSelectionChanged, this, &MainWindow::loadMedicalCard);
}

MainWindow::~MainWindow()
{
    if( dbconn.isOpen())
        dbconn.close();

    delete ui;
}

void MainWindow::showPatientVisits(){
    int currow = ui->twPatient->currentRow();
    if(currow < 0) {
        QMessageBox::information(this, "Информация", "Выберите пациента из таблицы");
        return;
    }

    QString patientFio = ui->twPatient->item(currow, 0)->text();

    // Проверяем соединение с БД
    if(!dbconn.isOpen()) {
        dbconnect();
        if(!dbconn.isOpen()) {
            QMessageBox::critical(this, "Ошибка", dbconn.lastError().text());
            return;
        }
    }

    // Вызываем метод загрузки визитов
    m_patientVisits->loadPatientVisits(patientFio, dbconn);

    // Показываем окно с визитами
    m_patientVisits->show();
    m_patientVisits->raise();
    m_patientVisits->activateWindow();
}


void MainWindow::upd(){
    if (!dbconn.isOpen())
    {
        dbconnect();
        if (!dbconn.isOpen())
        {
            QMessageBox::critical(this, "Error", dbconn.lastError().text());
            return;
        }
    }

    QSqlQuery query(dbconn);
    if (!query.exec("WITH numbered AS ("
                    "SELECT patient_id, ROW_NUMBER() OVER(ORDER BY patient_id) as new_id "
                    "FROM patient) "
                    "UPDATE patient p SET patient_id = n.new_id "
                    "FROM numbered n WHERE p.patient_id = n.patient_id"))
    {
        QMessageBox::critical(this, "Error", query.lastError().text());
        return;
    }

    if (!query.exec("SELECT setval('patient_patient_id_seq', (SELECT MAX(patient_id) FROM patient))"))
    {
        QMessageBox::critical(this, "Error", query.lastError().text());
        return;
    }
}


void MainWindow::selectAll()
{
    // Очистить содержимое компонента
    ui->twPatient->clearContents();
    ui->twMed->clearContents();
    // Если соединение не открыто, то вызвать нашу функцию для открытия
    // если подключиться не удалось, то вывести сообщение об ошибке и
    // выйти из функции
    if( !dbconn.isOpen() )
    {
        dbconnect();
        if( !dbconn.isOpen() )
        {
            QMessageBox::critical(this,"Error",dbconn.lastError().text());
            return;
        }
    }
    // Создать объект запроса с привязкой к установленному соединению
    QSqlQuery query(dbconn);
    // Создать строку запроса на выборку данных
    QString sqlstr = R"(SELECT
        fio AS "ФИО",
        adress AS "АДРЕС",
        phone AS "ТЕЛЕФОН",
        card_id AS "ID КАРТЫ"
        FROM patient)";

    // Выполнить запрос и поверить его успешность
    if( !query.exec(sqlstr) )
    {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }

    QSqlRecord record = query.record();
    int columnCount = record.count();
    ui->twPatient->setColumnCount(columnCount);
    QStringList headers;
    for(int i=0;i<columnCount;++i){
        headers<<record.fieldName(i);
    }
    ui->twPatient->setHorizontalHeaderLabels(headers);
    // Если запрос активен (успешно завершен),
    // то вывести сообщение о прочитанном количестве строк в окно вывода
    // и установить количество строк для компонента таблицы
    if( query.isActive())
        ui->twPatient->setRowCount( query.size());
    else
        ui->twPatient->setRowCount( 0);
    ui->teResult->append( QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next())
    {
        ui->twPatient->setItem(i,0,new QTableWidgetItem(query.value("ФИО").toString()));
        ui->twPatient->setItem(i,1,new QTableWidgetItem(query.value("АДРЕС").toString()));
        ui->twPatient->setItem(i,2,new QTableWidgetItem(query.value("ТЕЛЕФОН").toString()));
        ui->twPatient->setItem(i,3,new QTableWidgetItem(query.value("ID КАРТЫ").toString()));

        i++;
    }
    ui->twPatient->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twPatient->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twMed->clearContents();
    ui->twMed->setRowCount(1);
    ui->twMed->setColumnCount(5);

    headers.clear();
    headers <<"ID КАРТЫ"<< "ВЕС" << "РОСТ" << "ВОЗРАСТ" << "ДАТА ПРИКРЕПЛЕНИЯ";
     ui->twMed->setHorizontalHeaderLabels(headers);
    ui->twMed->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twMed->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::dbconnect()
{
    if(!dbconn.isOpen())
    {
        // Если соединение не открыто, то вывести список доступных драйверов БД
        // (вывод в поле teResult, метод append добавляет строки).
        ui->teResult->append("SQL drivers:");
        ui->teResult->append(QSqlDatabase::drivers().join(","));
        // Создать глобальную переменную для установки соединения с БД
        dbconn=QSqlDatabase::addDatabase("QPSQL");
        // Установить параметры соединения: имя БД, адрес хоста, логин и пароль пользователя, порт (если отличается от стандартного)
        dbconn.setDatabaseName("testdb");
        dbconn.setHostName("localhost");
        dbconn.setUserName("postgres");
        dbconn.setPassword("wtf123");
        // Открыть соединениe и результат вывести в окно вывода
        if( dbconn.open() )
            ui->teResult->append("Connect is open...");
        else
        {
            ui->teResult->append("Error of connect:");
            ui->teResult->append(dbconn.lastError().text());
        }
    }
    else
        // Если соединение уже открыто, то сообщить об этом
        ui->teResult->append("Connect is already open...");
}


void MainWindow::add()
{
    // Подключиться к БД
    if (!dbconn.isOpen())
    {
        dbconnect();
        if (!dbconn.isOpen())
        {
            QMessageBox::critical(this, "Error", dbconn.lastError().text());
            return;
        }
    }
    QSqlQuery query(dbconn);

    QString syncSeqQuery = "SELECT setval('patient_patient_id_seq',(SELECT MAX(patient_id) FROM patient))" ;
    if(!query.exec(syncSeqQuery)){
        ui->teResult->append(query.lastQuery());
        QMessageBox::critical(this, "Error", query.lastError().text());
        return;
    }

    // Создать строку запроса
    QString sqlstr = "insert into patient(fio,adress,phone,card_id) values(?,?,?,?)";
    // Подготовить запрос
    query.prepare(sqlstr);
    // Передать параметры из полей ввода в запрос
    query.bindValue(0, ui->LeFio->text());
    query.bindValue(1, ui->LeAdress->toPlainText());
    query.bindValue(2, ui->LePhone->text());
    // Если тип поля отличается от строкового, то преобразовать его
    query.bindValue(3, ui->LeCard_id->text().toLongLong());
    // Выполнить запрос
    if (!query.exec())
    {
        ui->teResult->append(query.lastQuery());
        QMessageBox::critical(this, "Error", query.lastError().text());
        return;
    }
    // Если запрос выполнен, то вывести сообщение одобавлении строки
 ui->teResult->append( QString("AddRead %1rows").arg(query.numRowsAffected()) );
// и обновить записи в компоненте таблицы
 selectAll();
}

void MainWindow::del()
{
    // Подключение к БД
    if( !dbconn.isOpen() )
    {
        dbconnect();
        if( !dbconn.isOpen() )
        {
            QMessageBox::critical(this,"Error",dbconn.lastError().text());
            return;
        }
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twPatient->currentRow();
    // Если он меньше 0 (строка не выбрана), то
    // сообщение об ошибке и выход из функции
    if( currow < 0 )
    {
        QMessageBox::critical(this,"Error","Not selected row!");
        return;
    }
    // Спросить у пользователя подтверждение удаления записи
    // Используется статический метод QMessageBox::question
    // для задания вопроса, который возвращает код нажатой кнопки
    if( QMessageBox::question(this,"Delete","Delete row?",
                              QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Cancel)
        return;
    // Создать объект запроса
    QSqlQuery query(dbconn);
    // Создать строку запроса.
    // Вместо подготовки запроса и передачи параметров значение параметра
    // конкатенируется со строкой запроса
    // Обратите,что строковое значение помещается в одинарные кавычки
    // Значение выбирается из компонента таблицы методом item(row,col)
    QString sqlstr = "delete from patient where fio = '"
                     + ui->twPatient->item(currow,0)->text() + "'";
    // Выполнить строку запроса и проверить его успешность
    if( !query.exec(sqlstr) )
    {
        ui->teResult->append( query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }
    // Вывести сообщение об удалении строки
    ui->teResult->append( QString("Del %1 rows").arg(query.numRowsAffected()) );
    // Обновить содержимое компонента таблицы
    upd();
    selectAll();
}


void MainWindow::edit(){
    if (!dbconn.isOpen())
    {
        dbconnect();
        if (!dbconn.isOpen())
        {
            QMessageBox::critical(this, "Error", dbconn.lastError().text());
            return;
        }
    }
    // Проверка выбранной строки
    int currow = ui->twPatient->currentRow();
    if (currow < 0)
    {
        QMessageBox::critical(this, "Error", "Не выбрана строка для редактирования!");
        return;
    }


    QString originalFio = ui->twPatient->item(currow, 0)->text();
    if (originalFio.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Не удалось определить ФИО пациента");
        return;
    }


    QSqlQuery query(dbconn);

    // Подготавливаем параметризованный запрос
    query.prepare("UPDATE patient "
                  "SET fio = :fio, "
                  "adress = :adress, "
                  "phone = :phone, "
                  "card_id = :card_id "
                  "WHERE fio = :original_fio");

    // Привязываем значения
    query.bindValue(":fio", ui->LeFio->text());
    query.bindValue(":adress", ui->LeAdress->toPlainText());
    query.bindValue(":phone", ui->LePhone->text());
    query.bindValue(":card_id", ui->LeCard_id->text().toInt());
    query.bindValue(":original_fio", originalFio);
    // Выполняем запрос
    // Выполнить запрос
    if (!query.exec())
    {
        ui->teResult->append(query.lastQuery());
        QMessageBox::critical(this, "Error", query.lastError().text());
        return;
    }
    // Если запрос выполнен, то вывести сообщение одобавлении строки
    ui->teResult->append( QString("AddRead %1rows").arg(query.numRowsAffected()) );
    // и обновить записи в компоненте таблицы
    upd();
    selectAll();
}

void MainWindow::loadMedicalCard(){

    ui->twMed->clearContents();
    int currow = ui->twPatient->currentRow();
    if(currow<0)return;
    QString cardId=ui->twPatient->item(currow,3)->text();
    if (!dbconn.isOpen()) {
        dbconnect();
        if (!dbconn.isOpen()) {
            QMessageBox::critical(this, "Ошибка", dbconn.lastError().text());
            return;
        }
    }
    QSqlQuery query(dbconn);
    query.prepare("SELECT * "
                  "FROM medcard WHERE card_id = ?");
    query.addBindValue(cardId);
    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }
    if (query.next()) {
        ui->twMed->setRowCount(1);
        ui->twMed->setColumnCount(5);

        QStringList headers;
        headers <<"ID КАРТЫ"<< "ВЕС" << "РОСТ" << "ВОЗРАСТ" << "ДАТА ПРИКРЕПЛЕНИЯ";
        ui->twMed->setHorizontalHeaderLabels(headers);

        ui->twMed->setItem(0, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->twMed->setItem(0, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->twMed->setItem(0, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->twMed->setItem(0, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->twMed->setItem(0, 4, new QTableWidgetItem(query.value(4).toString()));
    }


    ui->twMed->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->twMed->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
