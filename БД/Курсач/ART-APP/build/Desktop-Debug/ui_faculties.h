/********************************************************************************
** Form generated from reading UI file 'faculties.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACULTIES_H
#define UI_FACULTIES_H

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

class Ui_Faculties
{
public:
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QPushButton *btnSave;
    QLabel *lb_id_housing;
    QSpacerItem *verticalSpacer_3;
    QLabel *lb_title_f;
    QComboBox *cb_id_housing;
    QPushButton *btnPrevious;
    QLineEdit *le_id_f;
    QComboBox *cb_title_f;
    QPushButton *btn_to_housings;
    QPushButton *btnAddNew;
    QPushButton *btnEditRow;
    QPushButton *btnHome;
    QPushButton *btnDelete;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QLabel *lb_id_f;
    QLabel *lb_search_f;
    QLineEdit *le_search_f;
    QTableWidget *twData_f;

    void setupUi(QWidget *Faculties)
    {
        if (Faculties->objectName().isEmpty())
            Faculties->setObjectName("Faculties");
        Faculties->resize(1000, 550);
        frame = new QFrame(Faculties);
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
        btnSave = new QPushButton(frame);
        btnSave->setObjectName("btnSave");

        gridLayout_2->addWidget(btnSave, 5, 0, 1, 1);

        lb_id_housing = new QLabel(frame);
        lb_id_housing->setObjectName("lb_id_housing");

        gridLayout_2->addWidget(lb_id_housing, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 3, 5, 1, 1);

        lb_title_f = new QLabel(frame);
        lb_title_f->setObjectName("lb_title_f");

        gridLayout_2->addWidget(lb_title_f, 1, 0, 1, 2);

        cb_id_housing = new QComboBox(frame);
        cb_id_housing->setObjectName("cb_id_housing");
        cb_id_housing->setEditable(true);

        gridLayout_2->addWidget(cb_id_housing, 2, 3, 1, 7);

        btnPrevious = new QPushButton(frame);
        btnPrevious->setObjectName("btnPrevious");

        gridLayout_2->addWidget(btnPrevious, 4, 0, 1, 1);

        le_id_f = new QLineEdit(frame);
        le_id_f->setObjectName("le_id_f");

        gridLayout_2->addWidget(le_id_f, 0, 3, 1, 7);

        cb_title_f = new QComboBox(frame);
        cb_title_f->setObjectName("cb_title_f");
        cb_title_f->setEditable(true);

        gridLayout_2->addWidget(cb_title_f, 1, 3, 1, 7);

        btn_to_housings = new QPushButton(frame);
        btn_to_housings->setObjectName("btn_to_housings");

        gridLayout_2->addWidget(btn_to_housings, 4, 2, 1, 1);

        btnAddNew = new QPushButton(frame);
        btnAddNew->setObjectName("btnAddNew");

        gridLayout_2->addWidget(btnAddNew, 5, 2, 1, 1);

        btnEditRow = new QPushButton(frame);
        btnEditRow->setObjectName("btnEditRow");

        gridLayout_2->addWidget(btnEditRow, 5, 3, 1, 1);

        btnHome = new QPushButton(frame);
        btnHome->setObjectName("btnHome");

        gridLayout_2->addWidget(btnHome, 4, 3, 1, 1);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName("btnDelete");

        gridLayout_2->addWidget(btnDelete, 5, 4, 1, 1);

        btnNext = new QPushButton(frame);
        btnNext->setObjectName("btnNext");

        gridLayout_2->addWidget(btnNext, 4, 4, 1, 1);

        btnLast = new QPushButton(frame);
        btnLast->setObjectName("btnLast");

        gridLayout_2->addWidget(btnLast, 4, 5, 1, 1);

        lb_id_f = new QLabel(frame);
        lb_id_f->setObjectName("lb_id_f");

        gridLayout_2->addWidget(lb_id_f, 0, 0, 1, 3);

        lb_search_f = new QLabel(Faculties);
        lb_search_f->setObjectName("lb_search_f");
        lb_search_f->setGeometry(QRect(130, 20, 191, 24));
        le_search_f = new QLineEdit(Faculties);
        le_search_f->setObjectName("le_search_f");
        le_search_f->setGeometry(QRect(330, 20, 321, 24));
        twData_f = new QTableWidget(Faculties);
        twData_f->setObjectName("twData_f");
        twData_f->setGeometry(QRect(470, 60, 511, 381));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twData_f->sizePolicy().hasHeightForWidth());
        twData_f->setSizePolicy(sizePolicy1);
        twData_f->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        twData_f->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        twData_f->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        twData_f->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_f->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_f->horizontalHeader()->setStretchLastSection(true);

        retranslateUi(Faculties);

        QMetaObject::connectSlotsByName(Faculties);
    } // setupUi

    void retranslateUi(QWidget *Faculties)
    {
        Faculties->setWindowTitle(QCoreApplication::translate("Faculties", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        btnSave->setText(QCoreApplication::translate("Faculties", "\342\234\205", nullptr));
        lb_id_housing->setText(QCoreApplication::translate("Faculties", "\320\232\320\276\321\200\320\277\321\203\321\201", nullptr));
        lb_title_f->setText(QCoreApplication::translate("Faculties", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        btnPrevious->setText(QCoreApplication::translate("Faculties", "\360\237\241\270", nullptr));
        btn_to_housings->setText(QCoreApplication::translate("Faculties", "\320\232 \320\272\320\276\321\200\320\277\321\203\321\201\320\260\320\274", nullptr));
        btnAddNew->setText(QCoreApplication::translate("Faculties", "\342\236\225", nullptr));
        btnEditRow->setText(QCoreApplication::translate("Faculties", "\342\234\217\357\270\217", nullptr));
        btnHome->setText(QCoreApplication::translate("Faculties", "\360\237\217\240", nullptr));
        btnDelete->setText(QCoreApplication::translate("Faculties", "\342\235\214", nullptr));
        btnNext->setText(QCoreApplication::translate("Faculties", "\360\237\241\272", nullptr));
        btnLast->setText(QCoreApplication::translate("Faculties", "\342\207\266", nullptr));
        lb_id_f->setText(QCoreApplication::translate("Faculties", "ID \320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        lb_search_f->setText(QCoreApplication::translate("Faculties", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\321\216/\320\272\320\276\321\200\320\277\321\203\321\201\321\203:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Faculties: public Ui_Faculties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACULTIES_H
