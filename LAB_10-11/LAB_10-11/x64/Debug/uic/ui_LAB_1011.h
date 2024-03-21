/********************************************************************************
** Form generated from reading UI file 'LAB_1011.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB_1011_H
#define UI_LAB_1011_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LAB_1011Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LAB_1011Class)
    {
        if (LAB_1011Class->objectName().isEmpty())
            LAB_1011Class->setObjectName("LAB_1011Class");
        LAB_1011Class->resize(600, 400);
        menuBar = new QMenuBar(LAB_1011Class);
        menuBar->setObjectName("menuBar");
        LAB_1011Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LAB_1011Class);
        mainToolBar->setObjectName("mainToolBar");
        LAB_1011Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(LAB_1011Class);
        centralWidget->setObjectName("centralWidget");
        LAB_1011Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LAB_1011Class);
        statusBar->setObjectName("statusBar");
        LAB_1011Class->setStatusBar(statusBar);

        retranslateUi(LAB_1011Class);

        QMetaObject::connectSlotsByName(LAB_1011Class);
    } // setupUi

    void retranslateUi(QMainWindow *LAB_1011Class)
    {
        LAB_1011Class->setWindowTitle(QCoreApplication::translate("LAB_1011Class", "LAB_1011", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LAB_1011Class: public Ui_LAB_1011Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB_1011_H
