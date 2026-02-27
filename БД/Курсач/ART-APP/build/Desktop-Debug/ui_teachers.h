/********************************************************************************
** Form generated from reading UI file 'teachers.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACHERS_H
#define UI_TEACHERS_H

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

class Ui_Teachers
{
public:
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *le_id_te;
    QLineEdit *le_contacts_te;
    QLabel *lb_fio_te;
    QPushButton *btnNext;
    QPushButton *btnPrevious;
    QPushButton *btnSave;
    QComboBox *cb_id_faculty;
    QComboBox *cb_fio_te;
    QLabel *lb_id_te;
    QLabel *lb_faculty;
    QLabel *lb_contacts_te;
    QComboBox *cb_post;
    QLabel *lb_post;
    QPushButton *btnAddNew;
    QPushButton *btnEditRow;
    QPushButton *btnDelete;
    QPushButton *btnLast;
    QPushButton *btn_to_schedules;
    QPushButton *btnHome;
    QLabel *lb_search_te;
    QLineEdit *le_search_te;
    QPushButton *btnTeach_by_Fac;
    QTableWidget *twData_te;
    QPushButton *btn_All_Teach_by_All_Facs;

    void setupUi(QWidget *Teachers)
    {
        if (Teachers->objectName().isEmpty())
            Teachers->setObjectName("Teachers");
        Teachers->resize(1260, 470);
        frame = new QFrame(Teachers);
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
        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 5, 4, 1, 1);

        le_id_te = new QLineEdit(frame);
        le_id_te->setObjectName("le_id_te");

        gridLayout_2->addWidget(le_id_te, 0, 2, 1, 7);

        le_contacts_te = new QLineEdit(frame);
        le_contacts_te->setObjectName("le_contacts_te");

        gridLayout_2->addWidget(le_contacts_te, 2, 2, 1, 7);

        lb_fio_te = new QLabel(frame);
        lb_fio_te->setObjectName("lb_fio_te");

        gridLayout_2->addWidget(lb_fio_te, 1, 0, 1, 2);

        btnNext = new QPushButton(frame);
        btnNext->setObjectName("btnNext");

        gridLayout_2->addWidget(btnNext, 6, 4, 1, 1);

        btnPrevious = new QPushButton(frame);
        btnPrevious->setObjectName("btnPrevious");

        gridLayout_2->addWidget(btnPrevious, 6, 0, 1, 1);

        btnSave = new QPushButton(frame);
        btnSave->setObjectName("btnSave");

        gridLayout_2->addWidget(btnSave, 7, 0, 1, 1);

        cb_id_faculty = new QComboBox(frame);
        cb_id_faculty->setObjectName("cb_id_faculty");
        cb_id_faculty->setEditable(true);

        gridLayout_2->addWidget(cb_id_faculty, 4, 2, 1, 7);

        cb_fio_te = new QComboBox(frame);
        cb_fio_te->setObjectName("cb_fio_te");
        cb_fio_te->setEditable(true);

        gridLayout_2->addWidget(cb_fio_te, 1, 2, 1, 7);

        lb_id_te = new QLabel(frame);
        lb_id_te->setObjectName("lb_id_te");

        gridLayout_2->addWidget(lb_id_te, 0, 0, 1, 2);

        lb_faculty = new QLabel(frame);
        lb_faculty->setObjectName("lb_faculty");

        gridLayout_2->addWidget(lb_faculty, 4, 0, 1, 2);

        lb_contacts_te = new QLabel(frame);
        lb_contacts_te->setObjectName("lb_contacts_te");

        gridLayout_2->addWidget(lb_contacts_te, 2, 0, 1, 2);

        cb_post = new QComboBox(frame);
        cb_post->setObjectName("cb_post");
        cb_post->setEditable(true);

        gridLayout_2->addWidget(cb_post, 3, 2, 1, 7);

        lb_post = new QLabel(frame);
        lb_post->setObjectName("lb_post");

        gridLayout_2->addWidget(lb_post, 3, 0, 1, 1);

        btnAddNew = new QPushButton(frame);
        btnAddNew->setObjectName("btnAddNew");

        gridLayout_2->addWidget(btnAddNew, 7, 1, 1, 1);

        btnEditRow = new QPushButton(frame);
        btnEditRow->setObjectName("btnEditRow");

        gridLayout_2->addWidget(btnEditRow, 7, 2, 1, 1);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName("btnDelete");

        gridLayout_2->addWidget(btnDelete, 7, 3, 1, 1);

        btnLast = new QPushButton(frame);
        btnLast->setObjectName("btnLast");

        gridLayout_2->addWidget(btnLast, 6, 5, 1, 1);

        btn_to_schedules = new QPushButton(frame);
        btn_to_schedules->setObjectName("btn_to_schedules");

        gridLayout_2->addWidget(btn_to_schedules, 6, 1, 1, 2);

        btnHome = new QPushButton(frame);
        btnHome->setObjectName("btnHome");

        gridLayout_2->addWidget(btnHome, 6, 3, 1, 1);

        lb_search_te = new QLabel(Teachers);
        lb_search_te->setObjectName("lb_search_te");
        lb_search_te->setGeometry(QRect(10, 20, 181, 24));
        le_search_te = new QLineEdit(Teachers);
        le_search_te->setObjectName("le_search_te");
        le_search_te->setGeometry(QRect(200, 20, 321, 24));
        btnTeach_by_Fac = new QPushButton(Teachers);
        btnTeach_by_Fac->setObjectName("btnTeach_by_Fac");
        btnTeach_by_Fac->setGeometry(QRect(550, 20, 191, 24));
        twData_te = new QTableWidget(Teachers);
        twData_te->setObjectName("twData_te");
        twData_te->setGeometry(QRect(470, 60, 721, 331));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twData_te->sizePolicy().hasHeightForWidth());
        twData_te->setSizePolicy(sizePolicy1);
        twData_te->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        twData_te->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        twData_te->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        twData_te->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_te->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_te->horizontalHeader()->setStretchLastSection(true);
        btn_All_Teach_by_All_Facs = new QPushButton(Teachers);
        btn_All_Teach_by_All_Facs->setObjectName("btn_All_Teach_by_All_Facs");
        btn_All_Teach_by_All_Facs->setGeometry(QRect(770, 20, 201, 24));

        retranslateUi(Teachers);

        QMetaObject::connectSlotsByName(Teachers);
    } // setupUi

    void retranslateUi(QWidget *Teachers)
    {
        Teachers->setWindowTitle(QCoreApplication::translate("Teachers", "\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\320\270", nullptr));
        lb_fio_te->setText(QCoreApplication::translate("Teachers", "\320\244\320\230\320\236", nullptr));
        btnNext->setText(QCoreApplication::translate("Teachers", "\360\237\241\272", nullptr));
        btnPrevious->setText(QCoreApplication::translate("Teachers", "\360\237\241\270", nullptr));
        btnSave->setText(QCoreApplication::translate("Teachers", "\342\234\205", nullptr));
        lb_id_te->setText(QCoreApplication::translate("Teachers", "ID \320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        lb_faculty->setText(QCoreApplication::translate("Teachers", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        lb_contacts_te->setText(QCoreApplication::translate("Teachers", "\320\232\320\276\320\275\321\202\320\260\320\272\321\202\321\213", nullptr));
        lb_post->setText(QCoreApplication::translate("Teachers", "\320\224\320\276\320\273\320\266\320\275\320\276\321\201\321\202\321\214", nullptr));
        btnAddNew->setText(QCoreApplication::translate("Teachers", "\342\236\225", nullptr));
        btnEditRow->setText(QCoreApplication::translate("Teachers", "\342\234\217\357\270\217", nullptr));
        btnDelete->setText(QCoreApplication::translate("Teachers", "\342\235\214", nullptr));
        btnLast->setText(QCoreApplication::translate("Teachers", "\342\207\266", nullptr));
        btn_to_schedules->setText(QCoreApplication::translate("Teachers", "\320\232 \321\200\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\321\217\320\274", nullptr));
        btnHome->setText(QCoreApplication::translate("Teachers", "\360\237\217\240", nullptr));
        lb_search_te->setText(QCoreApplication::translate("Teachers", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \320\244\320\230\320\236/\320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\216:", nullptr));
        btnTeach_by_Fac->setText(QCoreApplication::translate("Teachers", "\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\320\270 \320\277\320\276 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\216", nullptr));
        btn_All_Teach_by_All_Facs->setText(QCoreApplication::translate("Teachers", "\320\237\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\320\270 \320\262\321\201\320\265\321\205 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Teachers: public Ui_Teachers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACHERS_H
