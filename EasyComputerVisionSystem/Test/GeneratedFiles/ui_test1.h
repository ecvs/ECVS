/********************************************************************************
** Form generated from reading UI file 'test1.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST1_H
#define UI_TEST1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Test1
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *widget;

    void setupUi(QWidget *Test1)
    {
        if (Test1->objectName().isEmpty())
            Test1->setObjectName(QStringLiteral("Test1"));
        Test1->resize(400, 596);
        pushButton = new QPushButton(Test1);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(160, 270, 75, 23));
        pushButton_2 = new QPushButton(Test1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(190, 400, 75, 23));
        widget = new QWidget(Test1);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 20, 321, 181));

        retranslateUi(Test1);
        QObject::connect(pushButton, SIGNAL(clicked()), Test1, SLOT(OnBtnClicked()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), Test1, SLOT(slot1()));

        QMetaObject::connectSlotsByName(Test1);
    } // setupUi

    void retranslateUi(QWidget *Test1)
    {
        Test1->setWindowTitle(QApplication::translate("Test1", "Test1", 0));
        pushButton->setText(QApplication::translate("Test1", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("Test1", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class Test1: public Ui_Test1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST1_H
