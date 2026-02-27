/********************************************************************************
** Form generated from reading UI file 'menuwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWINDOW_H
#define UI_MENUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuWindow
{
public:
    QPushButton *btnFaculties;
    QPushButton *btnHousings;
    QPushButton *btnStudents;
    QPushButton *btnMarks;
    QPushButton *btnSchedules;
    QLabel *lblTitle_2;
    QPushButton *btnTeachers;
    QPushButton *btnSubjects;
    QLabel *lblTitle;
    QPushButton *btnExit;

    void setupUi(QWidget *MenuWindow)
    {
        if (MenuWindow->objectName().isEmpty())
            MenuWindow->setObjectName("MenuWindow");
        MenuWindow->resize(807, 459);
        btnFaculties = new QPushButton(MenuWindow);
        btnFaculties->setObjectName("btnFaculties");
        btnFaculties->setGeometry(QRect(130, 220, 121, 51));
        btnHousings = new QPushButton(MenuWindow);
        btnHousings->setObjectName("btnHousings");
        btnHousings->setGeometry(QRect(130, 140, 121, 51));
        btnStudents = new QPushButton(MenuWindow);
        btnStudents->setObjectName("btnStudents");
        btnStudents->setGeometry(QRect(510, 140, 121, 51));
        btnMarks = new QPushButton(MenuWindow);
        btnMarks->setObjectName("btnMarks");
        btnMarks->setGeometry(QRect(510, 220, 121, 51));
        btnSchedules = new QPushButton(MenuWindow);
        btnSchedules->setObjectName("btnSchedules");
        btnSchedules->setGeometry(QRect(130, 310, 121, 51));
        lblTitle_2 = new QLabel(MenuWindow);
        lblTitle_2->setObjectName("lblTitle_2");
        lblTitle_2->setGeometry(QRect(270, 60, 221, 70));
        lblTitle_2->setStyleSheet(QString::fromUtf8("font-size: 20pt;"));
        lblTitle_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btnTeachers = new QPushButton(MenuWindow);
        btnTeachers->setObjectName("btnTeachers");
        btnTeachers->setGeometry(QRect(510, 310, 121, 51));
        btnSubjects = new QPushButton(MenuWindow);
        btnSubjects->setObjectName("btnSubjects");
        btnSubjects->setGeometry(QRect(320, 220, 121, 51));
        lblTitle = new QLabel(MenuWindow);
        lblTitle->setObjectName("lblTitle");
        lblTitle->setGeometry(QRect(190, 10, 371, 70));
        lblTitle->setStyleSheet(QString::fromUtf8("font-size: 20pt;"));
        lblTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btnExit = new QPushButton(MenuWindow);
        btnExit->setObjectName("btnExit");
        btnExit->setGeometry(QRect(660, 10, 121, 51));

        retranslateUi(MenuWindow);

        QMetaObject::connectSlotsByName(MenuWindow);
    } // setupUi

    void retranslateUi(QWidget *MenuWindow)
    {
        MenuWindow->setWindowTitle(QCoreApplication::translate("MenuWindow", "Form", nullptr));
        btnFaculties->setText(QCoreApplication::translate("MenuWindow", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        btnHousings->setText(QCoreApplication::translate("MenuWindow", "\320\232\320\276\321\200\320\277\321\203\321\201\320\260", nullptr));
        btnStudents->setText(QCoreApplication::translate("MenuWindow", "\320\241\321\202\321\203\320\264\320\265\320\275\321\202\321\213", nullptr));
        btnMarks->setText(QCoreApplication::translate("MenuWindow", "\320\236\321\206\320\265\320\275\320\272\320\270", nullptr));
        btnSchedules->setText(QCoreApplication::translate("MenuWindow", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\321\217 \320\267\320\260\320\275\321\217\321\202\320\270\320\271", nullptr));
        lblTitle_2->setText(QCoreApplication::translate("MenuWindow", "\320\234\320\265\320\275\321\216", nullptr));
        btnTeachers->setText(QCoreApplication::translate("MenuWindow", "\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\320\270", nullptr));
        btnSubjects->setText(QCoreApplication::translate("MenuWindow", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202\321\213", nullptr));
        lblTitle->setText(QCoreApplication::translate("MenuWindow", "\320\224\320\265\321\202\321\201\320\272\320\260\321\217 \321\210\320\272\320\276\320\273\320\260 \320\270\321\201\320\272\321\203\321\201\321\201\321\202\320\262", nullptr));
        btnExit->setText(QCoreApplication::translate("MenuWindow", "\320\222\321\213\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuWindow: public Ui_MenuWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWINDOW_H
