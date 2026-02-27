/********************************************************************************
** Form generated from reading UI file 'sub_students.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUB_STUDENTS_H
#define UI_SUB_STUDENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sub_Students
{
public:

    void setupUi(QWidget *Sub_Students)
    {
        if (Sub_Students->objectName().isEmpty())
            Sub_Students->setObjectName("Sub_Students");
        Sub_Students->resize(842, 417);

        retranslateUi(Sub_Students);

        QMetaObject::connectSlotsByName(Sub_Students);
    } // setupUi

    void retranslateUi(QWidget *Sub_Students)
    {
        Sub_Students->setWindowTitle(QCoreApplication::translate("Sub_Students", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sub_Students: public Ui_Sub_Students {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUB_STUDENTS_H
