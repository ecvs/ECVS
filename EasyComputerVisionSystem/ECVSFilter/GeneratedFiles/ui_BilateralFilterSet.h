/********************************************************************************
** Form generated from reading UI file 'BilateralFilterSet.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BILATERALFILTERSET_H
#define UI_BILATERALFILTERSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CBilateralFilterSet
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSlider *horizontalSliderD;
    QSpinBox *spinBoxD;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSlider *horizontalSliderSigmaColor;
    QSpinBox *spinBoxSigmaColor;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *horizontalSliderSigmaSpace;
    QSpinBox *spinBoxSigmaSpace;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *OKBtn;
    QPushButton *CancelBtn;
    QHBoxLayout *horizontalLayout_5;

    void setupUi(QWidget *CBilateralFilterSet)
    {
        if (CBilateralFilterSet->objectName().isEmpty())
            CBilateralFilterSet->setObjectName(QStringLiteral("CBilateralFilterSet"));
        CBilateralFilterSet->resize(987, 744);
        gridLayout = new QGridLayout(CBilateralFilterSet);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        label_4 = new QLabel(CBilateralFilterSet);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(70, 0));

        horizontalLayout_3->addWidget(label_4);

        horizontalSliderD = new QSlider(CBilateralFilterSet);
        horizontalSliderD->setObjectName(QStringLiteral("horizontalSliderD"));
        horizontalSliderD->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSliderD);

        spinBoxD = new QSpinBox(CBilateralFilterSet);
        spinBoxD->setObjectName(QStringLiteral("spinBoxD"));
        spinBoxD->setMinimumSize(QSize(60, 0));

        horizontalLayout_3->addWidget(spinBoxD);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(CBilateralFilterSet);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(70, 0));

        horizontalLayout_2->addWidget(label_2);

        horizontalSliderSigmaColor = new QSlider(CBilateralFilterSet);
        horizontalSliderSigmaColor->setObjectName(QStringLiteral("horizontalSliderSigmaColor"));
        horizontalSliderSigmaColor->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSliderSigmaColor);

        spinBoxSigmaColor = new QSpinBox(CBilateralFilterSet);
        spinBoxSigmaColor->setObjectName(QStringLiteral("spinBoxSigmaColor"));
        spinBoxSigmaColor->setMinimumSize(QSize(60, 0));

        horizontalLayout_2->addWidget(spinBoxSigmaColor);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(CBilateralFilterSet);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(70, 0));

        horizontalLayout->addWidget(label);

        horizontalSliderSigmaSpace = new QSlider(CBilateralFilterSet);
        horizontalSliderSigmaSpace->setObjectName(QStringLiteral("horizontalSliderSigmaSpace"));
        horizontalSliderSigmaSpace->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSliderSigmaSpace);

        spinBoxSigmaSpace = new QSpinBox(CBilateralFilterSet);
        spinBoxSigmaSpace->setObjectName(QStringLiteral("spinBoxSigmaSpace"));
        spinBoxSigmaSpace->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(spinBoxSigmaSpace);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        frame = new QFrame(CBilateralFilterSet);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        OKBtn = new QPushButton(CBilateralFilterSet);
        OKBtn->setObjectName(QStringLiteral("OKBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(OKBtn->sizePolicy().hasHeightForWidth());
        OKBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(OKBtn);

        CancelBtn = new QPushButton(CBilateralFilterSet);
        CancelBtn->setObjectName(QStringLiteral("CancelBtn"));
        sizePolicy1.setHeightForWidth(CancelBtn->sizePolicy().hasHeightForWidth());
        CancelBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(CancelBtn);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));

        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);


        retranslateUi(CBilateralFilterSet);

        QMetaObject::connectSlotsByName(CBilateralFilterSet);
    } // setupUi

    void retranslateUi(QWidget *CBilateralFilterSet)
    {
        CBilateralFilterSet->setWindowTitle(QApplication::translate("CBilateralFilterSet", "BilateralFilter", 0));
        label_4->setText(QApplication::translate("CBilateralFilterSet", "D", 0));
        label_2->setText(QApplication::translate("CBilateralFilterSet", "Sigma Color", 0));
        label->setText(QApplication::translate("CBilateralFilterSet", "Sigma Space", 0));
        OKBtn->setText(QApplication::translate("CBilateralFilterSet", "\347\241\256\345\256\232", 0));
        CancelBtn->setText(QApplication::translate("CBilateralFilterSet", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class CBilateralFilterSet: public Ui_CBilateralFilterSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BILATERALFILTERSET_H
