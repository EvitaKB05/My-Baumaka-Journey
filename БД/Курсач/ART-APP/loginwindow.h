#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "globals.h"
#pragma once
#include <QMainWindow>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_btnLogin_clicked();
    void on_btnCancel_clicked();

private:
    Ui::LoginWindow *ui;
    void setupWindow();
};

#endif // LOGINWINDOW_H
