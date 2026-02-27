/********************************************************************************
** Form generated from reading UI file 'marks.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKS_H
#define UI_MARKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
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

class Ui_Marks
{
public:
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QDateEdit *de_date_m;
    QComboBox *cb_mark;
    QLabel *lb_subject;
    QPushButton *btnEditRow;
    QPushButton *btnDelete;
    QLabel *lb_mark;
    QComboBox *cb_mark_type;
    QComboBox *cb_id_subject;
    QLabel *lb_student;
    QLabel *lb_mark_type;
    QPushButton *btnAddNew;
    QLabel *lb_teacher;
    QComboBox *cb_id_student;
    QLabel *lb_schedule;
    QLineEdit *le_id_mark;
    QLabel *lb_date_m;
    QPushButton *btnSave;
    QComboBox *cb_id_teacher;
    QLabel *lb_id_mark;
    QSpacerItem *verticalSpacer_3;
    QComboBox *cb_id_schedule;
    QPushButton *btnPrevious;
    QPushButton *btn_to_Teachers;
    QPushButton *btnHome;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QLabel *lb_search_mark;
    QLineEdit *le_search_mark;
    QPushButton *btn_Marks_by_Stud;
    QTableWidget *twData_mark;
    QPushButton *btnMarks_by_Fac;
    QPushButton *btn_Avg_Marks_by_All_Facs;
    QPushButton *btn_Marks_by_Teach;

    void setupUi(QWidget *Marks)
    {
        if (Marks->objectName().isEmpty())
            Marks->setObjectName("Marks");
        Marks->resize(1384, 470);
        frame = new QFrame(Marks);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 60, 451, 381));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName("gridLayout_2");
        de_date_m = new QDateEdit(frame);
        de_date_m->setObjectName("de_date_m");

        gridLayout_2->addWidget(de_date_m, 7, 2, 1, 4);

        cb_mark = new QComboBox(frame);
        cb_mark->setObjectName("cb_mark");
        cb_mark->setEditable(true);

        gridLayout_2->addWidget(cb_mark, 5, 2, 1, 4);

        lb_subject = new QLabel(frame);
        lb_subject->setObjectName("lb_subject");

        gridLayout_2->addWidget(lb_subject, 2, 0, 1, 2);

        btnEditRow = new QPushButton(frame);
        btnEditRow->setObjectName("btnEditRow");

        gridLayout_2->addWidget(btnEditRow, 12, 2, 1, 1);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName("btnDelete");

        gridLayout_2->addWidget(btnDelete, 12, 3, 1, 1);

        lb_mark = new QLabel(frame);
        lb_mark->setObjectName("lb_mark");

        gridLayout_2->addWidget(lb_mark, 5, 0, 1, 1);

        cb_mark_type = new QComboBox(frame);
        cb_mark_type->setObjectName("cb_mark_type");
        cb_mark_type->setEditable(true);

        gridLayout_2->addWidget(cb_mark_type, 1, 2, 1, 4);

        cb_id_subject = new QComboBox(frame);
        cb_id_subject->setObjectName("cb_id_subject");
        cb_id_subject->setEditable(true);

        gridLayout_2->addWidget(cb_id_subject, 2, 2, 1, 4);

        lb_student = new QLabel(frame);
        lb_student->setObjectName("lb_student");

        gridLayout_2->addWidget(lb_student, 4, 0, 1, 1);

        lb_mark_type = new QLabel(frame);
        lb_mark_type->setObjectName("lb_mark_type");

        gridLayout_2->addWidget(lb_mark_type, 1, 0, 1, 1);

        btnAddNew = new QPushButton(frame);
        btnAddNew->setObjectName("btnAddNew");

        gridLayout_2->addWidget(btnAddNew, 12, 1, 1, 1);

        lb_teacher = new QLabel(frame);
        lb_teacher->setObjectName("lb_teacher");

        gridLayout_2->addWidget(lb_teacher, 6, 0, 1, 2);

        cb_id_student = new QComboBox(frame);
        cb_id_student->setObjectName("cb_id_student");
        cb_id_student->setEditable(true);

        gridLayout_2->addWidget(cb_id_student, 4, 2, 1, 4);

        lb_schedule = new QLabel(frame);
        lb_schedule->setObjectName("lb_schedule");

        gridLayout_2->addWidget(lb_schedule, 8, 0, 1, 2);

        le_id_mark = new QLineEdit(frame);
        le_id_mark->setObjectName("le_id_mark");

        gridLayout_2->addWidget(le_id_mark, 0, 2, 1, 4);

        lb_date_m = new QLabel(frame);
        lb_date_m->setObjectName("lb_date_m");

        gridLayout_2->addWidget(lb_date_m, 7, 0, 1, 1);

        btnSave = new QPushButton(frame);
        btnSave->setObjectName("btnSave");

        gridLayout_2->addWidget(btnSave, 12, 0, 1, 1);

        cb_id_teacher = new QComboBox(frame);
        cb_id_teacher->setObjectName("cb_id_teacher");
        cb_id_teacher->setEditable(true);

        gridLayout_2->addWidget(cb_id_teacher, 6, 2, 1, 4);

        lb_id_mark = new QLabel(frame);
        lb_id_mark->setObjectName("lb_id_mark");

        gridLayout_2->addWidget(lb_id_mark, 0, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 9, 4, 1, 1);

        cb_id_schedule = new QComboBox(frame);
        cb_id_schedule->setObjectName("cb_id_schedule");
        cb_id_schedule->setEditable(true);

        gridLayout_2->addWidget(cb_id_schedule, 8, 2, 1, 4);

        btnPrevious = new QPushButton(frame);
        btnPrevious->setObjectName("btnPrevious");

        gridLayout_2->addWidget(btnPrevious, 11, 0, 1, 1);

        btn_to_Teachers = new QPushButton(frame);
        btn_to_Teachers->setObjectName("btn_to_Teachers");

        gridLayout_2->addWidget(btn_to_Teachers, 11, 1, 1, 2);

        btnHome = new QPushButton(frame);
        btnHome->setObjectName("btnHome");

        gridLayout_2->addWidget(btnHome, 11, 3, 1, 1);

        btnNext = new QPushButton(frame);
        btnNext->setObjectName("btnNext");

        gridLayout_2->addWidget(btnNext, 11, 4, 1, 1);

        btnLast = new QPushButton(frame);
        btnLast->setObjectName("btnLast");

        gridLayout_2->addWidget(btnLast, 11, 5, 1, 1);

        lb_search_mark = new QLabel(Marks);
        lb_search_mark->setObjectName("lb_search_mark");
        lb_search_mark->setGeometry(QRect(20, 10, 191, 31));
        le_search_mark = new QLineEdit(Marks);
        le_search_mark->setObjectName("le_search_mark");
        le_search_mark->setGeometry(QRect(220, 20, 321, 24));
        btn_Marks_by_Stud = new QPushButton(Marks);
        btn_Marks_by_Stud->setObjectName("btn_Marks_by_Stud");
        btn_Marks_by_Stud->setGeometry(QRect(550, 20, 141, 24));
        twData_mark = new QTableWidget(Marks);
        twData_mark->setObjectName("twData_mark");
        twData_mark->setGeometry(QRect(470, 60, 901, 381));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twData_mark->sizePolicy().hasHeightForWidth());
        twData_mark->setSizePolicy(sizePolicy1);
        twData_mark->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        twData_mark->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        twData_mark->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        twData_mark->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_mark->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_mark->horizontalHeader()->setStretchLastSection(true);
        btnMarks_by_Fac = new QPushButton(Marks);
        btnMarks_by_Fac->setObjectName("btnMarks_by_Fac");
        btnMarks_by_Fac->setGeometry(QRect(700, 20, 151, 24));
        btn_Avg_Marks_by_All_Facs = new QPushButton(Marks);
        btn_Avg_Marks_by_All_Facs->setObjectName("btn_Avg_Marks_by_All_Facs");
        btn_Avg_Marks_by_All_Facs->setGeometry(QRect(1030, 20, 181, 24));
        btn_Marks_by_Teach = new QPushButton(Marks);
        btn_Marks_by_Teach->setObjectName("btn_Marks_by_Teach");
        btn_Marks_by_Teach->setGeometry(QRect(860, 20, 161, 24));

        retranslateUi(Marks);

        QMetaObject::connectSlotsByName(Marks);
    } // setupUi

    void retranslateUi(QWidget *Marks)
    {
        Marks->setWindowTitle(QCoreApplication::translate("Marks", "\320\236\321\206\320\265\320\275\320\272\320\270", nullptr));
        lb_subject->setText(QCoreApplication::translate("Marks", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202", nullptr));
        btnEditRow->setText(QCoreApplication::translate("Marks", "\342\234\217\357\270\217", nullptr));
        btnDelete->setText(QCoreApplication::translate("Marks", "\342\235\214", nullptr));
        lb_mark->setText(QCoreApplication::translate("Marks", "\320\236\321\206\320\265\320\275\320\272\320\260", nullptr));
        lb_student->setText(QCoreApplication::translate("Marks", "\320\241\321\202\321\203\320\264\320\265\320\275\321\202", nullptr));
        lb_mark_type->setText(QCoreApplication::translate("Marks", "\320\242\320\270\320\277 \320\276\321\206\320\265\320\275\320\272\320\270", nullptr));
        btnAddNew->setText(QCoreApplication::translate("Marks", "\342\236\225", nullptr));
        lb_teacher->setText(QCoreApplication::translate("Marks", "\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
        lb_schedule->setText(QCoreApplication::translate("Marks", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\320\265 (\320\264\320\265\320\275\321\214)", nullptr));
        lb_date_m->setText(QCoreApplication::translate("Marks", "\320\224\320\260\321\202\320\260", nullptr));
        btnSave->setText(QCoreApplication::translate("Marks", "\342\234\205", nullptr));
        lb_id_mark->setText(QCoreApplication::translate("Marks", "ID \320\236\321\206\320\265\320\275\320\272\320\270", nullptr));
        btnPrevious->setText(QCoreApplication::translate("Marks", "\360\237\241\270", nullptr));
        btn_to_Teachers->setText(QCoreApplication::translate("Marks", "\320\232 \320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\217\320\274", nullptr));
        btnHome->setText(QCoreApplication::translate("Marks", "\360\237\217\240", nullptr));
        btnNext->setText(QCoreApplication::translate("Marks", "\360\237\241\272", nullptr));
        btnLast->setText(QCoreApplication::translate("Marks", "\342\207\266", nullptr));
        lb_search_mark->setText(QCoreApplication::translate("Marks", "\320\237\320\276\320\270\321\201\320\272 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\321\203/\320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\216", nullptr));
        btn_Marks_by_Stud->setText(QCoreApplication::translate("Marks", "\320\236\321\206\320\265\320\275\320\272\320\270 \320\277\320\276 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\321\203", nullptr));
        btnMarks_by_Fac->setText(QCoreApplication::translate("Marks", "\320\236\321\206\320\265\320\275\320\272\320\270 \320\277\320\276 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\216", nullptr));
        btn_Avg_Marks_by_All_Facs->setText(QCoreApplication::translate("Marks", "\320\241\321\200\320\265\320\264\320\275\320\270\320\265 \320\276\321\206\320\265\320\275\320\272\320\270 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\271", nullptr));
        btn_Marks_by_Teach->setText(QCoreApplication::translate("Marks", "\320\236\321\206\320\265\320\275\320\272\320\270 \320\277\320\276 \320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Marks: public Ui_Marks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKS_H
