/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionZapisz_konfiguracj;
    QAction *actionWczytaj_konfiguracj;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *comboTyp;
    QLabel *label_2;
    QDoubleSpinBox *spinAmp;
    QLabel *label_3;
    QDoubleSpinBox *spinOkres;
    QLabel *label_4;
    QDoubleSpinBox *spinWyp;
    QLabel *label_9;
    QDoubleSpinBox *spinS;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_8;
    QComboBox *comboTrybCalk;
    QLabel *label_5;
    QDoubleSpinBox *spinKp;
    QLabel *label_6;
    QDoubleSpinBox *spinTi;
    QPushButton *btnResetCalki;
    QLabel *label_7;
    QDoubleSpinBox *spinTd;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnReset;
    QPushButton *btnKonfiguracja;
    QDoubleSpinBox *spinInterwal;
    QLabel *label_10;
    QDoubleSpinBox *spinOknoCzasu;
    QMenuBar *menubar;
    QMenu *menuPlik;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(821, 849);
        actionZapisz_konfiguracj = new QAction(MainWindow);
        actionZapisz_konfiguracj->setObjectName("actionZapisz_konfiguracj");
        actionWczytaj_konfiguracj = new QAction(MainWindow);
        actionWczytaj_konfiguracj->setObjectName("actionWczytaj_konfiguracj");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");

        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(140, 0));
        groupBox->setMaximumSize(QSize(160, 300));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(groupBox);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        comboTyp = new QComboBox(groupBox);
        comboTyp->addItem(QString());
        comboTyp->addItem(QString());
        comboTyp->addItem(QString());
        comboTyp->setObjectName("comboTyp");

        verticalLayout->addWidget(comboTyp);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        spinAmp = new QDoubleSpinBox(groupBox);
        spinAmp->setObjectName("spinAmp");

        verticalLayout->addWidget(spinAmp);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        spinOkres = new QDoubleSpinBox(groupBox);
        spinOkres->setObjectName("spinOkres");

        verticalLayout->addWidget(spinOkres);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        spinWyp = new QDoubleSpinBox(groupBox);
        spinWyp->setObjectName("spinWyp");
        spinWyp->setMaximum(1.000000000000000);
        spinWyp->setValue(0.500000000000000);

        verticalLayout->addWidget(spinWyp);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");

        verticalLayout->addWidget(label_9);

        spinS = new QDoubleSpinBox(groupBox);
        spinS->setObjectName("spinS");
        spinS->setMinimum(-10.000000000000000);
        spinS->setMaximum(10.000000000000000);

        verticalLayout->addWidget(spinS);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");

        gridLayout->addLayout(horizontalLayout_3, 4, 1, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMinimumSize(QSize(0, 350));
        groupBox_2->setMaximumSize(QSize(160, 350));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");

        verticalLayout_2->addWidget(label_8);

        comboTrybCalk = new QComboBox(groupBox_2);
        comboTrybCalk->addItem(QString());
        comboTrybCalk->addItem(QString());
        comboTrybCalk->setObjectName("comboTrybCalk");

        verticalLayout_2->addWidget(comboTrybCalk);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        spinKp = new QDoubleSpinBox(groupBox_2);
        spinKp->setObjectName("spinKp");

        verticalLayout_2->addWidget(spinKp);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        verticalLayout_2->addWidget(label_6);

        spinTi = new QDoubleSpinBox(groupBox_2);
        spinTi->setObjectName("spinTi");

        verticalLayout_2->addWidget(spinTi);

        btnResetCalki = new QPushButton(groupBox_2);
        btnResetCalki->setObjectName("btnResetCalki");

        verticalLayout_2->addWidget(btnResetCalki);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(0, 20));

        verticalLayout_2->addWidget(label_7);

        spinTd = new QDoubleSpinBox(groupBox_2);
        spinTd->setObjectName("spinTd");

        verticalLayout_2->addWidget(spinTd);


        gridLayout->addWidget(groupBox_2, 4, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setMaximumSize(QSize(600, 60));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setObjectName("horizontalLayout");
        btnStart = new QPushButton(groupBox_3);
        btnStart->setObjectName("btnStart");
        btnStart->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(btnStart);

        btnStop = new QPushButton(groupBox_3);
        btnStop->setObjectName("btnStop");
        btnStop->setMinimumSize(QSize(50, 0));
        btnStop->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(btnStop);

        btnReset = new QPushButton(groupBox_3);
        btnReset->setObjectName("btnReset");
        btnReset->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(btnReset);

        btnKonfiguracja = new QPushButton(groupBox_3);
        btnKonfiguracja->setObjectName("btnKonfiguracja");
        btnKonfiguracja->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(btnKonfiguracja);

        spinInterwal = new QDoubleSpinBox(groupBox_3);
        spinInterwal->setObjectName("spinInterwal");
        spinInterwal->setMaximumSize(QSize(100, 30));
        spinInterwal->setMinimum(10.000000000000000);
        spinInterwal->setMaximum(1000.000000000000000);
        spinInterwal->setValue(200.000000000000000);

        horizontalLayout->addWidget(spinInterwal);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_10);

        spinOknoCzasu = new QDoubleSpinBox(groupBox_3);
        spinOknoCzasu->setObjectName("spinOknoCzasu");
        spinOknoCzasu->setMinimum(5.000000000000000);
        spinOknoCzasu->setMaximum(50.000000000000000);
        spinOknoCzasu->setValue(10.000000000000000);

        horizontalLayout->addWidget(spinOknoCzasu);


        gridLayout->addWidget(groupBox_3, 0, 0, 1, 2);

        gridLayout->setRowStretch(0, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 821, 21));
        menuPlik = new QMenu(menubar);
        menuPlik->setObjectName("menuPlik");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuPlik->menuAction());
        menuPlik->addAction(actionZapisz_konfiguracj);
        menuPlik->addAction(actionWczytaj_konfiguracj);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionZapisz_konfiguracj->setText(QCoreApplication::translate("MainWindow", "Zapisz konfiguracj\304\231", nullptr));
        actionWczytaj_konfiguracj->setText(QCoreApplication::translate("MainWindow", "Wczytaj konfiguracj\304\231", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Parametry Generatora", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Typ Sygna\305\202u:", nullptr));
        comboTyp->setItemText(0, QCoreApplication::translate("MainWindow", "Sta\305\202y", nullptr));
        comboTyp->setItemText(1, QCoreApplication::translate("MainWindow", "Prostok\304\205tny", nullptr));
        comboTyp->setItemText(2, QCoreApplication::translate("MainWindow", "Sinusoidalny", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Amplituda (A):", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Okres (T):", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Wype\305\202nienie (p):", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Sta\305\202a sk\305\202adowa (S):", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Parametry Regulatora:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Tryb ca\305\202kowania", nullptr));
        comboTrybCalk->setItemText(0, QCoreApplication::translate("MainWindow", "Zewn\304\231trznie", nullptr));
        comboTrybCalk->setItemText(1, QCoreApplication::translate("MainWindow", "Wewn\304\231trznie", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "Wzmocnienie (Kp):", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Sta\305\202a ca\305\202kowania (Ki):", nullptr));
        btnResetCalki->setText(QCoreApplication::translate("MainWindow", "Reset Ca\305\202ki", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Sta\305\202a r\303\263\305\274niczkowania(Kd):", nullptr));
        groupBox_3->setTitle(QString());
        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        btnKonfiguracja->setText(QCoreApplication::translate("MainWindow", "Konfiguracja Modelu", nullptr));
        spinInterwal->setSuffix(QCoreApplication::translate("MainWindow", "ms", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Okno czasu:", nullptr));
        menuPlik->setTitle(QCoreApplication::translate("MainWindow", "Plik", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
