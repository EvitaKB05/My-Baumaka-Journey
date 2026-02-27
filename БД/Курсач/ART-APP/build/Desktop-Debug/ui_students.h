/********************************************************************************
** Form generated from reading UI file 'students.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTS_H
#define UI_STUDENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Students
{
public:
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QPushButton *btnNext;
    QLineEdit *le_contacts_st;
    QLineEdit *le_id_st;
    QLabel *lb_fio_st;
    QSpacerItem *verticalSpacer_3;
    QLabel *lb_contacts_st;
    QLabel *lb_id_st;
    QComboBox *cb_id_faculty;
    QLabel *lb_faculty;
    QPushButton *btnPrevious;
    QComboBox *cb_fio_st;
    QPushButton *btnSave;
    QPushButton *btnAddNew;
    QPushButton *btnEditRow;
    QPushButton *btnLast;
    QPushButton *btnDelete;
    QPushButton *btn_to_marks;
    QPushButton *btnHome;
    QLabel *lb_search_st;
    QLineEdit *le_search_st;
    QPushButton *btnStud_by_Fac;
    QTableWidget *twData_st;
    QPushButton *btn_All_Studs_by_All_Facs;

    void setupUi(QWidget *Students)
    {
        if (Students->objectName().isEmpty())
            Students->setObjectName("Students");
        Students->resize(1206, 470);
        frame = new QFrame(Students);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 60, 451, 331));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName("gridLayout_2");
        btnNext = new QPushButton(frame);
        btnNext->setObjectName("btnNext");

        gridLayout_2->addWidget(btnNext, 5, 4, 1, 1);

        le_contacts_st = new QLineEdit(frame);
        le_contacts_st->setObjectName("le_contacts_st");

        gridLayout_2->addWidget(le_contacts_st, 2, 2, 1, 7);

        le_id_st = new QLineEdit(frame);
        le_id_st->setObjectName("le_id_st");

        gridLayout_2->addWidget(le_id_st, 0, 2, 1, 7);

        lb_fio_st = new QLabel(frame);
        lb_fio_st->setObjectName("lb_fio_st");

        gridLayout_2->addWidget(lb_fio_st, 1, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 4, 4, 1, 1);

        lb_contacts_st = new QLabel(frame);
        lb_contacts_st->setObjectName("lb_contacts_st");

        gridLayout_2->addWidget(lb_contacts_st, 2, 0, 1, 2);

        lb_id_st = new QLabel(frame);
        lb_id_st->setObjectName("lb_id_st");

        gridLayout_2->addWidget(lb_id_st, 0, 0, 1, 2);

        cb_id_faculty = new QComboBox(frame);
        cb_id_faculty->setObjectName("cb_id_faculty");
        cb_id_faculty->setEditable(true);

        gridLayout_2->addWidget(cb_id_faculty, 3, 2, 1, 7);

        lb_faculty = new QLabel(frame);
        lb_faculty->setObjectName("lb_faculty");

        gridLayout_2->addWidget(lb_faculty, 3, 0, 1, 2);

        btnPrevious = new QPushButton(frame);
        btnPrevious->setObjectName("btnPrevious");

        gridLayout_2->addWidget(btnPrevious, 5, 0, 1, 1);

        cb_fio_st = new QComboBox(frame);
        cb_fio_st->setObjectName("cb_fio_st");
        cb_fio_st->setEditable(true);

        gridLayout_2->addWidget(cb_fio_st, 1, 2, 1, 7);

        btnSave = new QPushButton(frame);
        btnSave->setObjectName("btnSave");

        gridLayout_2->addWidget(btnSave, 6, 0, 1, 1);

        btnAddNew = new QPushButton(frame);
        btnAddNew->setObjectName("btnAddNew");

        gridLayout_2->addWidget(btnAddNew, 6, 2, 1, 1);

        btnEditRow = new QPushButton(frame);
        btnEditRow->setObjectName("btnEditRow");

        gridLayout_2->addWidget(btnEditRow, 6, 3, 1, 1);

        btnLast = new QPushButton(frame);
        btnLast->setObjectName("btnLast");

        gridLayout_2->addWidget(btnLast, 5, 6, 1, 1);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName("btnDelete");

        gridLayout_2->addWidget(btnDelete, 6, 4, 1, 1);

        btn_to_marks = new QPushButton(frame);
        btn_to_marks->setObjectName("btn_to_marks");

        gridLayout_2->addWidget(btn_to_marks, 5, 2, 1, 1);

        btnHome = new QPushButton(frame);
        btnHome->setObjectName("btnHome");

        gridLayout_2->addWidget(btnHome, 5, 3, 1, 1);

        lb_search_st = new QLabel(Students);
        lb_search_st->setObjectName("lb_search_st");
        lb_search_st->setGeometry(QRect(10, 20, 181, 24));
        le_search_st = new QLineEdit(Students);
        le_search_st->setObjectName("le_search_st");
        le_search_st->setGeometry(QRect(200, 20, 321, 24));
        btnStud_by_Fac = new QPushButton(Students);
        btnStud_by_Fac->setObjectName("btnStud_by_Fac");
        btnStud_by_Fac->setGeometry(QRect(550, 20, 161, 24));
        twData_st = new QTableWidget(Students);
        twData_st->setObjectName("twData_st");
        twData_st->setGeometry(QRect(470, 60, 721, 331));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twData_st->sizePolicy().hasHeightForWidth());
        twData_st->setSizePolicy(sizePolicy1);
        twData_st->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        twData_st->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        twData_st->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        twData_st->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_st->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_st->horizontalHeader()->setStretchLastSection(true);
        btn_All_Studs_by_All_Facs = new QPushButton(Students);
        btn_All_Studs_by_All_Facs->setObjectName("btn_All_Studs_by_All_Facs");
        btn_All_Studs_by_All_Facs->setGeometry(QRect(750, 20, 181, 24));

        retranslateUi(Students);

        QMetaObject::connectSlotsByName(Students);
    } // setupUi

    void retranslateUi(QWidget *Students)
    {
        Students->setWindowTitle(QCoreApplication::translate("Students", "\320\241\321\202\321\203\320\264\320\265\320\275\321\202\321\213", nullptr));
        btnNext->setText(QCoreApplication::translate("Students", "\360\237\241\272", nullptr));
        lb_fio_st->setText(QCoreApplication::translate("Students", "\320\244\320\230\320\236", nullptr));
        lb_contacts_st->setText(QCoreApplication::translate("Students", "\320\232\320\276\320\275\321\202\320\260\320\272\321\202\321\213", nullptr));
        lb_id_st->setText(QCoreApplication::translate("Students", "ID \320\241\321\202\321\203\320\264\320\265\320\275\321\202\320\260", nullptr));
        lb_faculty->setText(QCoreApplication::translate("Students", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        btnPrevious->setText(QCoreApplication::translate("Students", "\360\237\241\270", nullptr));
        btnSave->setText(QCoreApplication::translate("Students", "\342\234\205", nullptr));
        btnAddNew->setText(QCoreApplication::translate("Students", "\342\236\225", nullptr));
        btnEditRow->setText(QCoreApplication::translate("Students", "\342\234\217\357\270\217", nullptr));
        btnLast->setText(QCoreApplication::translate("Students", "\342\207\266", nullptr));
        btnDelete->setText(QCoreApplication::translate("Students", "\342\235\214", nullptr));
        btn_to_marks->setText(QCoreApplication::translate("Students", "\320\232 \320\276\321\206\320\265\320\275\320\272\320\260\320\274", nullptr));
        btnHome->setText(QCoreApplication::translate("Students", "\360\237\217\240", nullptr));
        lb_search_st->setText(QCoreApplication::translate("Students", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \320\244\320\230\320\236/\320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\216:", nullptr));
        btnStud_by_Fac->setText(QCoreApplication::translate("Students", "\320\241\321\202\321\203\320\264\320\265\320\275\321\202\321\213 \320\277\320\276 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\216", nullptr));
        btn_All_Studs_by_All_Facs->setText(QCoreApplication::translate("Students", "\320\241\321\202\321\203\320\264\320\265\320\275\321\202\321\213 \320\262\321\201\320\265\321\205 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Students: public Ui_Students {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTS_H
