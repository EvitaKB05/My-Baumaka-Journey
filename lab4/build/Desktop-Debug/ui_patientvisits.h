/********************************************************************************
** Form generated from reading UI file 'patientvisits.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTVISITS_H
#define UI_PATIENTVISITS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_patientvisits
{
public:
    QWidget *centralwidget;
    QTableWidget *twVisits;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *patientvisits)
    {
        if (patientvisits->objectName().isEmpty())
            patientvisits->setObjectName("patientvisits");
        patientvisits->resize(800, 600);
        centralwidget = new QWidget(patientvisits);
        centralwidget->setObjectName("centralwidget");
        twVisits = new QTableWidget(centralwidget);
        twVisits->setObjectName("twVisits");
        twVisits->setGeometry(QRect(20, 30, 721, 501));
        patientvisits->setCentralWidget(centralwidget);
        menubar = new QMenuBar(patientvisits);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        patientvisits->setMenuBar(menubar);
        statusbar = new QStatusBar(patientvisits);
        statusbar->setObjectName("statusbar");
        patientvisits->setStatusBar(statusbar);

        retranslateUi(patientvisits);

        QMetaObject::connectSlotsByName(patientvisits);
    } // setupUi

    void retranslateUi(QMainWindow *patientvisits)
    {
        patientvisits->setWindowTitle(QCoreApplication::translate("patientvisits", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class patientvisits: public Ui_patientvisits {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTVISITS_H
