#ifndef FACULTIES_H
#define FACULTIES_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QMessageBox>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class faculties; }
QT_END_NAMESPACE

class faculties : public QMainWindow
{
    Q_OBJECT

public:
    explicit faculties(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    ~faculties();

    void loadFaculties(const QString &housingId);
    void setHousingId(const QString &id);

private slots:
    void add();
    void del();
    void edit();
    void onFacultySelected(int row, int column);
    void refreshData();

private:
    Ui::faculties *ui;
    QSqlDatabase *dbconn;
    QString currentHousingId;

    // Вспомогательные методы
    bool validateFacultyId(const QString &id);
    bool validateHousingReference(const QString &housingId);
    void clearInputFields();
    void populateFieldsFromSelectedRow();
    void setupTable();
};

#endif // FACULTIES_H
