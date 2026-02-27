#ifndef FACULTIES_H
#define FACULTIES_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class faculties;
}

class faculties : public QMainWindow
{
    Q_OBJECT

public:
    explicit faculties(QWidget *parent = nullptr);
    ~faculties();

    void loadFaculties(QSqlDatabase &db);
    QSqlDatabase dbconn;

private slots:
    void dbconnect();
    void selectAll();
    void add();
    void del();
    void edit();

private:
    Ui::faculties *ui;
};

#endif // FACULTIES_H
