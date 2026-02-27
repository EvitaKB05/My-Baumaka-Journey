#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include "ui_menuwindow.h"
#include "globals.h"
#pragma once
namespace Ui {
class MenuWindow;
}

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_btnHousings_clicked();
    void on_btnFaculties_clicked();
    void on_btnStudents_clicked();
    void on_btnMarks_clicked();
    void on_btnTeachers_clicked();
    void on_btnSchedules_clicked();
    void on_btnSubjects_clicked();
    void on_btnExit_clicked();

private:
    Ui::MenuWindow *ui;
};

#endif // MENUWINDOW_H
