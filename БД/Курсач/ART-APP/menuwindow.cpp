#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "housings.h"
#include "mainwindow.h"
#include "faculties.h"
#include "students.h"
#include "teachers.h"
#include "subjects.h"
#include "schedules.h"
#include "marks.h"


MenuWindow::MenuWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    setWindowTitle("Меню - Детская школа искусств");
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_btnHousings_clicked()
{
    Housings *housingsWindow = new Housings(this);
    housingsWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(housingsWindow, &Housings::returnToMainMenu, this, &MenuWindow::show);
    this->hide();
    housingsWindow->show();
}

void MenuWindow::on_btnFaculties_clicked()
{
    Faculties *facultiesWindow = new Faculties(this);
    facultiesWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(facultiesWindow, &Faculties::returnToMainMenu, this, &MenuWindow::show);
    this->hide();
    facultiesWindow->show();
}

void MenuWindow::on_btnStudents_clicked()
{
    Students *studentsWindow = new Students(this);
    studentsWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(studentsWindow, &Students::returnToMainMenu, this, &MenuWindow::show);
    this->hide();
    studentsWindow->show();
}

void MenuWindow::on_btnMarks_clicked()
{
    Marks *marksWindow = new Marks(this);
    marksWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(marksWindow, &Marks::returnToMainMenu, this, &MenuWindow::show);
    this->hide();
    marksWindow->show();
}

void MenuWindow::on_btnTeachers_clicked()
{
    Teachers *teachersWindow = new Teachers(this);
    teachersWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(teachersWindow, &Teachers::returnToMainMenu, this, &MenuWindow::show);
    this->hide();
    teachersWindow->show();
}

void MenuWindow::on_btnSchedules_clicked()
{
    Schedules *schedulesWindow = new Schedules(this);
    schedulesWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(schedulesWindow, &Schedules::returnToMainMenu, this, &MenuWindow::show);
    this->hide();
    schedulesWindow->show();
}

void MenuWindow::on_btnSubjects_clicked()
{
    Subjects *subjectsWindow = new Subjects(this);
    subjectsWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(subjectsWindow, &Subjects::returnToMainMenu, this, &MenuWindow::show);
    this->hide();
    subjectsWindow->show();
}
void MenuWindow::on_btnExit_clicked()
{
    this->close();

    // Создаем и показываем окно входа
    MainWindow *mainWindow = new MainWindow();
    mainWindow->setAttribute(Qt::WA_DeleteOnClose); // Автоматическое удаление после закрытия
    mainWindow->show(); // Показываем окно входа
}
