/********************************************************************************
** Form generated from reading UI file 'InputSet.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTSET_H
#define UI_INPUTSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CInputSet
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableView *tableViewInputParam;
    QTableView *tableViewSelectedObj;
    QTableView *tableViewSelectedParam;

    void setupUi(QWidget *CInputSet)
    {
        if (CInputSet->objectName().isEmpty())
            CInputSet->setObjectName(QStringLiteral("CInputSet"));
        CInputSet->resize(729, 506);
        pushButton = new QPushButton(CInputSet);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(560, 470, 75, 23));
        pushButton_2 = new QPushButton(CInputSet);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(640, 470, 75, 23));
        tableViewInputParam = new QTableView(CInputSet);
        tableViewInputParam->setObjectName(QStringLiteral("tableViewInputParam"));
        tableViewInputParam->setGeometry(QRect(10, 10, 231, 451));
        tableViewSelectedObj = new QTableView(CInputSet);
        tableViewSelectedObj->setObjectName(QStringLiteral("tableViewSelectedObj"));
        tableViewSelectedObj->setGeometry(QRect(260, 10, 131, 451));
        tableViewSelectedParam = new QTableView(CInputSet);
        tableViewSelectedParam->setObjectName(QStringLiteral("tableViewSelectedParam"));
        tableViewSelectedParam->setGeometry(QRect(400, 10, 321, 451));

        retranslateUi(CInputSet);

        QMetaObject::connectSlotsByName(CInputSet);
    } // setupUi

    void retranslateUi(QWidget *CInputSet)
    {
        CInputSet->setWindowTitle(QApplication::translate("CInputSet", "CFlowSet", 0));
        pushButton->setText(QApplication::translate("CInputSet", "\347\241\256\345\256\232", 0));
        pushButton_2->setText(QApplication::translate("CInputSet", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class CInputSet: public Ui_CInputSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTSET_H
