/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *lbFio;
    QLineEdit *LeFio;
    QLabel *lbAdress;
    QTextEdit *LeAdress;
    QLabel *lbPhone;
    QLineEdit *LePhone;
    QLabel *lbCard_id;
    QLineEdit *LeCard_id;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDel;
    QPushButton *btnConnect;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSelectAll;
    QLabel *label;
    QTableWidget *twPatient;
    QLabel *label_2;
    QTableWidget *twMed;
    QTextEdit *teResult;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(884, 556);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        lbFio = new QLabel(frame);
        lbFio->setObjectName("lbFio");
        lbFio->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(lbFio, 0, 0, 1, 1);

        LeFio = new QLineEdit(frame);
        LeFio->setObjectName("LeFio");

        gridLayout->addWidget(LeFio, 0, 1, 1, 1);

        lbAdress = new QLabel(frame);
        lbAdress->setObjectName("lbAdress");
        lbAdress->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(lbAdress, 1, 0, 1, 1);

        LeAdress = new QTextEdit(frame);
        LeAdress->setObjectName("LeAdress");

        gridLayout->addWidget(LeAdress, 1, 1, 1, 2);

        lbPhone = new QLabel(frame);
        lbPhone->setObjectName("lbPhone");
        lbPhone->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(lbPhone, 2, 0, 1, 1);

        LePhone = new QLineEdit(frame);
        LePhone->setObjectName("LePhone");

        gridLayout->addWidget(LePhone, 2, 1, 1, 1);

        lbCard_id = new QLabel(frame);
        lbCard_id->setObjectName("lbCard_id");
        lbCard_id->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(lbCard_id, 3, 0, 1, 1);

        LeCard_id = new QLineEdit(frame);
        LeCard_id->setObjectName("LeCard_id");

        gridLayout->addWidget(LeCard_id, 3, 1, 1, 1);

        btnAdd = new QPushButton(frame);
        btnAdd->setObjectName("btnAdd");

        gridLayout->addWidget(btnAdd, 4, 0, 1, 2);

        btnEdit = new QPushButton(frame);
        btnEdit->setObjectName("btnEdit");

        gridLayout->addWidget(btnEdit, 4, 2, 1, 1);

        btnDel = new QPushButton(frame);
        btnDel->setObjectName("btnDel");

        gridLayout->addWidget(btnDel, 4, 3, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 5, 1);

        btnConnect = new QPushButton(centralwidget);
        btnConnect->setObjectName("btnConnect");

        gridLayout_2->addWidget(btnConnect, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(279, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        btnSelectAll = new QPushButton(centralwidget);
        btnSelectAll->setObjectName("btnSelectAll");

        gridLayout_2->addWidget(btnSelectAll, 0, 3, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 1, 1, 1, 1);

        twPatient = new QTableWidget(centralwidget);
        twPatient->setObjectName("twPatient");
        twPatient->setMinimumSize(QSize(10, 10));

        gridLayout_2->addWidget(twPatient, 2, 1, 1, 3);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 3, 1, 1, 1);

        twMed = new QTableWidget(centralwidget);
        twMed->setObjectName("twMed");

        gridLayout_2->addWidget(twMed, 4, 1, 1, 3);

        teResult = new QTextEdit(centralwidget);
        teResult->setObjectName("teResult");
        teResult->setReadOnly(true);

        gridLayout_2->addWidget(teResult, 5, 0, 1, 4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 884, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lbFio->setText(QCoreApplication::translate("MainWindow", "FIO", nullptr));
        lbAdress->setText(QCoreApplication::translate("MainWindow", "adress", nullptr));
        lbPhone->setText(QCoreApplication::translate("MainWindow", "phone", nullptr));
        lbCard_id->setText(QCoreApplication::translate("MainWindow", "card_id", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        btnEdit->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        btnDel->setText(QCoreApplication::translate("MainWindow", "Del", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        btnSelectAll->setText(QCoreApplication::translate("MainWindow", "Select All", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\206\320\270\320\265\320\275\321\202\321\213", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\264\320\272\320\260\321\200\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
