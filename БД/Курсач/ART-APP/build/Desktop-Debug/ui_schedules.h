/********************************************************************************
** Form generated from reading UI file 'schedules.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULES_H
#define UI_SCHEDULES_H

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
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Schedules
{
public:
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QComboBox *cb_week_day;
    QPushButton *btnPrevious;
    QLabel *lb_id_teacher;
    QTimeEdit *time_edit_time;
    QPushButton *btnNext;
    QComboBox *cb_lesson_type;
    QPushButton *btnSave;
    QLabel *lb_lesson_type;
    QComboBox *cb_id_faculty;
    QLineEdit *le_id_sched;
    QComboBox *cb_id_teacher;
    QLabel *lb_id_sched;
    QLabel *lb_time;
    QSpacerItem *verticalSpacer_3;
    QComboBox *cb_id_subject;
    QLabel *lb_subject;
    QLabel *lb_id_housing;
    QComboBox *cb_id_housing;
    QPushButton *btnAddNew;
    QPushButton *btnEditRow;
    QPushButton *btnDelete;
    QPushButton *btn_to_Teachers;
    QPushButton *btnHome;
    QPushButton *btnLast;
    QLabel *lb_faculty;
    QLabel *lb_week_day;
    QLabel *lb_search_sched;
    QLineEdit *le_search_sched;
    QPushButton *btn_Sched_by_Fac;
    QTableWidget *twData_sched;
    QPushButton *btnSched_by_Teach;
    QPushButton *btn_All_Scheds;

    void setupUi(QWidget *Schedules)
    {
        if (Schedules->objectName().isEmpty())
            Schedules->setObjectName("Schedules");
        Schedules->resize(1260, 470);
        frame = new QFrame(Schedules);
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
        cb_week_day = new QComboBox(frame);
        cb_week_day->setObjectName("cb_week_day");
        cb_week_day->setEditable(true);

        gridLayout_2->addWidget(cb_week_day, 4, 2, 1, 4);

        btnPrevious = new QPushButton(frame);
        btnPrevious->setObjectName("btnPrevious");

        gridLayout_2->addWidget(btnPrevious, 10, 0, 1, 1);

        lb_id_teacher = new QLabel(frame);
        lb_id_teacher->setObjectName("lb_id_teacher");

        gridLayout_2->addWidget(lb_id_teacher, 7, 0, 1, 2);

        time_edit_time = new QTimeEdit(frame);
        time_edit_time->setObjectName("time_edit_time");

        gridLayout_2->addWidget(time_edit_time, 5, 2, 1, 4);

        btnNext = new QPushButton(frame);
        btnNext->setObjectName("btnNext");

        gridLayout_2->addWidget(btnNext, 10, 4, 1, 1);

        cb_lesson_type = new QComboBox(frame);
        cb_lesson_type->setObjectName("cb_lesson_type");
        cb_lesson_type->setEditable(true);

        gridLayout_2->addWidget(cb_lesson_type, 6, 2, 1, 4);

        btnSave = new QPushButton(frame);
        btnSave->setObjectName("btnSave");

        gridLayout_2->addWidget(btnSave, 11, 0, 1, 1);

        lb_lesson_type = new QLabel(frame);
        lb_lesson_type->setObjectName("lb_lesson_type");

        gridLayout_2->addWidget(lb_lesson_type, 6, 0, 1, 1);

        cb_id_faculty = new QComboBox(frame);
        cb_id_faculty->setObjectName("cb_id_faculty");
        cb_id_faculty->setEditable(true);

        gridLayout_2->addWidget(cb_id_faculty, 1, 2, 1, 4);

        le_id_sched = new QLineEdit(frame);
        le_id_sched->setObjectName("le_id_sched");

        gridLayout_2->addWidget(le_id_sched, 0, 2, 1, 4);

        cb_id_teacher = new QComboBox(frame);
        cb_id_teacher->setObjectName("cb_id_teacher");
        cb_id_teacher->setEditable(true);

        gridLayout_2->addWidget(cb_id_teacher, 7, 2, 1, 4);

        lb_id_sched = new QLabel(frame);
        lb_id_sched->setObjectName("lb_id_sched");

        gridLayout_2->addWidget(lb_id_sched, 0, 0, 1, 2);

        lb_time = new QLabel(frame);
        lb_time->setObjectName("lb_time");

        gridLayout_2->addWidget(lb_time, 5, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 9, 4, 1, 1);

        cb_id_subject = new QComboBox(frame);
        cb_id_subject->setObjectName("cb_id_subject");
        cb_id_subject->setEditable(true);

        gridLayout_2->addWidget(cb_id_subject, 2, 2, 1, 4);

        lb_subject = new QLabel(frame);
        lb_subject->setObjectName("lb_subject");

        gridLayout_2->addWidget(lb_subject, 2, 0, 1, 2);

        lb_id_housing = new QLabel(frame);
        lb_id_housing->setObjectName("lb_id_housing");

        gridLayout_2->addWidget(lb_id_housing, 8, 0, 1, 1);

        cb_id_housing = new QComboBox(frame);
        cb_id_housing->setObjectName("cb_id_housing");
        cb_id_housing->setEditable(true);

        gridLayout_2->addWidget(cb_id_housing, 8, 2, 1, 4);

        btnAddNew = new QPushButton(frame);
        btnAddNew->setObjectName("btnAddNew");

        gridLayout_2->addWidget(btnAddNew, 11, 1, 1, 1);

        btnEditRow = new QPushButton(frame);
        btnEditRow->setObjectName("btnEditRow");

        gridLayout_2->addWidget(btnEditRow, 11, 2, 1, 1);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName("btnDelete");

        gridLayout_2->addWidget(btnDelete, 11, 3, 1, 1);

        btn_to_Teachers = new QPushButton(frame);
        btn_to_Teachers->setObjectName("btn_to_Teachers");

        gridLayout_2->addWidget(btn_to_Teachers, 10, 1, 1, 2);

        btnHome = new QPushButton(frame);
        btnHome->setObjectName("btnHome");

        gridLayout_2->addWidget(btnHome, 10, 3, 1, 1);

        btnLast = new QPushButton(frame);
        btnLast->setObjectName("btnLast");

        gridLayout_2->addWidget(btnLast, 10, 5, 1, 1);

        lb_faculty = new QLabel(frame);
        lb_faculty->setObjectName("lb_faculty");

        gridLayout_2->addWidget(lb_faculty, 1, 0, 1, 2);

        lb_week_day = new QLabel(frame);
        lb_week_day->setObjectName("lb_week_day");

        gridLayout_2->addWidget(lb_week_day, 4, 0, 1, 2);

        lb_search_sched = new QLabel(Schedules);
        lb_search_sched->setObjectName("lb_search_sched");
        lb_search_sched->setGeometry(QRect(60, 0, 151, 51));
        le_search_sched = new QLineEdit(Schedules);
        le_search_sched->setObjectName("le_search_sched");
        le_search_sched->setGeometry(QRect(220, 20, 321, 24));
        btn_Sched_by_Fac = new QPushButton(Schedules);
        btn_Sched_by_Fac->setObjectName("btn_Sched_by_Fac");
        btn_Sched_by_Fac->setGeometry(QRect(550, 20, 191, 24));
        twData_sched = new QTableWidget(Schedules);
        twData_sched->setObjectName("twData_sched");
        twData_sched->setGeometry(QRect(470, 60, 721, 381));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twData_sched->sizePolicy().hasHeightForWidth());
        twData_sched->setSizePolicy(sizePolicy1);
        twData_sched->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        twData_sched->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        twData_sched->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        twData_sched->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_sched->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_sched->horizontalHeader()->setStretchLastSection(true);
        btnSched_by_Teach = new QPushButton(Schedules);
        btnSched_by_Teach->setObjectName("btnSched_by_Teach");
        btnSched_by_Teach->setGeometry(QRect(760, 20, 191, 24));
        btn_All_Scheds = new QPushButton(Schedules);
        btn_All_Scheds->setObjectName("btn_All_Scheds");
        btn_All_Scheds->setGeometry(QRect(970, 20, 191, 24));

        retranslateUi(Schedules);

        QMetaObject::connectSlotsByName(Schedules);
    } // setupUi

    void retranslateUi(QWidget *Schedules)
    {
        Schedules->setWindowTitle(QCoreApplication::translate("Schedules", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\321\217 \320\267\320\260\320\275\321\217\321\202\320\270\320\271", nullptr));
        btnPrevious->setText(QCoreApplication::translate("Schedules", "\360\237\241\270", nullptr));
        lb_id_teacher->setText(QCoreApplication::translate("Schedules", "\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
        btnNext->setText(QCoreApplication::translate("Schedules", "\360\237\241\272", nullptr));
        btnSave->setText(QCoreApplication::translate("Schedules", "\342\234\205", nullptr));
        lb_lesson_type->setText(QCoreApplication::translate("Schedules", "\320\242\320\270\320\277 \320\267\320\260\320\275\321\217\321\202\320\270\321\217", nullptr));
        lb_id_sched->setText(QCoreApplication::translate("Schedules", "ID \320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\321\217", nullptr));
        lb_time->setText(QCoreApplication::translate("Schedules", "\320\222\321\200\320\265\320\274\321\217", nullptr));
        lb_subject->setText(QCoreApplication::translate("Schedules", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202", nullptr));
        lb_id_housing->setText(QCoreApplication::translate("Schedules", "\320\232\320\276\321\200\320\277\321\203\321\201", nullptr));
        btnAddNew->setText(QCoreApplication::translate("Schedules", "\342\236\225", nullptr));
        btnEditRow->setText(QCoreApplication::translate("Schedules", "\342\234\217\357\270\217", nullptr));
        btnDelete->setText(QCoreApplication::translate("Schedules", "\342\235\214", nullptr));
        btn_to_Teachers->setText(QCoreApplication::translate("Schedules", "\320\232 \320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\217\320\274", nullptr));
        btnHome->setText(QCoreApplication::translate("Schedules", "\360\237\217\240", nullptr));
        btnLast->setText(QCoreApplication::translate("Schedules", "\342\207\266", nullptr));
        lb_faculty->setText(QCoreApplication::translate("Schedules", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        lb_week_day->setText(QCoreApplication::translate("Schedules", "\320\224\320\265\320\275\321\214 \320\275\320\265\320\264\320\265\320\273\320\270", nullptr));
        lb_search_sched->setText(QCoreApplication::translate("Schedules", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\216/\n"
"\320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\216/\n"
" \321\201\321\202\321\203\320\264\320\265\320\275\321\202\321\203", nullptr));
        btn_Sched_by_Fac->setText(QCoreApplication::translate("Schedules", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \320\277\320\276 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\216", nullptr));
        btnSched_by_Teach->setText(QCoreApplication::translate("Schedules", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \320\277\320\276 \320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\216", nullptr));
        btn_All_Scheds->setText(QCoreApplication::translate("Schedules", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\321\217 \320\262\321\201\320\265\321\205 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Schedules: public Ui_Schedules {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULES_H
