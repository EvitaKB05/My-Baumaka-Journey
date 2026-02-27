#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Детская школа искусств");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnEnter_clicked()
{
    //this->close();
    LoginWindow *loginWindow = new LoginWindow(this);
    loginWindow->setAttribute(Qt::WA_DeleteOnClose);
    loginWindow->show();
}

void MainWindow::on_btnExit_clicked()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText("Вы действительно хотите выйти?");
    msgBox.setIcon(QMessageBox::Question);


    QPushButton *btnYes = msgBox.addButton("Да", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.exec();

    if (msgBox.clickedButton() == btnYes) {
        close();
    }
}
