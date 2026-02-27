/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnEnter;
    QLabel *lblTitle;
    QLabel *lblGreeting;
    QPushButton *btnExit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        btnEnter = new QPushButton(centralwidget);
        btnEnter->setObjectName("btnEnter");
        btnEnter->setGeometry(QRect(190, 250, 151, 51));
        lblTitle = new QLabel(centralwidget);
        lblTitle->setObjectName("lblTitle");
        lblTitle->setGeometry(QRect(200, 10, 371, 70));
        lblTitle->setStyleSheet(QString::fromUtf8("font-size: 20pt;"));
        lblTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lblGreeting = new QLabel(centralwidget);
        lblGreeting->setObjectName("lblGreeting");
        lblGreeting->setGeometry(QRect(140, 120, 521, 91));
        lblGreeting->setStyleSheet(QString::fromUtf8("font-size: 14pt;"));
        lblGreeting->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btnExit = new QPushButton(centralwidget);
        btnExit->setObjectName("btnExit");
        btnExit->setGeometry(QRect(420, 250, 151, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\202\321\201\320\272\320\260\321\217 \321\210\320\272\320\276\320\273\320\260 \320\270\321\201\320\272\321\203\321\201\321\201\321\202\320\262", nullptr));
        btnEnter->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\271\321\202\320\270 \320\262 \321\201\320\270\321\201\321\202\320\265\320\274\321\203", nullptr));
        lblTitle->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\202\321\201\320\272\320\260\321\217 \321\210\320\272\320\276\320\273\320\260 \320\270\321\201\320\272\321\203\321\201\321\201\321\202\320\262", nullptr));
        lblGreeting->setText(QCoreApplication::translate("MainWindow", "\320\227\320\264\321\200\320\260\320\262\321\201\321\202\320\262\321\203\320\271\321\202\320\265!\n"
"\320\224\320\273\321\217 \320\264\320\260\320\273\321\214\320\275\320\265\320\271\321\210\320\265\320\263\320\276 \320\262\320\267\320\260\320\270\320\274\320\276\320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\217 - \320\262\320\276\320\271\320\264\320\270\321\202\320\265 \320\262 \321\201\320\270\321\201\321\202\320\265\320\274\321\203!", nullptr));
        btnExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
