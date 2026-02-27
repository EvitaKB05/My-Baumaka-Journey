/********************************************************************************
** Form generated from reading UI file 'subjects.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBJECTS_H
#define UI_SUBJECTS_H

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

class Ui_Subjects
{
public:
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QPushButton *btnSave;
    QSpacerItem *verticalSpacer_3;
    QLabel *lb_id_sub;
    QPushButton *btnEditRow;
    QPushButton *btnDelete;
    QPushButton *btnPrevious;
    QPushButton *btnNext;
    QLabel *lb_faculty;
    QLineEdit *le_learning_hours;
    QLabel *lb_learning_hours;
    QComboBox *cb_title_sub;
    QPushButton *btnAddNew;
    QPushButton *btnLast;
    QPushButton *btnHome;
    QPushButton *btn_to_schedules;
    QLabel *lb_name_sub;
    QComboBox *cb_id_faculty;
    QLineEdit *le_id_sub;
    QLabel *lb_search_sub;
    QLineEdit *le_search_sub;
    QPushButton *btnTeach_by_Sub;
    QTableWidget *twData_sub;
    QPushButton *btnStud_by_Sub;
    QPushButton *btnSub_by_Fac;
    QPushButton *btnAllSubs;

    void setupUi(QWidget *Subjects)
    {
        if (Subjects->objectName().isEmpty())
            Subjects->setObjectName("Subjects");
        Subjects->resize(1260, 470);
        frame = new QFrame(Subjects);
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
        btnSave = new QPushButton(frame);
        btnSave->setObjectName("btnSave");

        gridLayout_2->addWidget(btnSave, 6, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 4, 5, 1, 1);

        lb_id_sub = new QLabel(frame);
        lb_id_sub->setObjectName("lb_id_sub");

        gridLayout_2->addWidget(lb_id_sub, 0, 0, 1, 2);

        btnEditRow = new QPushButton(frame);
        btnEditRow->setObjectName("btnEditRow");

        gridLayout_2->addWidget(btnEditRow, 6, 2, 1, 1);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName("btnDelete");

        gridLayout_2->addWidget(btnDelete, 6, 3, 1, 1);

        btnPrevious = new QPushButton(frame);
        btnPrevious->setObjectName("btnPrevious");

        gridLayout_2->addWidget(btnPrevious, 5, 0, 1, 1);

        btnNext = new QPushButton(frame);
        btnNext->setObjectName("btnNext");

        gridLayout_2->addWidget(btnNext, 5, 4, 1, 1);

        lb_faculty = new QLabel(frame);
        lb_faculty->setObjectName("lb_faculty");

        gridLayout_2->addWidget(lb_faculty, 3, 0, 1, 2);

        le_learning_hours = new QLineEdit(frame);
        le_learning_hours->setObjectName("le_learning_hours");

        gridLayout_2->addWidget(le_learning_hours, 2, 2, 1, 5);

        lb_learning_hours = new QLabel(frame);
        lb_learning_hours->setObjectName("lb_learning_hours");

        gridLayout_2->addWidget(lb_learning_hours, 2, 0, 1, 2);

        cb_title_sub = new QComboBox(frame);
        cb_title_sub->setObjectName("cb_title_sub");
        cb_title_sub->setEditable(true);

        gridLayout_2->addWidget(cb_title_sub, 1, 2, 1, 5);

        btnAddNew = new QPushButton(frame);
        btnAddNew->setObjectName("btnAddNew");

        gridLayout_2->addWidget(btnAddNew, 6, 1, 1, 1);

        btnLast = new QPushButton(frame);
        btnLast->setObjectName("btnLast");

        gridLayout_2->addWidget(btnLast, 5, 5, 1, 1);

        btnHome = new QPushButton(frame);
        btnHome->setObjectName("btnHome");

        gridLayout_2->addWidget(btnHome, 5, 3, 1, 1);

        btn_to_schedules = new QPushButton(frame);
        btn_to_schedules->setObjectName("btn_to_schedules");

        gridLayout_2->addWidget(btn_to_schedules, 5, 1, 1, 2);

        lb_name_sub = new QLabel(frame);
        lb_name_sub->setObjectName("lb_name_sub");

        gridLayout_2->addWidget(lb_name_sub, 1, 0, 1, 2);

        cb_id_faculty = new QComboBox(frame);
        cb_id_faculty->setObjectName("cb_id_faculty");
        cb_id_faculty->setEditable(true);

        gridLayout_2->addWidget(cb_id_faculty, 3, 2, 1, 5);

        le_id_sub = new QLineEdit(frame);
        le_id_sub->setObjectName("le_id_sub");

        gridLayout_2->addWidget(le_id_sub, 0, 2, 1, 5);

        lb_search_sub = new QLabel(Subjects);
        lb_search_sub->setObjectName("lb_search_sub");
        lb_search_sub->setGeometry(QRect(10, 20, 181, 24));
        le_search_sub = new QLineEdit(Subjects);
        le_search_sub->setObjectName("le_search_sub");
        le_search_sub->setGeometry(QRect(200, 20, 321, 24));
        btnTeach_by_Sub = new QPushButton(Subjects);
        btnTeach_by_Sub->setObjectName("btnTeach_by_Sub");
        btnTeach_by_Sub->setGeometry(QRect(530, 20, 171, 24));
        twData_sub = new QTableWidget(Subjects);
        twData_sub->setObjectName("twData_sub");
        twData_sub->setGeometry(QRect(470, 60, 721, 331));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twData_sub->sizePolicy().hasHeightForWidth());
        twData_sub->setSizePolicy(sizePolicy1);
        twData_sub->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        twData_sub->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        twData_sub->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        twData_sub->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_sub->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_sub->horizontalHeader()->setStretchLastSection(true);
        btnStud_by_Sub = new QPushButton(Subjects);
        btnStud_by_Sub->setObjectName("btnStud_by_Sub");
        btnStud_by_Sub->setGeometry(QRect(710, 20, 131, 24));
        btnSub_by_Fac = new QPushButton(Subjects);
        btnSub_by_Fac->setObjectName("btnSub_by_Fac");
        btnSub_by_Fac->setGeometry(QRect(850, 20, 161, 24));
        btnAllSubs = new QPushButton(Subjects);
        btnAllSubs->setObjectName("btnAllSubs");
        btnAllSubs->setGeometry(QRect(1020, 20, 101, 24));

        retranslateUi(Subjects);

        QMetaObject::connectSlotsByName(Subjects);
    } // setupUi

    void retranslateUi(QWidget *Subjects)
    {
        Subjects->setWindowTitle(QCoreApplication::translate("Subjects", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202\321\213", nullptr));
        btnSave->setText(QCoreApplication::translate("Subjects", "\342\234\205", nullptr));
        lb_id_sub->setText(QCoreApplication::translate("Subjects", "ID \320\237\321\200\320\265\320\264\320\274\320\265\321\202\320\260", nullptr));
        btnEditRow->setText(QCoreApplication::translate("Subjects", "\342\234\217\357\270\217", nullptr));
        btnDelete->setText(QCoreApplication::translate("Subjects", "\342\235\214", nullptr));
        btnPrevious->setText(QCoreApplication::translate("Subjects", "\360\237\241\270", nullptr));
        btnNext->setText(QCoreApplication::translate("Subjects", "\360\237\241\272", nullptr));
        lb_faculty->setText(QCoreApplication::translate("Subjects", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        lb_learning_hours->setText(QCoreApplication::translate("Subjects", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\207\320\260\321\201\320\276\320\262", nullptr));
        btnAddNew->setText(QCoreApplication::translate("Subjects", "\342\236\225", nullptr));
        btnLast->setText(QCoreApplication::translate("Subjects", "\342\207\266", nullptr));
        btnHome->setText(QCoreApplication::translate("Subjects", "\360\237\217\240", nullptr));
        btn_to_schedules->setText(QCoreApplication::translate("Subjects", "\320\232 \321\200\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\321\217\320\274", nullptr));
        lb_name_sub->setText(QCoreApplication::translate("Subjects", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        lb_search_sub->setText(QCoreApplication::translate("Subjects", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\321\216:", nullptr));
        btnTeach_by_Sub->setText(QCoreApplication::translate("Subjects", "\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\320\270 \320\277\320\276 \320\277\321\200\320\265\320\264\320\274\320\265\321\202\321\203", nullptr));
        btnStud_by_Sub->setText(QCoreApplication::translate("Subjects", "\320\241\321\202\321\203\320\264\320\265\320\275\321\202\321\213 \320\277\320\276 \320\277\321\200\320\265\320\264\320\274\320\265\321\202\321\203", nullptr));
        btnSub_by_Fac->setText(QCoreApplication::translate("Subjects", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202\321\213 \320\277\320\276 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\216", nullptr));
        btnAllSubs->setText(QCoreApplication::translate("Subjects", "\320\222\321\201\320\265 \320\277\321\200\320\265\320\264\320\274\320\265\321\202\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Subjects: public Ui_Subjects {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBJECTS_H
