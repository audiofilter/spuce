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
    QPushButton *MaxflatFIR;
    QPushButton *RaisedCosine;
    QPushButton *RootRaisedCosine;
    QPushButton *Gaussian;
    QPushButton *Sinc;
    QPushButton *Remez;
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
        MaxflatFIR = new QPushButton(centralWidget);
        MaxflatFIR->setObjectName(QStringLiteral("MaxflatFIR"));
        MaxflatFIR->setGeometry(QRect(10, 30, 181, 27));
        MaxflatFIR->setCheckable(true);
        RaisedCosine = new QPushButton(centralWidget);
        RaisedCosine->setObjectName(QStringLiteral("RaisedCosine"));
        RaisedCosine->setGeometry(QRect(10, 60, 181, 27));
        RaisedCosine->setCheckable(true);
        RootRaisedCosine = new QPushButton(centralWidget);
        RootRaisedCosine->setObjectName(QStringLiteral("RootRaisedCosine"));
        RootRaisedCosine->setGeometry(QRect(10, 90, 181, 27));
        RootRaisedCosine->setCheckable(true);
        Remez = new QPushButton(centralWidget);
        Remez->setObjectName(QStringLiteral("Remez"));
        Remez->setGeometry(QRect(10, 120, 181, 27));
        Remez->setCheckable(true);
        Gaussian = new QPushButton(centralWidget);
        Gaussian->setObjectName(QStringLiteral("Gaussian"));
        Gaussian->setGeometry(QRect(10, 150, 181, 27));
        Gaussian->setCheckable(true);
        Sinc = new QPushButton(centralWidget);
        Sinc->setObjectName(QStringLiteral("Sinc"));
        Sinc->setGeometry(QRect(10, 180, 181, 27));
        Sinc->setCheckable(true);
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
        MaxflatFIR->setText(QApplication::translate("MainWindow", "Maxflat FIR", 0));
        RaisedCosine->setText(QApplication::translate("MainWindow", "RaisedCosine", 0));
        RootRaisedCosine->setText(QApplication::translate("MainWindow", "RootRaisedCosine", 0));
        Remez->setText(QApplication::translate("MainWindow", "Remez", 0));
        Gaussian->setText(QApplication::translate("MainWindow", "Gaussian", 0));
        Sinc->setText(QApplication::translate("MainWindow", "Sinc", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
