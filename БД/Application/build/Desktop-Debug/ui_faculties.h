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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnConnect;
    QPushButton *btnSelectAll;
    QTextEdit *teResult;
    QTableWidget *twData;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *lbID;
    QLineEdit *leId;
    QLabel *lbTitle;
    QTextEdit *teTitle;
    QLabel *lbHousing;
    QLineEdit *leHousingId;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDel;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        Form->resize(930, 582);
        menubar = new QMenuBar(Form);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(80, 0, 800, 21));
        statusbar = new QStatusBar(Form);
        statusbar->setObjectName("statusbar");
        statusbar->setGeometry(QRect(80, 0, 3, 22));
        centralwidget = new QWidget(Form);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setGeometry(QRect(80, 30, 781, 526));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(277, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        btnConnect = new QPushButton(centralwidget);
        btnConnect->setObjectName("btnConnect");

        gridLayout_2->addWidget(btnConnect, 0, 1, 1, 1);

        btnSelectAll = new QPushButton(centralwidget);
        btnSelectAll->setObjectName("btnSelectAll");

        gridLayout_2->addWidget(btnSelectAll, 0, 3, 1, 1);

        teResult = new QTextEdit(centralwidget);
        teResult->setObjectName("teResult");
        teResult->setReadOnly(true);

        gridLayout_2->addWidget(teResult, 2, 0, 1, 4);

        twData = new QTableWidget(centralwidget);
        twData->setObjectName("twData");

        gridLayout_2->addWidget(twData, 1, 1, 1, 3);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        lbID = new QLabel(frame);
        lbID->setObjectName("lbID");

        gridLayout->addWidget(lbID, 0, 0, 1, 1);

        leId = new QLineEdit(frame);
        leId->setObjectName("leId");

        gridLayout->addWidget(leId, 0, 1, 1, 3);

        lbTitle = new QLabel(frame);
        lbTitle->setObjectName("lbTitle");

        gridLayout->addWidget(lbTitle, 1, 0, 1, 1);

        teTitle = new QTextEdit(frame);
        teTitle->setObjectName("teTitle");

        gridLayout->addWidget(teTitle, 1, 1, 1, 3);

        lbHousing = new QLabel(frame);
        lbHousing->setObjectName("lbHousing");

        gridLayout->addWidget(lbHousing, 2, 0, 1, 1);

        leHousingId = new QLineEdit(frame);
        leHousingId->setObjectName("leHousingId");

        gridLayout->addWidget(leHousingId, 2, 1, 1, 3);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 2, 1, 1);

        btnAdd = new QPushButton(frame);
        btnAdd->setObjectName("btnAdd");

        gridLayout->addWidget(btnAdd, 4, 0, 1, 2);

        btnEdit = new QPushButton(frame);
        btnEdit->setObjectName("btnEdit");

        gridLayout->addWidget(btnEdit, 4, 2, 1, 1);

        btnDel = new QPushButton(frame);
        btnDel->setObjectName("btnDel");

        gridLayout->addWidget(btnDel, 4, 3, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 2, 1);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        btnConnect->setText(QCoreApplication::translate("Form", "Connect", nullptr));
        btnSelectAll->setText(QCoreApplication::translate("Form", "Select All", nullptr));
        lbID->setText(QCoreApplication::translate("Form", "ID", nullptr));
        lbTitle->setText(QCoreApplication::translate("Form", "Title", nullptr));
        lbHousing->setText(QCoreApplication::translate("Form", "Id_housing", nullptr));
        btnAdd->setText(QCoreApplication::translate("Form", "Add", nullptr));
        btnEdit->setText(QCoreApplication::translate("Form", "Edit", nullptr));
        btnDel->setText(QCoreApplication::translate("Form", "Del", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACULTIES_H
