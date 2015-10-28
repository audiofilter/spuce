/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
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
    QPushButton *Chebyshev;
    QPushButton *Elliptic;
    QPushButton *MaxflatFIR;
    QPushButton *MaxflatHalfband;
    QPushButton *RaisedCosine;
    QPushButton *RootRaisedCosine;
    QPushButton *EllipticHalfband;
    QPushButton *Remez;
    QPushButton *NotchIIR;
    QPushButton *CutBoost;
    QPushButton *Butterworth;
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
        Chebyshev = new QPushButton(centralWidget);
        Chebyshev->setObjectName(QStringLiteral("Chebyshev"));
        Chebyshev->setGeometry(QRect(10, 70, 181, 27));
        Chebyshev->setCheckable(true);
        Elliptic = new QPushButton(centralWidget);
        Elliptic->setObjectName(QStringLiteral("Elliptic"));
        Elliptic->setGeometry(QRect(10, 100, 181, 27));
        Elliptic->setCheckable(true);
        MaxflatFIR = new QPushButton(centralWidget);
        MaxflatFIR->setObjectName(QStringLiteral("MaxflatFIR"));
        MaxflatFIR->setGeometry(QRect(10, 130, 181, 27));
        MaxflatFIR->setCheckable(true);
        MaxflatHalfband = new QPushButton(centralWidget);
        MaxflatHalfband->setObjectName(QStringLiteral("MaxflatHalfband"));
        MaxflatHalfband->setGeometry(QRect(10, 160, 181, 27));
        MaxflatHalfband->setCheckable(true);
        RaisedCosine = new QPushButton(centralWidget);
        RaisedCosine->setObjectName(QStringLiteral("RaisedCosine"));
        RaisedCosine->setGeometry(QRect(10, 220, 181, 27));
        RaisedCosine->setCheckable(true);
        RootRaisedCosine = new QPushButton(centralWidget);
        RootRaisedCosine->setObjectName(QStringLiteral("RootRaisedCosine"));
        RootRaisedCosine->setGeometry(QRect(10, 250, 181, 27));
        RootRaisedCosine->setCheckable(true);
        EllipticHalfband = new QPushButton(centralWidget);
        EllipticHalfband->setObjectName(QStringLiteral("EllipticHalfband"));
        EllipticHalfband->setGeometry(QRect(10, 190, 181, 27));
        EllipticHalfband->setCheckable(true);
        Remez = new QPushButton(centralWidget);
        Remez->setObjectName(QStringLiteral("Remez"));
        Remez->setGeometry(QRect(10, 280, 181, 27));
        Remez->setCheckable(true);
        NotchIIR = new QPushButton(centralWidget);
        NotchIIR->setObjectName(QStringLiteral("NotchIIR"));
        NotchIIR->setGeometry(QRect(10, 310, 181, 27));
        NotchIIR->setCheckable(true);
        CutBoost = new QPushButton(centralWidget);
        CutBoost->setObjectName(QStringLiteral("CutBoost"));
        CutBoost->setGeometry(QRect(10, 340, 181, 27));
        CutBoost->setCheckable(true);
        Butterworth = new QPushButton(centralWidget);
        Butterworth->setObjectName(QStringLiteral("Butterworth"));
        Butterworth->setGeometry(QRect(10, 40, 181, 27));
        Butterworth->setCheckable(true);
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
        Chebyshev->setText(QApplication::translate("MainWindow", "Chebyshev", 0));
        Elliptic->setText(QApplication::translate("MainWindow", "Elliptic", 0));
        MaxflatFIR->setText(QApplication::translate("MainWindow", "Maxflat FIR", 0));
        MaxflatHalfband->setText(QApplication::translate("MainWindow", "MaxflatHalfband", 0));
        RaisedCosine->setText(QApplication::translate("MainWindow", "RaisedCosine", 0));
        RootRaisedCosine->setText(QApplication::translate("MainWindow", "RootRaisedCosine", 0));
        EllipticHalfband->setText(QApplication::translate("MainWindow", "EllipticHalfband", 0));
        Remez->setText(QApplication::translate("MainWindow", "Remez", 0));
        NotchIIR->setText(QApplication::translate("MainWindow", "Notch", 0));
        CutBoost->setText(QApplication::translate("MainWindow", "CutBoost", 0));
        Butterworth->setText(QApplication::translate("MainWindow", "Butterworth", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
