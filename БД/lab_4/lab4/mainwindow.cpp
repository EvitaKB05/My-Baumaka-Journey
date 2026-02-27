
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnConnect,SIGNAL(clicked(bool)),this, SLOT(dbconnect()));
    connect(ui->btnSelectAll, SIGNAL(clicked(bool)), this, SLOT(selectAll()));
    connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->btnDel, SIGNAL(clicked(bool)), this, SLOT(del()));
    connect(ui->btnEdit, SIGNAL(clicked(bool)), this, SLOT(edit()));
    connect(ui->twData, &QTableWidget::itemDoubleClicked,this, &MainWindow::showFaculties);
    // Количество столбцов
    ui->twData->setColumnCount(3);
    // Возможность прокрутки
    ui->twData->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twData->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
    ui->twData->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->twData->setHorizontalHeaderItem(1,new QTableWidgetItem("Title"));
    ui->twData->setHorizontalHeaderItem(2,new QTableWidgetItem("Address"));

    // Последний столбец растягивается при изменении размера формы
    ui->twData->horizontalHeader()->setStretchLastSection(true);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twData->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void MainWindow::showFaculties(){
    int currow = ui->twData->currentRow();
    if(currow < 0) {
        return;
    }

    QString ID = ui->twData->item(currow, 0)->text();

    // Проверяем соединение с БД
    if(!dbconn.isOpen()) {
        dbconnect();
        if(!dbconn.isOpen()) {
            QMessageBox::critical(this, "Ошибка", dbconn.lastError().text());
            return;
        }
    }

    m_faculties = new faculties(this, dbconn);

    // Вызываем метод загрузки визитов
    m_faculties->loadFaculties(ID);

    // Показываем окно с визитами
    m_faculties->show();
    m_faculties->raise();
    m_faculties->activateWindow();
}
MainWindow::~MainWindow()
{
    if( dbconn.isOpen())
        dbconn.close();
    delete ui;
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
        dbconn.setDatabaseName("dbtest");
        dbconn.setHostName("localhost");
        dbconn.setPort(5432);
        dbconn.setUserName("postgres");
        dbconn.setPassword("mrduckword532854");
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

void MainWindow::selectAll()
{
    // Очистить содержимое компонента
    ui->twData->clearContents();
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
    QString sqlstr = "select * from housings";
    // Выполнить запрос и поверить его успешность
    bool query_success = query.exec(sqlstr);
    // Если запрос активен (успешно завершен),
    // то вывести сообщение о прочитанном количестве строк в окно вывода
    // и установить количество строк для компонента таблицы
    if( query_success )
        ui->twData->setRowCount( query.size());
    else
        ui->twData->setRowCount( 0);
    ui->teResult->append( QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next())
    {
        ui->twData->setItem(i,0,new
                           QTableWidgetItem(query.value("id_housing").toString()));
        ui->twData->setItem(i,1,new
                           QTableWidgetItem(query.value("title").toString()));
        ui->twData->setItem(i,2,new
                           QTableWidgetItem(query.value("address").toString()));

        i++;
    }
}

void MainWindow::add()
{
    // Connect to database
    if( !dbconn.isOpen() )
    {
        dbconnect();
        if( !dbconn.isOpen() )
        {
            QMessageBox::critical(this,"Error",dbconn.lastError().text());
            return;
        }
    }

    // First get the maximum current ID
    QSqlQuery maxIdQuery(dbconn);
    if( !maxIdQuery.exec("SELECT MAX(id_housing) FROM housings") )
    {
        QMessageBox::critical(this,"Error",maxIdQuery.lastError().text());
        return;
    }

    int nextId = 1; // Default if table is empty
    if( maxIdQuery.next() )
    {
        nextId = maxIdQuery.value(0).toInt() + 1;
    }

    QSqlQuery query(dbconn);
    QString sqlstr = "INSERT INTO housings(id_housing, title, address) VALUES(?, ?, ?)";
    query.prepare(sqlstr);

    // Set default values if fields are empty
    QString title = ui->teTitle->toPlainText().trimmed();
    QString address = ui->leAddress->text().trimmed();

    if(title.isEmpty()) {
        title = "New Housing " + QString::number(nextId);  // Default title
    }
    if(address.isEmpty()) {
        address = "Unknown Address";  // Default address
    }

    // Bind values with calculated ID and defaults
    query.bindValue(0, nextId);
    query.bindValue(1, title);
    query.bindValue(2, address);

    if( !query.exec() )
    {
        ui->teResult->append( query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }

    // Clear input fields after successful addition
    ui->teTitle->clear();
    ui->leAddress->clear();

    ui->teResult->append( QString("Added new housing (ID: %1, Title: %2, Address: %3)")
                             .arg(nextId)
                             .arg(title)
                             .arg(address) );
    selectAll(); // Refresh the table view
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
    int currow = ui->twData->currentRow();
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
    if( QMessageBox::question(this,"Delete","Удалить строку данных?",
                              QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Cancel)
        return;
    // Создать объект запроса
    QSqlQuery query(dbconn);
    // Создать строку запроса.
    // Вместо подготовки запроса и передачи параметров значение параметра
    // конкатенируется со строкой запроса
    // Обратите,что строковое значение помещается в одинарные кавычки
    // Значение выбирается из компонента таблицы методом item(row,col)
    QString sqlstr = "delete from housings where id_housing = '"
                     + ui->twData->item(currow,0)->text() + "'";
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
    selectAll();
}

void MainWindow::edit()
{
    // Connect to database
    if (!dbconn.isOpen())
    {
        dbconnect();
        if (!dbconn.isOpen())
        {
            QMessageBox::critical(this, "Error", dbconn.lastError().text());
            return;
        }
    }

    // Get selected row
    int currow = ui->twData->currentRow();
    if (currow < 0)
    {
        QMessageBox::critical(this, "Error", "No row selected!");
        return;
    }

    // Get original ID (before potential edit)
    QString originalId = ui->twData->item(currow, 0)->text();

    // Ask for confirmation
    if (QMessageBox::question(this, "Confirm Edit",
                              "Вы хотите отредактировать эту строку данных?",
                              QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes)
    {
        return;
    }

    // Get new values from input fields
    QString newId = ui->leId->text().trimmed();
    QString newTitle = ui->teTitle->toPlainText().trimmed();
    QString newAddress = ui->leAddress->text().trimmed();

    // Validate inputs
    if (newId.isEmpty() || newTitle.isEmpty() || newAddress.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Все поля должны быть заполнены!");
        return;
    }

    // Check if ID is being changed to a value that already exists
    if (newId != originalId)
    {
        QSqlQuery checkQuery(dbconn);
        checkQuery.prepare("SELECT COUNT(*) FROM housings WHERE id_housing = ?");
        checkQuery.bindValue(0, newId);

        if (!checkQuery.exec() || !checkQuery.next())
        {
            QMessageBox::critical(this, "Error", "Failed to check ID uniqueness");
            return;
        }

        if (checkQuery.value(0).toInt() > 0)
        {
            QMessageBox::warning(this, "Warning", "This ID already exists!");
            return;
        }
    }

    // Start transaction
    dbconn.transaction();

    // Update the record
    QSqlQuery query(dbconn);
    query.prepare("UPDATE housings SET id_housing = ?, title = ?, address = ? WHERE id_housing = ?");
    query.bindValue(0, newId);
    query.bindValue(1, newTitle);
    query.bindValue(2, newAddress);
    query.bindValue(3, originalId);

    if (!query.exec())
    {
        dbconn.rollback();
        ui->teResult->append("Failed query: " + query.lastQuery());
        ui->teResult->append("Error: " + query.lastError().text());
        QMessageBox::critical(this, "Error", "Failed to update record");
        return;
    }

    // Commit transaction
    if (!dbconn.commit())
    {
        QMessageBox::critical(this, "Error", "Failed to commit changes");
        return;
    }

    ui->teResult->append(QString("Successfully updated record (ID: %1)").arg(newId));
    selectAll(); // Refresh the table

    // Clear input fields
    ui->leId->clear();
    ui->teTitle->clear();
    ui->leAddress->clear();
}


