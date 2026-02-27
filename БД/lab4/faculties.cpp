#include "mainwindow.h"
#include "faculties.h"
#include "ui_mainwindow.h"
#include "ui_faculties.h"

faculties::faculties(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::faculties)
{
    ui->setupUi(this);
    connect(ui->btnConnect,SIGNAL(clicked(bool)),this, SLOT(dbconnect()));
    connect(ui->btnSelectAll, SIGNAL(clicked(bool)), this, SLOT(selectAll()));
    connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->btnDel, SIGNAL(clicked(bool)), this, SLOT(del()));
    connect(ui->btnEdit, SIGNAL(clicked(bool)), this, SLOT(edit()));

    // Set column count for faculties
    ui->twData->setColumnCount(3);
    ui->twData->setAutoScroll(true);
    ui->twData->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twData->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Set headers for faculties table
    ui->twData->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->twData->setHorizontalHeaderItem(1,new QTableWidgetItem("Title"));
    ui->twData->setHorizontalHeaderItem(2,new QTableWidgetItem("Housing ID"));

    ui->twData->horizontalHeader()->setStretchLastSection(true);
    ui->twData->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

faculties::~faculties()
{
    if(dbconn.isOpen())
        dbconn.close();
    delete ui;
}

void faculties::dbconnect()
{
    if(!dbconn.isOpen())
    {
        ui->teResult->append("SQL drivers:");
        ui->teResult->append(QSqlDatabase::drivers().join(","));
        dbconn=QSqlDatabase::addDatabase("QPSQL");
        dbconn.setDatabaseName("dbtest");
        dbconn.setHostName("localhost");
        dbconn.setPort(5432);
        dbconn.setUserName("postgres");
        dbconn.setPassword("mrduckword532854");

        if(dbconn.open())
            ui->teResult->append("Connect is open...");
        else
        {
            ui->teResult->append("Error of connect:");
            ui->teResult->append(dbconn.lastError().text());
        }
    }
    else
        ui->teResult->append("Connect is already open...");
}

void faculties::selectAll()
{
    ui->twData->clearContents();

    if(!dbconn.isOpen())
    {
        dbconnect();
        if(!dbconn.isOpen())
        {
            QMessageBox::critical(this,"Error",dbconn.lastError().text());
            return;
        }
    }

    QSqlQuery query(dbconn);
    QString sqlstr = "SELECT * FROM faculties ORDER BY id_faculty";
    bool query_success = query.exec(sqlstr);

    if(query_success)
        ui->twData->setRowCount(query.size());
    else
        ui->twData->setRowCount(0);

    ui->teResult->append(QString("Read %1 rows").arg(query.size()));

    int i=0;
    while(query.next())
    {
        ui->twData->setItem(i,0,new QTableWidgetItem(query.value("id_faculty").toString()));
        ui->twData->setItem(i,1,new QTableWidgetItem(query.value("title").toString()));
        ui->twData->setItem(i,2,new QTableWidgetItem(query.value("id_housing").toString()));
        i++;
    }
}

void faculties::add()
{
    if(!dbconn.isOpen())
    {
        dbconnect();
        if(!dbconn.isOpen())
        {
            QMessageBox::critical(this,"Error",dbconn.lastError().text());
            return;
        }
    }

    // Get next ID
    QSqlQuery maxIdQuery(dbconn);
    if(!maxIdQuery.exec("SELECT MAX(id_faculty) FROM faculties"))
    {
        QMessageBox::critical(this,"Error",maxIdQuery.lastError().text());
        return;
    }

    int nextId = 1;
    if(maxIdQuery.next())
    {
        nextId = maxIdQuery.value(0).toInt() + 1;
    }

    QSqlQuery query(dbconn);
    QString sqlstr = "INSERT INTO faculties(id_faculty, title, id_housing) VALUES(?, ?, ?)";
    query.prepare(sqlstr);

    QString title = ui->teTitle->toPlainText().trimmed();
    QString housingId = ui->leHousingId->text().trimmed();

    if(title.isEmpty())
    {
        title = "New Faculty " + QString::number(nextId);
    }
    if(housingId.isEmpty())
    {
        // Default to housing ID 1 if not specified
        housingId = "1";
    }

    // Validate housing ID exists
    QSqlQuery housingCheck(dbconn);
    housingCheck.prepare("SELECT COUNT(*) FROM housings WHERE id_housing = ?");
    housingCheck.bindValue(0, housingId.toInt());
    if(!housingCheck.exec() || !housingCheck.next() || housingCheck.value(0).toInt() == 0)
    {
        QMessageBox::warning(this, "Warning", "Invalid housing ID specified");
        return;
    }

    query.bindValue(0, nextId);
    query.bindValue(1, title);
    query.bindValue(2, housingId.toInt());

    if(!query.exec())
    {
        ui->teResult->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }

    ui->teTitle->clear();
    ui->leHousingId->clear();

    ui->teResult->append(QString("Added new faculty (ID: %1, Title: %2, Housing ID: %3)")
                             .arg(nextId)
                             .arg(title)
                             .arg(housingId));
    selectAll();
}

void faculties::del()
{
    if(!dbconn.isOpen())
    {
        dbconnect();
        if(!dbconn.isOpen())
        {
            QMessageBox::critical(this,"Error",dbconn.lastError().text());
            return;
        }
    }

    int currow = ui->twData->currentRow();
    if(currow < 0)
    {
        QMessageBox::critical(this,"Error","Not selected row!");
        return;
    }

    if(QMessageBox::question(this,"Delete","Delete row?",
                              QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Cancel)
        return;

    QSqlQuery query(dbconn);
    QString sqlstr = "DELETE FROM faculties WHERE id_faculty = '"
                     + ui->twData->item(currow,0)->text() + "'";

    if(!query.exec(sqlstr))
    {
        ui->teResult->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }

    ui->teResult->append(QString("Deleted %1 rows").arg(query.numRowsAffected()));
    selectAll();
}

void faculties::edit()
{
    if(!dbconn.isOpen())
    {
        dbconnect();
        if(!dbconn.isOpen())
        {
            QMessageBox::critical(this,"Error",dbconn.lastError().text());
            return;
        }
    }

    int currow = ui->twData->currentRow();
    if(currow < 0)
    {
        QMessageBox::critical(this,"Error","No row selected!");
        return;
    }

    QString originalId = ui->twData->item(currow,0)->text();

    if(QMessageBox::question(this,"Confirm Edit",
                              "Are you sure you want to edit this record?",
                              QMessageBox::Yes|QMessageBox::No) != QMessageBox::Yes)
    {
        return;
    }

    QString newId = ui->leId->text().trimmed();
    QString newTitle = ui->teTitle->toPlainText().trimmed();
    QString newHousingId = ui->leHousingId->text().trimmed();

    if(newId.isEmpty() || newTitle.isEmpty() || newHousingId.isEmpty())
    {
        QMessageBox::warning(this,"Warning","All fields must be filled!");
        return;
    }

    // Check if ID is being changed to a value that already exists
    if(newId != originalId)
    {
        QSqlQuery checkQuery(dbconn);
        checkQuery.prepare("SELECT COUNT(*) FROM faculties WHERE id_faculty = ?");
        checkQuery.bindValue(0, newId);

        if(!checkQuery.exec() || !checkQuery.next())
        {
            QMessageBox::critical(this,"Error","Failed to check ID uniqueness");
            return;
        }

        if(checkQuery.value(0).toInt() > 0)
        {
            QMessageBox::warning(this,"Warning","This ID already exists!");
            return;
        }
    }

    // Validate housing ID exists
    QSqlQuery housingCheck(dbconn);
    housingCheck.prepare("SELECT COUNT(*) FROM housings WHERE id_housing = ?");
    housingCheck.bindValue(0, newHousingId.toInt());
    if(!housingCheck.exec() || !housingCheck.next() || housingCheck.value(0).toInt() == 0)
    {
        QMessageBox::warning(this, "Warning", "Invalid housing ID specified");
        return;
    }

    dbconn.transaction();

    QSqlQuery query(dbconn);
    query.prepare("UPDATE faculties SET id_faculty = ?, title = ?, id_housing = ? WHERE id_faculty = ?");
    query.bindValue(0, newId);
    query.bindValue(1, newTitle);
    query.bindValue(2, newHousingId.toInt());
    query.bindValue(3, originalId);

    if(!query.exec())
    {
        dbconn.rollback();
        ui->teResult->append("Failed query: " + query.lastQuery());
        ui->teResult->append("Error: " + query.lastError().text());
        QMessageBox::critical(this,"Error","Failed to update record");
        return;
    }

    if(!dbconn.commit())
    {
        QMessageBox::critical(this,"Error","Failed to commit changes");
        return;
    }

    ui->teResult->append(QString("Successfully updated record (ID: %1)").arg(newId));
    selectAll();

    ui->leId->clear();
    ui->teTitle->clear();
    ui->leHousingId->clear();
}
