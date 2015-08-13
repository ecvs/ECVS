/********************************************************************************
** Form generated from reading UI file 'ecvs.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECVS_H
#define UI_ECVS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ECVSClass
{
public:
    QAction *actionToolBox;
    QAction *actionDfas;
    QAction *actionDebugWnd;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuCamera;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ECVSClass)
    {
        if (ECVSClass->objectName().isEmpty())
            ECVSClass->setObjectName(QStringLiteral("ECVSClass"));
        ECVSClass->resize(998, 674);
        actionToolBox = new QAction(ECVSClass);
        actionToolBox->setObjectName(QStringLiteral("actionToolBox"));
        actionDfas = new QAction(ECVSClass);
        actionDfas->setObjectName(QStringLiteral("actionDfas"));
        actionDebugWnd = new QAction(ECVSClass);
        actionDebugWnd->setObjectName(QStringLiteral("actionDebugWnd"));
        centralWidget = new QWidget(ECVSClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ECVSClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ECVSClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 998, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QStringLiteral("menuCamera"));
        ECVSClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ECVSClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ECVSClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ECVSClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ECVSClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuCamera->menuAction());

        retranslateUi(ECVSClass);

        QMetaObject::connectSlotsByName(ECVSClass);
    } // setupUi

    void retranslateUi(QMainWindow *ECVSClass)
    {
        ECVSClass->setWindowTitle(QApplication::translate("ECVSClass", "ECVS", 0));
        actionToolBox->setText(QApplication::translate("ECVSClass", "\345\267\245\345\205\267\347\256\261", 0));
        actionDfas->setText(QApplication::translate("ECVSClass", "\345\257\271\350\261\241\345\210\227\350\241\250", 0));
        actionDebugWnd->setText(QApplication::translate("ECVSClass", "\350\260\203\350\257\225\347\252\227\345\217\243", 0));
        menuFile->setTitle(QApplication::translate("ECVSClass", "\346\226\207\344\273\266", 0));
        menuView->setTitle(QApplication::translate("ECVSClass", "\350\247\206\345\233\276", 0));
        menuCamera->setTitle(QApplication::translate("ECVSClass", "\347\233\270\346\234\272", 0));
    } // retranslateUi

};

namespace Ui {
    class ECVSClass: public Ui_ECVSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECVS_H
