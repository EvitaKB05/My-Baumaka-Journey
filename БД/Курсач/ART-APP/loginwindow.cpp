#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include "menuwindow.h"
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    setupWindow();
}

void LoginWindow::setupWindow()
{
    setWindowTitle("Авторизация");
    //setFixedSize(400, 350);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    ui->lePassword->setEchoMode(QLineEdit::Password);

    /*setStyleSheet(
        "QMainWindow { background: white; }"
        "QLabel { color: black; }"
        "QLineEdit, QComboBox {"
        "   background: white;"
        "   color: black;"
        "   border: 1px solid #ccc;"
        "   padding: 3px;"
        "}"
        );
    */
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnLogin_clicked()
{
    QString fullName = ui->leFullName->text().trimmed();
    QString role = ui->cbRole->currentText();
    QString password = ui->lePassword->text();

    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите ФИО!");
        return;
    }

    if (password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите пароль!");
        return;
    }

    // Удаляем локальное объявление currentUserRole и используем глобальную переменную
    if (ui->cbRole->currentText() == "Преподаватель") {
        currentUserRole = UserRole::Teacher;
    }
    else if (ui->cbRole->currentText() == "Студент") {
        currentUserRole = UserRole::Student;
    }
    else {
        currentUserRole = UserRole::Admin;
    }

    // Закрываем окно авторизации
    this->close();


    QMessageBox::information(this, "Успешный вход",
                             QString("Добро пожаловать, %1!\nВаша роль: %2").arg(fullName).arg(role));
    close();

    // Открываем главное меню
    MenuWindow *menuWindow = new MenuWindow();
    menuWindow->show();
}




void LoginWindow::on_btnCancel_clicked()
{
    close();
}
