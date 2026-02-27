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
    explicit faculties(QWidget *parent, QSqlDatabase &db);
    ~faculties();
    void loadFaculties(const QString &ID);

// private slots:
//     void add();

//     void del();

//     void edit();

private:
    Ui::faculties *ui;
    QSqlDatabase dbconn;
};

#endif // FACULTIES_H
