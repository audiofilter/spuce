/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *customPlot;
    QLabel *label;
  	QPushButton *MaxflatSubband;
  	QPushButton *EllipticSubband;
  	QPushButton *NotchIIR;
  	QPushButton *CutBoost;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 450);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(200, 10, 581, 411));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy2);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 101, 21));
        MaxflatSubband = new QPushButton(centralWidget);
        MaxflatSubband->setObjectName(QStringLiteral("MaxflatSubband"));
        MaxflatSubband->setGeometry(QRect(10, 70, 181, 27));
        MaxflatSubband->setCheckable(true);
        NotchIIR = new QPushButton(centralWidget);
        NotchIIR->setObjectName(QStringLiteral("NotchIIR"));
        NotchIIR->setGeometry(QRect(10, 100, 181, 27));
        NotchIIR->setCheckable(true);
        EllipticSubband = new QPushButton(centralWidget);
        EllipticSubband->setObjectName(QStringLiteral("EllipticSubband"));
        EllipticSubband->setGeometry(QRect(10, 160, 181, 27));
        EllipticSubband->setCheckable(true);
        CutBoost = new QPushButton(centralWidget);
        CutBoost->setObjectName(QStringLiteral("CutBoost"));
        CutBoost->setGeometry(QRect(10, 130, 181, 27));
        CutBoost->setCheckable(true);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QCustomPlot simple demo", 0));
        label->setText(QApplication::translate("MainWindow", "Filter Type", 0));
        MaxflatSubband->setText(QApplication::translate("MainWindow", "MaxflatSubband", 0));
        NotchIIR->setText(QApplication::translate("MainWindow", "NotchIIR", 0));
        EllipticSubband->setText(QApplication::translate("MainWindow", "EllipticSubband", 0));
        CutBoost->setText(QApplication::translate("MainWindow", "CutBoost", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
