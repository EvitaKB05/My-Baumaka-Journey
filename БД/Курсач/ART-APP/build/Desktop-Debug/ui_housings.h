/********************************************************************************
** Form generated from reading UI file 'housings.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOUSINGS_H
#define UI_HOUSINGS_H

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

class Ui_Housings
{
public:
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QComboBox *cb_title_h;
    QLineEdit *le_id_h;
    QLabel *lb_title_h;
    QLabel *lb_address_h;
    QPushButton *btnSave;
    QPushButton *btnPrevious;
    QPushButton *btnEditRow;
    QPushButton *btnDelete;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *le_address_h;
    QPushButton *btnAddNew;
    QLabel *lb_id_h;
    QPushButton *btnHome;
    QPushButton *btn_to_faculties;
    QPushButton *btnNext;
    QPushButton *btnLast;
    QLabel *lb_search_h;
    QLineEdit *le_search_h;
    QTableWidget *twData_h;

    void setupUi(QWidget *Housings)
    {
        if (Housings->objectName().isEmpty())
            Housings->setObjectName("Housings");
        Housings->resize(1000, 550);
        frame = new QFrame(Housings);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(20, 70, 400, 430));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName("gridLayout_2");
        cb_title_h = new QComboBox(frame);
        cb_title_h->setObjectName("cb_title_h");
        cb_title_h->setEditable(true);

        gridLayout_2->addWidget(cb_title_h, 1, 2, 1, 8);

        le_id_h = new QLineEdit(frame);
        le_id_h->setObjectName("le_id_h");

        gridLayout_2->addWidget(le_id_h, 0, 2, 1, 8);

        lb_title_h = new QLabel(frame);
        lb_title_h->setObjectName("lb_title_h");

        gridLayout_2->addWidget(lb_title_h, 1, 0, 1, 2);

        lb_address_h = new QLabel(frame);
        lb_address_h->setObjectName("lb_address_h");

        gridLayout_2->addWidget(lb_address_h, 2, 0, 1, 1);

        btnSave = new QPushButton(frame);
        btnSave->setObjectName("btnSave");

        gridLayout_2->addWidget(btnSave, 7, 0, 1, 2);

        btnPrevious = new QPushButton(frame);
        btnPrevious->setObjectName("btnPrevious");

        gridLayout_2->addWidget(btnPrevious, 6, 0, 1, 1);

        btnEditRow = new QPushButton(frame);
        btnEditRow->setObjectName("btnEditRow");

        gridLayout_2->addWidget(btnEditRow, 7, 3, 1, 1);

        btnDelete = new QPushButton(frame);
        btnDelete->setObjectName("btnDelete");

        gridLayout_2->addWidget(btnDelete, 7, 4, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 3, 5, 1, 1);

        le_address_h = new QLineEdit(frame);
        le_address_h->setObjectName("le_address_h");

        gridLayout_2->addWidget(le_address_h, 2, 2, 1, 8);

        btnAddNew = new QPushButton(frame);
        btnAddNew->setObjectName("btnAddNew");

        gridLayout_2->addWidget(btnAddNew, 7, 2, 1, 1);

        lb_id_h = new QLabel(frame);
        lb_id_h->setObjectName("lb_id_h");

        gridLayout_2->addWidget(lb_id_h, 0, 0, 1, 2);

        btnHome = new QPushButton(frame);
        btnHome->setObjectName("btnHome");

        gridLayout_2->addWidget(btnHome, 6, 4, 1, 1);

        btn_to_faculties = new QPushButton(frame);
        btn_to_faculties->setObjectName("btn_to_faculties");

        gridLayout_2->addWidget(btn_to_faculties, 6, 2, 1, 2);

        btnNext = new QPushButton(frame);
        btnNext->setObjectName("btnNext");

        gridLayout_2->addWidget(btnNext, 6, 5, 1, 1);

        btnLast = new QPushButton(frame);
        btnLast->setObjectName("btnLast");

        gridLayout_2->addWidget(btnLast, 6, 7, 1, 1);

        lb_search_h = new QLabel(Housings);
        lb_search_h->setObjectName("lb_search_h");
        lb_search_h->setGeometry(QRect(180, 20, 161, 24));
        le_search_h = new QLineEdit(Housings);
        le_search_h->setObjectName("le_search_h");
        le_search_h->setGeometry(QRect(350, 20, 400, 24));
        twData_h = new QTableWidget(Housings);
        twData_h->setObjectName("twData_h");
        twData_h->setGeometry(QRect(440, 70, 540, 430));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twData_h->sizePolicy().hasHeightForWidth());
        twData_h->setSizePolicy(sizePolicy1);
        twData_h->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        twData_h->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        twData_h->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        twData_h->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_h->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        twData_h->horizontalHeader()->setStretchLastSection(true);

        retranslateUi(Housings);

        QMetaObject::connectSlotsByName(Housings);
    } // setupUi

    void retranslateUi(QWidget *Housings)
    {
        Housings->setWindowTitle(QCoreApplication::translate("Housings", "\320\232\320\276\321\200\320\277\321\203\321\201\320\260", nullptr));
        lb_title_h->setText(QCoreApplication::translate("Housings", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        lb_address_h->setText(QCoreApplication::translate("Housings", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        btnSave->setText(QCoreApplication::translate("Housings", "\342\234\205", nullptr));
        btnPrevious->setText(QCoreApplication::translate("Housings", "\360\237\241\270", nullptr));
        btnEditRow->setText(QCoreApplication::translate("Housings", "\342\234\217\357\270\217", nullptr));
        btnDelete->setText(QCoreApplication::translate("Housings", "\342\235\214", nullptr));
        btnAddNew->setText(QCoreApplication::translate("Housings", "\342\236\225", nullptr));
        lb_id_h->setText(QCoreApplication::translate("Housings", "ID \320\232\320\276\321\200\320\277\321\203\321\201\320\260", nullptr));
        btnHome->setText(QCoreApplication::translate("Housings", "\360\237\217\240", nullptr));
        btn_to_faculties->setText(QCoreApplication::translate("Housings", "\320\232 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217\320\274", nullptr));
        btnNext->setText(QCoreApplication::translate("Housings", "\360\237\241\272", nullptr));
        btnLast->setText(QCoreApplication::translate("Housings", "\342\207\266", nullptr));
        lb_search_h->setText(QCoreApplication::translate("Housings", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\321\216/\320\260\320\264\321\200\320\265\321\201\321\203:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Housings: public Ui_Housings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOUSINGS_H
