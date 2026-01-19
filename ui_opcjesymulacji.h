/********************************************************************************
** Form generated from reading UI file 'opcjesymulacji.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPCJESYMULACJI_H
#define UI_OPCJESYMULACJI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_opcjeSymulacji
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineA;
    QLabel *label_2;
    QLineEdit *lineB;
    QLabel *label_3;
    QSpinBox *spinK;
    QLabel *label_4;
    QDoubleSpinBox *spinZ;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *spinUmin;
    QLabel *label_5;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *spinUmax;
    QLabel *label_6;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *spinYmin;
    QLabel *label_7;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *spinYmax;
    QLabel *label_8;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkOgraniczenia;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *opcjeSymulacji)
    {
        if (opcjeSymulacji->objectName().isEmpty())
            opcjeSymulacji->setObjectName("opcjeSymulacji");
        opcjeSymulacji->resize(400, 300);
        layoutWidget = new QWidget(opcjeSymulacji);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 111, 221));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        lineA = new QLineEdit(layoutWidget);
        lineA->setObjectName("lineA");

        verticalLayout->addWidget(lineA);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        lineB = new QLineEdit(layoutWidget);
        lineB->setObjectName("lineB");

        verticalLayout->addWidget(lineB);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        spinK = new QSpinBox(layoutWidget);
        spinK->setObjectName("spinK");
        spinK->setMinimum(1);
        spinK->setMaximum(100);

        verticalLayout->addWidget(spinK);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        spinZ = new QDoubleSpinBox(layoutWidget);
        spinZ->setObjectName("spinZ");
        spinZ->setSingleStep(0.010000000000000);

        verticalLayout->addWidget(spinZ);

        horizontalLayoutWidget = new QWidget(opcjeSymulacji);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(230, 10, 160, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        spinUmin = new QDoubleSpinBox(horizontalLayoutWidget);
        spinUmin->setObjectName("spinUmin");
        spinUmin->setMinimum(-100.000000000000000);
        spinUmin->setMaximum(0.000000000000000);
        spinUmin->setSingleStep(0.100000000000000);
        spinUmin->setValue(-10.000000000000000);

        horizontalLayout->addWidget(spinUmin);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName("label_5");

        horizontalLayout->addWidget(label_5);

        horizontalLayoutWidget_2 = new QWidget(opcjeSymulacji);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(230, 50, 160, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        spinUmax = new QDoubleSpinBox(horizontalLayoutWidget_2);
        spinUmax->setObjectName("spinUmax");
        spinUmax->setMaximum(100.000000000000000);
        spinUmax->setSingleStep(0.100000000000000);
        spinUmax->setValue(10.000000000000000);

        horizontalLayout_2->addWidget(spinUmax);

        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName("label_6");

        horizontalLayout_2->addWidget(label_6);

        horizontalLayoutWidget_3 = new QWidget(opcjeSymulacji);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(230, 90, 160, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        spinYmin = new QDoubleSpinBox(horizontalLayoutWidget_3);
        spinYmin->setObjectName("spinYmin");
        spinYmin->setMinimum(-100.000000000000000);
        spinYmin->setMaximum(0.000000000000000);
        spinYmin->setSingleStep(0.100000000000000);
        spinYmin->setValue(-10.000000000000000);

        horizontalLayout_3->addWidget(spinYmin);

        label_7 = new QLabel(horizontalLayoutWidget_3);
        label_7->setObjectName("label_7");

        horizontalLayout_3->addWidget(label_7);

        horizontalLayoutWidget_4 = new QWidget(opcjeSymulacji);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(230, 130, 160, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        spinYmax = new QDoubleSpinBox(horizontalLayoutWidget_4);
        spinYmax->setObjectName("spinYmax");
        spinYmax->setMaximum(100.000000000000000);
        spinYmax->setSingleStep(0.100000000000000);
        spinYmax->setValue(10.000000000000000);

        horizontalLayout_4->addWidget(spinYmax);

        label_8 = new QLabel(horizontalLayoutWidget_4);
        label_8->setObjectName("label_8");

        horizontalLayout_4->addWidget(label_8);

        verticalLayoutWidget = new QWidget(opcjeSymulacji);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(230, 170, 160, 41));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkOgraniczenia = new QCheckBox(verticalLayoutWidget);
        checkOgraniczenia->setObjectName("checkOgraniczenia");
        checkOgraniczenia->setChecked(true);

        verticalLayout_2->addWidget(checkOgraniczenia);

        verticalLayoutWidget_2 = new QWidget(opcjeSymulacji);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(-1, 259, 401, 41));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        buttonBox = new QDialogButtonBox(verticalLayoutWidget_2);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setMaximumSize(QSize(280, 16777215));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(opcjeSymulacji);

        QMetaObject::connectSlotsByName(opcjeSymulacji);
    } // setupUi

    void retranslateUi(QDialog *opcjeSymulacji)
    {
        opcjeSymulacji->setWindowTitle(QCoreApplication::translate("opcjeSymulacji", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("opcjeSymulacji", "Wielomian A", nullptr));
        lineA->setText(QCoreApplication::translate("opcjeSymulacji", "0.00", nullptr));
        label_2->setText(QCoreApplication::translate("opcjeSymulacji", "Wielomian B", nullptr));
        lineB->setText(QCoreApplication::translate("opcjeSymulacji", "0.00", nullptr));
        label_3->setText(QCoreApplication::translate("opcjeSymulacji", "Op\303\263\305\272nienie (k)", nullptr));
        label_4->setText(QCoreApplication::translate("opcjeSymulacji", "Zak\305\202\303\263cenie", nullptr));
        label_5->setText(QCoreApplication::translate("opcjeSymulacji", "u min", nullptr));
        label_6->setText(QCoreApplication::translate("opcjeSymulacji", "u max", nullptr));
        label_7->setText(QCoreApplication::translate("opcjeSymulacji", "y min", nullptr));
        label_8->setText(QCoreApplication::translate("opcjeSymulacji", "y max", nullptr));
        checkOgraniczenia->setText(QCoreApplication::translate("opcjeSymulacji", "W\305\202\304\205cz ograniczenia", nullptr));
    } // retranslateUi

};

namespace Ui {
    class opcjeSymulacji: public Ui_opcjeSymulacji {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPCJESYMULACJI_H
