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
    QLineEdit *leAddress;
    QPushButton *btnAdd;
    QLabel *lbID;
    QTextEdit *teTitle;
    QLabel *lbAddress;
    QLabel *lbTitle;
    QPushButton *btnEdit;
    QLineEdit *leId;
    QPushButton *btnDel;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnConnect;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSelectAll;
    QTableWidget *twData;
    QTextEdit *teResult;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
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
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        leAddress = new QLineEdit(frame);
        leAddress->setObjectName("leAddress");

        gridLayout->addWidget(leAddress, 2, 1, 1, 3);

        btnAdd = new QPushButton(frame);
        btnAdd->setObjectName("btnAdd");

        gridLayout->addWidget(btnAdd, 4, 0, 1, 2);

        lbID = new QLabel(frame);
        lbID->setObjectName("lbID");

        gridLayout->addWidget(lbID, 0, 0, 1, 1);

        teTitle = new QTextEdit(frame);
        teTitle->setObjectName("teTitle");

        gridLayout->addWidget(teTitle, 1, 1, 1, 3);

        lbAddress = new QLabel(frame);
        lbAddress->setObjectName("lbAddress");

        gridLayout->addWidget(lbAddress, 2, 0, 1, 1);

        lbTitle = new QLabel(frame);
        lbTitle->setObjectName("lbTitle");

        gridLayout->addWidget(lbTitle, 1, 0, 1, 1);

        btnEdit = new QPushButton(frame);
        btnEdit->setObjectName("btnEdit");

        gridLayout->addWidget(btnEdit, 4, 2, 1, 1);

        leId = new QLineEdit(frame);
        leId->setObjectName("leId");

        gridLayout->addWidget(leId, 0, 1, 1, 3);

        btnDel = new QPushButton(frame);
        btnDel->setObjectName("btnDel");

        gridLayout->addWidget(btnDel, 4, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 2, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 2, 1);

        btnConnect = new QPushButton(centralwidget);
        btnConnect->setObjectName("btnConnect");

        gridLayout_2->addWidget(btnConnect, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(277, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);

        btnSelectAll = new QPushButton(centralwidget);
        btnSelectAll->setObjectName("btnSelectAll");

        gridLayout_2->addWidget(btnSelectAll, 0, 3, 1, 1);

        twData = new QTableWidget(centralwidget);
        twData->setObjectName("twData");

        gridLayout_2->addWidget(twData, 1, 1, 1, 3);

        teResult = new QTextEdit(centralwidget);
        teResult->setObjectName("teResult");
        teResult->setReadOnly(true);

        gridLayout_2->addWidget(teResult, 2, 0, 1, 4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
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
        btnAdd->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        lbID->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        lbAddress->setText(QCoreApplication::translate("MainWindow", "Address", nullptr));
        lbTitle->setText(QCoreApplication::translate("MainWindow", "Title", nullptr));
        btnEdit->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        btnDel->setText(QCoreApplication::translate("MainWindow", "Del", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        btnSelectAll->setText(QCoreApplication::translate("MainWindow", "Select All", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
